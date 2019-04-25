#ifndef RECEIVER_H
#define RECEIVER_H

#include <QDialog>
//#pragma execution_character_set("utf-8")
//#pragma execution_character_set("utf-8")class QHostAddress;

#include<QHostAddress>
#include<QTime>
#include<QTimer>
#include "pkt.h"
class QUdpSocket;
namespace Ui {
class receiver;
}
struct packet;
struct ack_packet ;

class receiver : public QDialog
{
    Q_OBJECT

public:
    explicit receiver(QWidget *parent = 0,const QHostAddress &ip=QHostAddress("127.0.0.1"),const QString &filename="",long int len=0);
    ~receiver();
    void init();
    void closeEvent(QCloseEvent *);
private slots:
    void rcvpkt();
    void timeout_handler();
signals:
    //timeout();
private:
    Ui::receiver *ui;
    QUdpSocket *udpsocket;
    quint16 tPort;
    long int filesize;
    qint64 totalBytes;
    qint64 bytesReceived;
    QString fileName;
    QHostAddress senderip;
    QTime alltime;
    FILE* output;
    QTimer timer;
    int expected_num = 0, timeout = 4;
    struct packet file_name_pkt;
    int flag;

};


#endif // RECEIVER_H
