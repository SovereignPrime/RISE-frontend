#include <QFileDialog>
#include <QFileInfo>
#include <QVariant>
#include "rise.h"



RISE::RISE(QString *p)
{
    path = *p;
#ifdef Q_WS_WIN
    backend.start("../start.cmd");
    QString tmpdir = qgetenv("TMP");
#else
    backend.start(path.append("/rise_service"), QStringList() << "start");
    backend.waitForFinished();
    QString tmpdir = "/tmp";
#endif
    QFile file(tmpdir.append("/rise.port"));
    while (!file.exists());

    if(file.open(QFile::ReadOnly))
        port = file.readLine();
    else
        return;
    pWebView = webView();
    pWebPage = pWebView->page();
    pWebPage->setForwardUnsupportedContent(true);
    createActions();
    QString url = port.prepend("http://localhost:");
    loadUrl(QUrl(url));
    show();
}

RISE::~RISE()
{
#ifndef Q_WS_WIN
    backend.start(path.append("/rise_service"), QStringList() << "stop");
    //backend.waitForFinished();
#endif
}

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
        reply->request().setAttribute(QNetworkRequest::User, fileName);
        connect(reply, SIGNAL(finished()), this, SLOT(downloaded()));
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
