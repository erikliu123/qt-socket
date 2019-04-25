//tcpserver.h
#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QMainWindow>
#include <QtNetwork>
#include <QTimer>
#include <QMap>
#include "db.h"
namespace Ui {
class TcpServer;
}
struct socket{
    QString theip;
    quint16 port;
};
class TcpServer : public QMainWindow
{
    Q_OBJECT

public:


    std::string gethostMac();
    explicit TcpServer(QWidget *parent = 0);
    bool checkExist(QString name);
    bool checkSignIn(QString name,QString passward);
    bool checkHasSign(QString name,QString passward,QString mail);
    bool checkMail(QString, QString);
    bool checkReset(QString, QString);
    ~TcpServer();


signals:
    void sbLogin();
    void userNumChange();

private slots:
      void sendUserList();
       void sendUsertcp();
    void readData();
    void on_startBtn_clicked();
    void on_closeBtn_clicked();
    void acceptConnection();
   void removeUserFormList();



private:
     //QTcpSocket *tcpSocket;
    Ui::TcpServer *ui;
    MySql *QMysql;
    //QTcpSocket *tcpSocket;
    QTcpServer *tcpServer;
    QTimer *timer;
    //QList<QTcpSocket *> userList;

    QMap<QString,  socket> usertcp;//用户作为服务器的信息
    QMap<QTcpSocket *,QString> userMessage;//在线用户信息
     QMap<QTcpSocket *,  QString> tcpMAC;//记录登录失败的MAC
};

#endif // TCPSERVER_H
