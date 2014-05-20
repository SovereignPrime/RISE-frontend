#include <QFileDialog>
#include <QFileInfo>
#include <QVariant>
#include "rise.h"



RISE::RISE()
{
    pWebView = webView();
    pWebPage = pWebView->page();
    pWebPage->setForwardUnsupportedContent(true);
    createActions();
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
