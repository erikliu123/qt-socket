#include "receiver.h"
#include "pkt.h"
#include "ui_receiver.h"
#include <QDebug>

#include <QUdpSocket>
//#include <QTimer>
#include <cstring>
//#include <QTime>

#include <QMessageBox>
#define ackport 6000
receiver::receiver(QWidget *parent,const QHostAddress &hostip,const QString &filename,long int len) :
    QDialog(parent),
    ui(new Ui::receiver)
{
    ui->setupUi(this);
    setFixedSize(400,190);
    filesize=len;
    bytesReceived = 0;
    expected_num=0;
    senderip=QHostAddress(hostip);
    output=fopen(filename.toLatin1(),"wb");
    tPort = 6000;
    udpsocket = new QUdpSocket(this);
    udpsocket->bind(QHostAddress::Any, tPort);
    init();
}

receiver::~receiver()
{
    delete ui;
}

void receiver::init(){
    connect(udpsocket, SIGNAL(readyRead()),this, SLOT(rcvpkt()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(timeout_handler()));
    ui->progressBar->reset();
    flag=1;
    timer.stop();
    ui->progressBar->setMaximum(filesize);
}



void receiver::timeout_handler() {
    timer.stop();
    flag=0;
    QMessageBox::information(NULL,"提示","接收超时");
    close();
}


void receiver::rcvpkt(){

    char pkt_buf[sizeof(struct packet)];
    QHostAddress senderaddr;
    quint16 senderport;
    struct ack_packet ack;
    struct packet *pkt=NULL;
    if(expected_num==0) alltime.start();
    while(udpsocket->hasPendingDatagrams()&&flag==1)
    {
        udpsocket->readDatagram((char*)&pkt_buf,(qint64)sizeof(struct packet),&senderaddr,&senderport);
        /*if(senderaddr!=senderip)
            continue;*/
        pkt = (struct packet *) pkt_buf;
        if(pkt->len > sizeof(struct packet)) {
            fclose(output);
            QMessageBox::information(NULL,"提示","接收出错");

            close();
            break;
        }
        if(pkt->seqnum == (unsigned int)expected_num ) {
            int data_size = pkt->len - 6;
            fwrite(pkt->data,data_size,1,output);
            expected_num++;
        }
        /*send ACK*/

        ack.acknum = expected_num-1;
        ack.len = 6;

        udpsocket->writeDatagram((char *)&ack,sizeof(struct ack_packet),senderip,tPort+1);
        qDebug("ack==%d",ack.acknum);
        timer.start(8000);
    }
    bytesReceived=ftell(output);//ftell 用于得到文件位置指针当前位置相对于文件首的偏移字节数

    ui->progressBar->setValue(bytesReceived);
    ui->progressBar->setFormat("%p%");
    if(bytesReceived>=filesize){
        udpsocket->readAll();
        if(output)
        {
            fclose(output);
            output=0;
        }
        ack.len = 0;
        flag=0;
        udpsocket->writeDatagram((char *)&ack,sizeof(struct ack_packet),senderip,tPort+1);
        udpsocket->writeDatagram((char *)&ack,sizeof(struct ack_packet),senderip,tPort+1);
        udpsocket->writeDatagram((char *)&ack,sizeof(struct ack_packet),senderip,tPort+1);
        QTime endtime;
        endtime.start();
        QString v="接收完成，平均速率:"+QString::number(filesize/(alltime.msecsTo(endtime)))+"KB/S";
        QMessageBox::information(NULL,"提示",v);
        //if(endtime>5000)
             close();
    }
}

void receiver::closeEvent(QCloseEvent *)
{
    if(output) fclose(output);
    output=0;
    flag=0;
    timer.stop();
    delete udpsocket;
    close();
}
