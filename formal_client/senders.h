#ifndef SENDERS_H
#define SENDERS_H
#include "pkt.h"
#include <QObject>
#include <QUdpSocket>
#include <QDialog>
#include <QTimer>

#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QMessageBox>

#include <cstring>
#include <fstream>
#include <stdint.h>
//#include <sys/time.h>
#include <cstdlib>

#include <iostream>

#include <QString>
//#pragma execution_character_set("utf-8")
//#pragma execution_character_set("utf-8")
//#include <QObject>  /**必不可少*/

namespace Ui {
class senders;
}


struct packet;
struct ack_packet;

class senders: public QDialog
{

Q_OBJECT
public:
     explicit senders(QWidget *parent = 0,const QHostAddress &hip=QHostAddress("127.0.0.1"),const QString &fileName="",long int len=0);
    ~senders();
    void init();
    void gbn();
    void send(int i);
    void resend();
    void closeEvent(QCloseEvent *);
    //Q_OBJECT
private slots:

     void recv_ack();
signals:

 private:
    FILE *input;

    qint64 bytesSend;
    QUdpSocket *udpsocket;
    Ui::senders *ui;
    quint16 udpport;
    QString filename;

    QHostAddress hostip;

    int flag;
    int sending_window_size;
    int remaining_chunks;
    int base=0,  next_seqnum=0;
   int expected_seqnum = 0;
    int duplicate=0, resend_base=0;
    int timeout=2,timeout_counter=0;
    int lastsend;
    int timepass;

    //int last_resent=0;
    struct packet *pkts;

    QTime alltime;//全局时间，计算速率

    QTime ack_time;


    long int filesize;
};

#endif // SENDERS_H
