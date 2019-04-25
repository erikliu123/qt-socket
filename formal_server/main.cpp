#include "server.h"
#include "db.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MySql *s=new MySql();
            QTranslator qtTranslator;
            qtTranslator.load("myapp.qm");
            a.installTranslator(&qtTranslator);
            QTranslator qtTranslator2;
            qtTranslator2.load("qt_zh_CN.qm");
            a.installTranslator(&qtTranslator2);

    //s.initsql();
    TcpServer w;
    w.show();

    return a.exec();
}
