#include "senders.h"
#include "ui_senders.h"
#include <QDebug>
#include <QMessageBox>

#include <cstring>
#include <fstream>
#include <stdint.h>
//#include <sys/time.h>
#include <cstdlib>

#include <iostream>
//#include <QMainWindow>
#define udport 6000
#define data_size 800
using namespace std;
namespace Ui {
class senders;
}
//connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessages()));
senders::senders(QWidget *parent,const QHostAddress &hip,const QString &fileName,long int len) ://QDialog(parent),//���󣡣���
    QDialog(parent),
    ui(new Ui::senders)
{
    ui->setupUi(this);
    setFixedSize(500,210);
    udpport= udport;
    base=0;//����ȱ��
    bytesSend=0;resend_base=0;
    sending_window_size=80;
    hostip=QHostAddress(hip);

    input=fopen(fileName.toLatin1(), "rb");
    filesize=len;
    timepass=0;
    ack_time.start();
    if(!input)
    {
        QMessageBox::information(NULL,"��ʾ","�ļ���ȡʧ��");

        close();
    }
    udpsocket = new QUdpSocket(this);

    udpsocket->bind(QHostAddress::Any, udport+1);
    connect(udpsocket, SIGNAL(readyRead()),this, SLOT(recv_ack()));//recv_ack�����s
//connect(this, SIGNAL(sendName(QString)), dialog, SLOT(showName(QString)));
    ui->progressBar->reset();
    ui->progressBar->setMaximum(filesize);
    //this->init();
}
senders::~senders(){

    delete ui;
}

void senders::init()
{
    udpsocket = new QUdpSocket(this);

    udpsocket->bind(QHostAddress::Any, udport+1);
    connect(udpsocket, SIGNAL(readyRead()),this, SLOT(recv_ack()));//recv_ack�����s

    ui->progressBar->reset();
    ui->progressBar->setMaximum(filesize);
}

void senders::send(int i) {
    int index = i%sending_window_size;
    // qDebug()<<hostip<<udpport;
   // qDebug("senders::send index=%i ",index);

    udpsocket->writeDatagram((char *)&pkts[index],sizeof(struct packet),hostip,udpport);//���ļ�
    while (udpsocket->waitForBytesWritten()) {
    }
}

void senders::closeEvent(QCloseEvent *)
{
    flag=0;
    //timer.stop();
    fclose(input);
    free(pkts);
    close();
}

void senders::resend() {
    duplicate= 0;

    resend_base = min(base + sending_window_size, next_seqnum);

    for(int i=base; i<resend_base; i++) {//�ش�������İ�
        send(i);
    }
    ack_time.start();
}


void senders::recv_ack() {
    /*wait for ACKs*/
    qDebug("recv_acks ");
    char ack_buf[6];
    QHostAddress sender;
    quint16 senderPort;
    while(udpsocket->hasPendingDatagrams()){
        int n = udpsocket->readDatagram((char*)&ack_buf,(qint64)sizeof(struct ack_packet),&sender,&senderPort);//recvfrom(new_sock,ack_buf,sizeof(struct ack_packet),0,(struct sockaddr *)&from,&fromlen);
       /* if (n < 0||sender!=hostip)  {//sender!=hostip
            qDebug()<<sender<<hostip;
            return ;
        }*/
        qDebug()<<sender<<hostip;
        struct ack_packet *ack = (struct ack_packet *) ack_buf;

        if(ack->len == 6)
        {
            if(ack->acknum < (unsigned int)base) {
                if(ack->acknum != (unsigned int)lastsend) { //if duplicate ack was sent but for a newly lost pkt
                    duplicate ++;
                }
                if(duplicate >= 3) {
                    lastsend = ack->acknum;
                    resend();
                }
            } else {
                //sending_window_size = min(MAX_WINDOW_SIZE, sending_window_size*2);//min(MAX_WINDOW_SIZE, sending_window_size+1);


                if(resend_base != 0 && resend_base < next_seqnum) {
                    int indx = sending_window_size - (resend_base - (base+1));

                    indx = min(resend_base+indx, next_seqnum);
                    for(int i=resend_base; i<indx; i++) {//Send pcks!!
                        send(i);
                    }
                    resend_base = indx;
                }
            }
            bytesSend += data_size;
            timeout_counter=0;
            QCoreApplication::processEvents();
            base = ack->acknum + 1;

            qDebug("base=%d,  ack=%d",base,ack->acknum);
            ack_time.start();
        }

        else if(ack->len==0)//�յ�����Ϊ0�Ľ���
        {
            flag=0;
            QTime temp;
            temp.start();
            QString out="������ɣ�ƽ������Ϊ"+QString::number(filesize/(alltime.msecsTo(temp)))+"KB/S";
            QMessageBox::information(NULL,"��ʾ",out);
            close();
        }
    }
    ui->progressBar->setValue(bytesSend);
    ui->progressBar->setFormat("%p%");
    return;
}



void senders::gbn() {

    char buff[data_size];
    flag=1;//������Ǳ����ļ������Ƿ����
    struct packet pkt;
    QTime curtime;
    memset(buff,0,data_size);
    int length = fread(buff, 1, data_size, input);

    char buff_next[data_size];
    memset(buff_next,0,data_size);

    //int length_next = fread(buff_next, 1, data_size, input);
    int length_next=length;
    remaining_chunks = length_next;
    pkts= (struct packet *)malloc(sending_window_size*sizeof(struct packet));

    ack_time.start();//ĳ��packet�Ƿ���û�г�ʱ
    alltime.start();//�����ļ����ܼ�ʱ

    while(length > 0&&flag==1){
        QCoreApplication::processEvents();
        //if(udpsocket->hasPendingDatagrams()) recv_ack();
        curtime.start();
        timepass=ack_time.msecsTo(curtime);


        if(timepass>=5000){
            qDebug("wait too long");
            resend();
            continue;
        }
        if((resend_base == next_seqnum) && next_seqnum < base+sending_window_size) {
            pkt.len = length + 6;
            pkt.seqnum = next_seqnum;
            memcpy(pkt.data, buff, data_size);//copy to data

            pkts[next_seqnum%sending_window_size] = pkt;

            send(next_seqnum);//����
            if(next_seqnum == base)
            {
                timeout_counter=0;
                ack_time.start();
            }
            next_seqnum++;
            resend_base++;
            memset(buff,0,data_size);
            memcpy(buff, buff_next, length_next);
            length = length_next;
            memset(buff_next,0,data_size);
            length_next = fread(buff_next, 1, data_size, input);
            remaining_chunks = length_next;
        }

    }
    return ;
}
