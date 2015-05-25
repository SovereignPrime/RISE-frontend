#ifndef RISE_H
#define RISE_H
#include <QAction>
#include <QGraphicsWebView>
#include <QWebPage>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QProcess>
#include <QWebView>
//#include "html5applicationviewer.h"

class RISE : public QWebView
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
    void dropEvent(QDropEvent*);

    QWebPage *pWebPage;

    QProcess backend;
    QString port;
    QString path;
    QFile clog;
    QClipboard *clipboard;


};

#endif // RISE_H
