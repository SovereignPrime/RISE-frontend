#include <QApplication>
#include "rise.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString path = "../rise/bin";
    //QString path = app.applicationDirPath();
    RISE rise(&path);
    rise.show();
    return app.exec();
}
