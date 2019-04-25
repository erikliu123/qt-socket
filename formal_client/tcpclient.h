//tcpclient.h
#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QMainWindow>
#include <QtNetwork>
#include <QMessageBox>
#include <QInputDialog>
//#pragma execution_character_set("utf-8")
//#pragma execution_character_set("utf-8")

namespace Ui {
class TcpClient;
}

class TcpClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit TcpClient(QWidget *parent = 0);
    ~TcpClient();
    QString gethostMac();
protected:
    void init();
    void connectServer();

private slots:
    void on_sendBtn_clicked();
    void on_link_clicked();
    void on_dislink_clicked();
    void displayError(QAbstractSocket::SocketError);

    void on_signBtn_clicked();

    void readMessages();

    //void readip();

    //void on_pushButton_2_clicked();

    void on_resetpwdButton_clicked();
    void reset(QString);

private:
    Ui::TcpClient *ui;
    QTcpSocket *tcpSocket;
   // QTcpSocket *tcpSocket2;
    int readFlag;

    QString myip;
    int myport;

};

#endif // TCPCLIENT_H
