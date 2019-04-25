#include "tcpclient.h"
#include <QApplication>
#include <QPixmap>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QScreen>
#include<QDebug>
#pragma execution_character_set("utf-8")
int main(int argc, char *argv[]){
    QApplication a(argc,argv);
    TcpClient w;
    w.show();
/*
 * 截屏部分
    QThread::sleep(1);//必须要睡眠，这个show是异步的，程序执行的很快截屏不到。
    QString fileName;
    QScreen *grab= QGuiApplication::primaryScreen();
    WId showid=QApplication::desktop()->winId();
    qDebug("%d QApplication::desktop()->winId()=%d",w.winId(),QApplication::desktop()->winId());
    qDebug()<<w.geometry().x()<<w.geometry().y();
    QPixmap temp=grab->grabWindow(showid,w.geometry().x(),w.geometry().y(),
                                  w.geometry().width(),w.geometry().height());//参数1 showid=0，才能截屏成功

    fileName= QDateTime::currentDateTime().toString("yyyy-MM-ddHH-mm-ss")+"_"+QString::number(showid)  + ".jpg";//通过时间命名文件
    if(!temp.save(fileName, "jpg"))

    {

        QMessageBox::information(NULL,"失败","nothing",QMessageBox::Ok);

    }
    else{
        QMessageBox::information(NULL,"截图成功","nothing",QMessageBox::Ok);
    }
*/
    return a.exec();

}
