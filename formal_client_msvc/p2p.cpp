//personaldialog.cpp

#include "p2p.h"
#include "ui_p2p.h"
#include <QDebug>
#include <QMap>
#include <QMessageBox>
#include <QDir>
#include <QTextCodec>
#include <QDateTime>


/*
 *
 #ifndef ABC_H
 #define ABC_H
 */


PersonalDialog::PersonalDialog(QWidget *parent,QTcpSocket *_tcp,QString _hisname,QString _selfName,  QMap<QString,PersonalDialog*> *list) :
    QDialog(parent),mytcp(_tcp),oppositeName(_hisname),selfName(_selfName),mylist(list),
    ui(new Ui::p2p)
{
    ui->setupUi(this);
    this->setWindowTitle(tr(oppositeName.toUtf8()+"     私聊窗口"));
    // this->setWindowTitle(tr(oppositeName));
    //connect(tcp,SIGNAL(readyRead()),this,SLOT(readIpAndPort()));
    messageLen=0;areadyRecv=0;
    ui->textEdit->setReadOnly(true);
    connect(ui->pushButton_send_3,SIGNAL(clicked()),this,SLOT(on_pushButton_send_3_clicked()));

}

//TODO：改变tcp的东西

PersonalDialog::~PersonalDialog()
{
    mytcp->close();
    delete ui;
}

void PersonalDialog::on_pushButton_send_clicked()//发送信息
{
    QString ds1=ui->textEdit_2->toHtml();
    ui->textEdit_2->clear();
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString header="\t\t"+time.toString("yyyy-MM-dd hh:mm:ss")+" \n";//发送人+消息存储

    ui->textEdit->append("<font color=#EE0000> "+selfName + header + ds1+"</font>");
    //ui->textEdit->append(data1);

    QString ds2="d+"+selfName+"+"+oppositeName+"+"+ds1;
    unStoreMes.push_back("<font color=#EE0000> "+selfName + header + ds1+"</font>");
    // mytcp->write(ds2.toUtf8());
    QString data="privatechat+"+selfName+"+"+ QString::number(ds1.length()) +"+"+ds1;
    mytcp->write(data.toUtf8());
}

/*void PersonalDialog::on_filesender_clicked()//发送信息
{

        receiver=new recvfiles;

        if(send)delete send;
        send=0;
        if(rec)delete rec;
        rec=0;
        qDebug()<<Tip<<Tport<<filename<<length;
        sender = new sendfiles(this,Tip,filename,length);//文件发送
        sender->show();
        qDebug()<<"send is called";

        sender->gbn();
        qDebug()<<"gbn is called"

}*/

/*void PersonalDialog::on_pushButton_sendFile_clicked()
{

    qDebug()<<"waiting for sending files";
     Client *myclient=new Client(this);
     myclient->show();
     QString str1=ui->lineEdit_name->text();
     QString senddata="inquiry#"+str1;
     tcp->write(senddata.toLatin1());
}*/
/*void PersonalDialog::readIpAndPort()
{
    int i;
    QByteArray temp=tcp->readAll();
    QString data=QString::fromLocal8Bit(temp);
    qDebug()<<data;
    QStringList list=data.split("#");
    QString str1=list[0];
    qDebug()<<str1;
}*/


void PersonalDialog::getMessage(QString name, QString message)//得到信息
{
    setNameText(name);
    areadyRecv+=message.length();
    messageStr+=message;

    if(areadyRecv>=messageLen){
        QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
        QString data="\t\t"+time.toString("yyyy-MM-dd hh:mm:ss");//发送人+消息存储
        ui->textEdit->append("<font color=#00CDCD> "+oppositeName + data +messageStr+"</font>");//light blue
        unStoreMes.push_back("<font color=#00CDCD> "+oppositeName + data +messageStr+"</font>");
        messageStr="";
        messageLen=0;areadyRecv=0;
    }

    //ui->textEdit->append(message);
}
void PersonalDialog::getMessageWithNoHead(QString name,QString message)
{
    getMessage("",message);
    //ui->textEdit->append(message);
}

void PersonalDialog::changeSocket(QTcpSocket *s)
{
    //修改TCP 套接字是必须的，因为要往正确的tcp发送信息！（tcp->write）
        mytcp->close();
        mytcp=s;


}

//名字只读
void PersonalDialog::setNameText(QString name)
{
    ui->lineEdit_name->clear();
    ui->lineEdit_name->setReadOnly(true);
    ui->lineEdit_name->append(name);

}

//窗口关闭后删除该该用户
void PersonalDialog::closeEvent(QCloseEvent *){

    QMap<QString,PersonalDialog*>::iterator it;
    for (it = mylist->begin();it != mylist->end(); it++)
    {
        QString num = it.key();
        qDebug() << "the current number is " << num;
        if (num  == oppositeName)
        {
            mylist->erase(it);
            qDebug() << "erase number : " << num;
            break;
        }

    }
    // *mylist->erase(oppositeName);
    close();
}


void PersonalDialog::on_pushButton_send_2_clicked()//聊天记录导出
{
    // 检查目录是否存在，若不存在则新建
    QDir dir;
    if (!dir.exists(dir_str))
    {
        bool res = dir.mkpath(dir_str);
        qDebug() << "新建目录是否成功" << res;
        if(!res){
            QMessageBox::information(this,"错误",dir_str+" 创建失败！",QMessageBox::Ok);

            return ;
        }
    }

    QString filename=selfName+"__"+oppositeName;
    QFile chat(dir_str+filename);//,QIODevice::Append

    if(!chat.open(QIODevice::Append))
    {
        QMessageBox::information(NULL,"提示","聊天文件读取失败！");
        return;
    }
    while(!unStoreMes.empty()){
        chat.write(unStoreMes[0].toUtf8());
        unStoreMes.pop_front();
    }
    //chat.write(ui->textEdit->toHtml().toUtf8());//打开文件应该以UTF8打开，否则GBK会乱码
    chat.close();
    QMessageBox::information(this,"提示","聊天文件成功导出！");// QMessageBox::information(NULL 有问题！！

}

void PersonalDialog::on_pushButton_send_3_clicked()
{
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
    QString filename=selfName+"__"+oppositeName;
    QFile file(dir_str+filename);//,QIODevice::Append
    //指定为UTF-8
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");

    //如果打开文件失败,直接退出
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        return;
    QString str;
    //当未到达文件结束位置
    while(!file.atEnd())
    {
        //读取一行文本数据
        QByteArray line = file.readLine();

        //将读取到的行数据转换为Unicode
         str+= codec->toUnicode(line,line.length());
        //将得到的字符设置到编辑框中显示

    }
    //TODO:没有记录的消息有哪些？
     ui->textEdit->clear();//把前面的消息清空，防止重复记录.最好加一个list记录本次登录传递的的消息，先把未记录的消息刷到本地文件！
     ui->textEdit->append(str);

     for(QVector<QString>::iterator it=unStoreMes.begin(); it!=unStoreMes.end() ;++it){
        ui->textEdit->append(*it);
     }

}
