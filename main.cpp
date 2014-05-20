#include <QApplication>
#include <QProcess>
#include "rise.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    RISE rise;
    rise.show();
    QProcess process;

#ifdef Q_WS_WIN
    process.start("../start.cmd");
    QString tmpdir = qgetenv("TMP");
#else
    process.start("/opt/rise/bin/rise_service", QStringList() << "start");
    process.waitForFinished();
    QString tmpdir = "/tmp";
#endif
    QFile file(tmpdir.append("/rise.port"));
    while (!file.exists());
    QString port = "";
    if(file.open(QFile::ReadOnly))
        port = file.readLine();
    else
        return -1;
    rise.loadUrl(QUrl(port.prepend("http://localhost:")));
    return app.exec();
}
