#ifndef RISE_H
#define RISE_H
#include <QAction>
#include <QGraphicsWebView>
#include <QWebPage>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QProcess>
#include "html5applicationviewer.h"

class RISE : public Html5ApplicationViewer
{
    Q_OBJECT

public:
    RISE(QString *p);
    ~RISE();

private slots:
    void downloadRequested(const QNetworkRequest &);
    void unsupportedContent(QNetworkReply *);
    void downloaded();
    void error(QNetworkReply::NetworkError);
    void downloadProgress(qint64 r, qint64 t);
    void readyReadStandardOutput();

private:
    void createActions();

    QGraphicsWebView *pWebView;
    QWebPage *pWebPage;

    QProcess backend;
    QString port;
    QString path;


};

#endif // RISE_H
