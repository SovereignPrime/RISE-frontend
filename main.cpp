#include <QApplication>
#include "rise.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    RISE rise;
    rise.show();
    rise.loadUrl(QUrl(QLatin1String("http://localhost:44813")));
    return app.exec();
}
