#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMap>
#include <QTcpServer>
#include <QSet>
#include <QStackedWidget>
#include<QRegExp>
#include "p2p.h"
namespace Ui {
class MainWindow;
}

struct socket{
    QString theip;
    qint16 port;

    bool operator == (const socket &a) const{
		/*
		 QString pattern("(.*) = (.*)");
    QRegExp rx(pattern);

    QString str(“a=100″);
    int pos = str.indexOf(rx);
		*/
		QString pattern("[0-9]");
		QRegExp rx(pattern);
		QString temp = a.theip.mid(a.theip.indexOf(rx)), temp2 = this->theip.mid(this->theip.indexOf(rx));
        return (temp==temp2) && (a.port==this->port);

    }
    bool operator != (const socket &a) const{
		QString pattern("[0-9]");
		QRegExp rx(pattern);
		QString temp = a.theip.mid(a.theip.indexOf(rx)), temp2 = this->theip.mid(this->theip.indexOf(rx));
        return !((temp == temp2) && (a.port == this->port));
    }
};

class ChatRoom : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatRoom(QWidget *parent = 0);
    ChatRoom(QWidget *parent,QTcpSocket *pTcpSocket,QString _name, qint16 _port, QString serverIP="127.0.0.1") ;
    ~ChatRoom();
    QString getList(QStringList &list);
    PersonalDialog* newp2p(QString);
	void closeEvent(QCloseEvent *);
public slots:
    QTcpSocket* createP2PSocket(QString &str);
    void stackchanged(int index);
    void getUserList();
    void acceptConnection();
    void sendLeave();
    void opponentHasLeave();//对方下线
    void readMessages();//远地服务器
    void readMessages3();//P2P
    void on_listWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QStackedWidget *m_pStackedWidget;
    QString  SbCreatServer= "server";//创建新服务端
    QTcpSocket *tcpSocket;
    QString name;
    QStringList onlineUser;
    QString myip;
    QString serverIP; //NAT无法P2P发送时备用
    quint16 myport;
    int flag;

    int Tport;

    QTcpServer *person;//创建自己的服务端

    QString filename;
public:
    //receiver *rec;
    //senders *send;
    long int length;

    QMap<QString,socket> pp;
    QSet<QString> hasLogUser;
    QMap<QString,PersonalDialog*> pdList;

    QString lastSendName="";//上次谁发来了消息
	QSet<QTcpSocket *> *socket_list ;
};

#endif // MAINWINDOW_H
