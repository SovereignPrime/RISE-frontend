#include <QFileDialog>
#include <QFileInfo>
#include <QVariant>
#include <QEventLoop>
#include <QApplication>
#include <QRegExp>
#include "rise.h"



RISE::RISE(QString *p)
{
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    QDir pt(*p);
    pt.cdUp();
    backend.setWorkingDirectory(pt.path());
    env.insert("ROOTDIR", ".");
    env.insert("DOC_ROOT", "./site/static");
    QStringList args;
    QString vsn = "v";
    QFile vsn_file(pt.path() + "/releases/start_erl.data");
    if (vsn_file.open(QFile::ReadOnly)) {
        vsn = vsn_file.readLine().split(' ').last().trimmed();
    }
    path = *p;
    backend.setProcessEnvironment(env);
    clog.setFileName(env.value("HOME") + "/.config/RISE/log/erlang.log");
    if (clog.exists())
      clog.remove();
    clog.open(QFile::WriteOnly);



#ifdef Q_OS_WIN32
    args << "-pa" << "./site/include" << "./site/ebin" <<
            "-boot" << "./releases/" + vsn  + "/rise" <<
            "-embded" << "-sname" << "rise" <<
            "-config" << "./etc/app.generated.config" <<
            "-args_file" << "./etc/vm.args";
    backend.start(backend.workingDirectory() + "/erts-6.0/bin/erl.exe", args );
#else
    args << "-pa" << "./site/include" << 
        "-pa" << "./site/ebin" <<
        "-boot" << "./releases/" + vsn + "/rise" <<
        "-embded" << "-sname" << "rise" <<
        "-config" << "./etc/app.config" <<
        "-config" << "./etc/bitmessage.config" <<
        "-config" << "./etc/cowboy.config" <<
        "-config" << "./etc/eminer.config" <<
        "-config" << "./etc/etorrent.config" <<
        "-config" << "./etc/sync.config" <<
        "-args_file" << "./etc/vm.args";
    backend.start(backend.workingDirectory() + "/erts-6.1/bin/erl", args );
#endif
    connect(&backend, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
    backend.waitForStarted(300000);
    backend.waitForReadyRead();
    pWebView = webView();
    pWebView -> setAcceptHoverEvents(true);
    pWebPage = pWebView->page();
    pWebPage->setForwardUnsupportedContent(true);
    createActions();
    showExpanded();
}

RISE::~RISE()
{
    backend.terminate();
}

void RISE::readyReadStandardOutput()
{
    while (backend.canReadLine()) {

        QByteArray data = backend.readLine();
        QString str(data);
        clog.write(data);
        QRegExp cap("^.+0.0.0:(\\d+),.*$");
        if (cap.exactMatch(str)) {
            port = cap.cap(1);
            QString url = port.prepend("http://localhost:");
            loadUrl(QUrl(url));
        }
    }
};

void RISE::createActions()
{
    connect(pWebView->page(), SIGNAL(downloadRequested(QNetworkRequest)), this, SLOT(downloadRequested(QNetworkRequest)));
    connect(pWebPage, SIGNAL(unsupportedContent(QNetworkReply*)), this, SLOT(unsupportedContent(QNetworkReply*)));
}

void RISE::downloadRequested(const QNetworkRequest &request)
{
    // First prompted with a file dialog to make sure
    // they want the file and to select a download
    // location and name.
    QString defaultFileName =
            QFileInfo(request.url().toString()).fileName();
    QString fileName =
            QFileDialog::getSaveFileName(this,
                                         tr("Save File"),
                                         defaultFileName);
    if (fileName.isEmpty())
        return;

    // Construct a new request that stores the
    // file name that should be used when the
    // download is complete
    QNetworkRequest newRequest = request;
    newRequest.setAttribute(QNetworkRequest::User,
                            fileName);

    // Ask the network manager to download
    // the file and connect to the progress
    // and finished signals.
    QNetworkAccessManager *networkManager =
            pWebView->page()->networkAccessManager();
    QNetworkReply *reply =
            networkManager->get(newRequest);
   /* connect(
                reply, SIGNAL(downloadProgress(qint64, qint64)),
                this, SLOT(downloadProgress(qint64, qint64)));*/
    connect(reply, SIGNAL(finished()),
            this, SLOT(downloaded()));
}

void RISE::unsupportedContent(QNetworkReply *reply)
{
    if (reply->hasRawHeader("Content-Disposition"))
    {
        QString disp = reply->rawHeader("Content-Disposition");
        QString defaultFileName = disp.split(";")[1].split("=")[1];
        QString fileName =
                QFileDialog::getSaveFileName(this,
                                             tr("Save File"),
                                             defaultFileName);

        if (fileName.isEmpty())
            return;
        if (reply->isFinished()) {
            QFile file(fileName);
            if(file.open(QFile::ReadWrite))
                file.write(reply->readAll());
        } else {
            reply->request().setAttribute(QNetworkRequest::User, fileName);
            connect(reply, SIGNAL(finished()), this, SLOT(downloaded()));
            connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadProgress(qint64, qint64)));
            connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
        }
    }
    return;
}

void RISE::downloaded()
{
    QNetworkReply * reply = ((QNetworkReply*)sender());
    QString fileName = reply->request().attribute(QNetworkRequest::User).toString();
    QFile file(fileName);
    if(file.open(QFile::ReadWrite))
        file.write(reply->readAll());
}

void RISE::error(QNetworkReply::NetworkError code)
{
    //qDebug() << "Network error: " << code << "\n";
}

void RISE::downloadProgress(qint64 r, qint64 t)
{
    //qDebug() << "Network error: " << r << ", " << t << "\n";
}
