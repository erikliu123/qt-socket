//personaldialog.h
#pragma once
#ifndef PERSONALDIALOG_H
#define PERSONALDIALOG_H
#include <QDialog>
#include <QTcpSocket>
#include <QUdpSocket>
//#include <QNetworkInterface>
#include <QVector>

namespace Ui {
    class p2p;
}
/*
struct{
    QString name,date,message;
}unstoreMessage;*/

class PersonalDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PersonalDialog(QWidget *parent = 0,QTcpSocket *_tcp=0,QString _oppositeName=0,QString _selfName=0, QMap<QString,PersonalDialog*> *_list=0);
    ~PersonalDialog();

    QString oppositeName;
    void setNameText(QString name);
    void closeEvent(QCloseEvent *);
    void getMessage(QString name,QString message);
    void getMessageWithNoHead(QString name,QString message);
    void changeSocket(QTcpSocket *s);   //修改TCP 套接字是必须的，因为要往正确的tcp发送信息！（tcp->write）

private slots:
    // void on_filesender_clicked();// send file
    void on_pushButton_send_clicked();

    //    void on_pushButton_sendFile_clicked();


    void on_pushButton_send_2_clicked();

    void on_pushButton_send_3_clicked();

private:
    QVector<QString> unStoreMes;
    /*recvfiles *receive;
    sendfiles *sender;*/

    Ui::p2p *ui;
    QTcpSocket *mytcp;
    QUdpSocket *myudp;
    QString selfName;
    QMap<QString,PersonalDialog*> *mylist;

public:
    QString messageStr;
    int messageLen,areadyRecv;
     QString dir_str = "D:/1_chat/";//默认路径
};

#endif // PERSONALDIALOG_H
