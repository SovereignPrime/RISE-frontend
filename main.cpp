#include <QApplication>
#include "rise.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    RISE rise;
    rise.show();
    return app.exec();
}
