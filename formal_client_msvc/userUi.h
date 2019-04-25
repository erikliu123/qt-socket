//userinterface.h
#ifndef USERINTERFACE_H
#define USERINTERFACE_H
//#ifndef USERUI_H
//#define USERUI_H
#pragma once
#include "senders.h"
#include "receiver.h"
#include "p2p.h"

#include <QMainWindow> //neccessary
#include <QTcpSocket>


class QMainWindow;
class QTcpServer;
//class senders;
//class receiver;
class QUdpSocket;

namespace Ui {
class UserInterface;
}
using namespace std;

struct socket{
    QString theip;
    qint16 port;

    bool operator == (const socket &a) const{
        return a.theip==this->theip && a.port==this->port;

    }
    bool operator != (const socket &a) const{
        return !(a.theip==this->theip && a.port==this->port);
    }
};


class UserUi : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserUi(QWidget *parent = 0,QTcpSocket *pTcpSocket=0,QString _name="",qint16 _port=6000);
    ~UserUi();
    void closeEvent(QCloseEvent *);
    QString getList(QStringList &s);

private slots:
    QTcpSocket* createP2PSocket(QString &str);
    void sendLeave();
    void opponentHasLeave(QString &name);
    void readMessages();
    void readMessages2();
    void readMessages3();
    void acceptConnection();
    void on_pushButton_clicked();

    void on_refreshBtn_clicked();
    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_openFileBtn_clicked();

    void on_pushButton_4_clicked();

private:
    QString  SbCreatServer= "server";//创建新服务端
    Ui::UserInterface *ui;
    QTcpSocket *tcpSocket;
    QString name;
    QStringList onlineUser;
    QString myip;
    quint16 myport;
    int flag;

    int Tport;

    QHostAddress Tip;//没作用？

    QTcpServer *person;//创建自己的服务端
    QTcpSocket *hh,*hh1;

    QString filename;
public:
    receiver *rec;
    senders *send;
    long int length;

    QMap<QString,socket> pp;
    QMap<QString,PersonalDialog*> pdList;

    QString lastSendName="";//上次谁发来了消息
};

#endif // USERINTERFACE_H
