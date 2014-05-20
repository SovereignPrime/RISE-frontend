#ifndef RISE_H
#define RISE_H
#include <QAction>
#include <QGraphicsWebView>
#include <QWebPage>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "html5applicationviewer.h"

class RISE : public Html5ApplicationViewer
{
    Q_OBJECT

public:
    RISE();

private slots:
    void downloadRequested(const QNetworkRequest &);
    void unsupportedContent(QNetworkReply *);
    void downloaded();

private:
    void createActions();

    QGraphicsWebView *pWebView;
    QWebPage *pWebPage;

};

#endif // RISE_H
