//tcpclient.cpp
#include "tcpclient.h"
#include "ui_tcpclient.h"
#include "userUi.h"
#include <QDebug>
#include <cstdio>
//#include <mem.h>
//#define ip "222.20.104.43"
QString  MesLog  =  "a";//请求注册
QString   MesLogin   =  "b";//请求登录
QString  SbLogin="c";
QString   MesLogError   = "d";//注册失败
QString   MesLogSuc   =  "e";//注册成功

QString   forgetpass   =  "forget";//忘记密码
QString  modifypass   =  "hhh";//修改密码

QString  LoginSuc   =  "f";//登录成功
//QString  Loginerror =  "g";//登录失败
//QString  SbCreatServer= "server";//创建新服务端

QString   MesError   =  "i";
QString   FileSend = "j";
QString  MesNormal  =  "k";//单人
QString   MesToAll   =  "l";//全体
QString   OnLineUser =  "m";
QString   FIN="z";

QString ip="222.20.104.43";

using namespace std;
//#define ip "169.254.99.173"
qint16 port =5050;

TcpClient::TcpClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcpClient)
{
    readFlag=1;
    ui->setupUi(this);
    ui->passwardLineEdit->setEchoMode(QLineEdit::Password);  //密码方式显示文本
    init();

}

TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::init()
{
    tcpSocket=new QTcpSocket(this);
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));   //发生错误时执行displayError函数
}

void TcpClient::connectServer()
{
    tcpSocket->abort();   //取消已有的连接
    ip=ui->ServerIp->text();
    tcpSocket->connectToHost(ip,port);
    /*判断socket的有效性*/
    if(!tcpSocket->isValid()){

        QMessageBox::information(NULL,"Socket Error","&本地套接字无效！",QMessageBox::Ok);
        on_dislink_clicked();
        return ;
    }

    /*本地套接字正常，但是服务器异常或者未打开*/
    if(!tcpSocket->waitForConnected(10000))
    {
        QMessageBox::information(NULL, tr("Socket Error"), tr("连接服务端失败！"));
        on_dislink_clicked();

        return;
    }
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessages()));
    QString macaddr=gethostMac();
    macaddr="mac+"+macaddr+"+";
    tcpSocket->write(macaddr.toUtf8());

}
/*借鉴博客上得到MAC地址*/
QString TcpClient::gethostMac()
{
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();// 获取所有网络接口列表
    int nCnt = nets.count();
    QString strMacAddr = "";
    for(int i = 0; i < nCnt; i ++)
    {
        qDebug()<<nets[i].hardwareAddress();
        // 如果此网络接口被激活并且正在运行并且不是回环地址，则就是我们需要找的Mac地址
        if(nets[i].flags().testFlag(QNetworkInterface::IsUp) && nets[i].flags().testFlag(QNetworkInterface::IsRunning)
                && !nets[i].flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            strMacAddr = nets[i].hardwareAddress();
            break;
        }
    }
    return strMacAddr;
}

void TcpClient::on_link_clicked()
{
    ui->link->setEnabled(false);
    ui->dislink->setEnabled(true);
    connectServer();
}

void TcpClient::on_dislink_clicked()
{
    ui->dislink->setEnabled(false);
    ui->link->setEnabled(true);
    tcpSocket->abort();
}


void TcpClient::on_sendBtn_clicked()
{
    QString userName=ui->userLineEdit->text();
    QString passward=ui->passwardLineEdit->text();
    if(userName=="" || passward=="")
        QMessageBox::information(NULL,"warning","输入不能为空",QMessageBox::Ok);


    QString bs="b";
    QString data=bs+"+"+userName+"+"+passward;
    // connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readip()));
    tcpSocket->write(data.toUtf8());
}


void TcpClient::on_signBtn_clicked()
{
    QString u=ui->userLineEdit->text();
    QString pass=ui->passwardLineEdit->text();
    bool ok;
    QString mail=QInputDialog::getText(NULL,tr("填写密保验证"),
                                       tr("请输入密保邮箱"),
                                       QLineEdit::Normal,"例:123456789@qq.com",&ok);
    if(u=="" || pass==""||!ok||mail.isEmpty()){
        QMessageBox::information(NULL,"warning","输入不能为空",QMessageBox::Ok);
        return;
    }
    QString data="";
    //memset(data, 0x00, sizof(data));
    //memcpy(data, &MesLog, 2);//注册
    // QString as=MesLog;
    data=MesLog+"+"+u+"+"+pass+"+"+mail;
    tcpSocket->write(data.toUtf8());

}


void TcpClient::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<tcpSocket->errorString();   //输出出错信息
}


void TcpClient::readMessages()
{
    if(readFlag==0)
        return;
    QString data=tcpSocket->readAll();
    qDebug()<<data;

    QStringList list=data.split("+");
    if(list[0]=="a" && list[2]=="true")
        QMessageBox::information(NULL,"信息提示","注册成功!",QMessageBox::Ok);


    else if(list[0]=="a" && list[2]=="false")
        QMessageBox::information(NULL,"信息提示","注册失败,用户名已经被注册!",QMessageBox::Ok);


    else if(list[0]=="b" && list[2]=="true")
        //QMessageBox::information(NULL,"信息提示","登录成功!",QMessageBox::Ok);
    {
        qint16 pport=list[3].toInt();
        UserUi *user=new UserUi(this,tcpSocket,list[1],pport);


        this->close();//关闭当前的登录窗口
        user->show();
        readFlag=0;
    }

    else if(list[0]=="b" && list[2]=="false")
        QMessageBox::information(NULL,"信息提示","登录失败,用户名或密码错误!",QMessageBox::Ok);


    else if(list[0]==forgetpass && list[2]=="false")
        QMessageBox::information(NULL,"信息提示","重置失败，用户名不存在或密保填写错误！",QMessageBox::Ok);


    else if(list[0]==forgetpass && list[2]=="true")
    {
        reset(list[1]);
    }
    else if(list[0]==modifypass && list[2]=="true")
        QMessageBox::information(NULL,"信息提示","密码修改成功，请重新登陆!",QMessageBox::Ok);


    else if(list[0]==modifypass && list[2]=="false")
        QMessageBox::information(NULL,"信息提示","密码修改失败，请重试!",QMessageBox::Ok);
    else if(list[0]=="lock"){
        ui->centralWidget->setEnabled(false);
        QMessageBox::information(NULL,"已被锁屏","联系管理员QQ1171045702！",QMessageBox::Ok);
    }

    else
        return;
}



void TcpClient::on_resetpwdButton_clicked()
{
    bool ok;
    QString datt=QInputDialog::getText(NULL,tr("密保验证"),
                                       tr("请输入用户名+'+'+密保邮箱"),
                                       QLineEdit::Normal,"如:lisi+12345@qq.com",&ok);
    if(!ok||datt.isEmpty()){
        QMessageBox::information(NULL,"warning","输入不能为空",QMessageBox::Ok);

        return;
    }
    QString data= forgetpass+ "+"+datt;
    tcpSocket->write(data.toUtf8());
}

void TcpClient::reset(QString name)
{
    bool ok;

    QString newpwd=QInputDialog::getText(NULL,tr("重置密码"),
                                         tr("请输入新密码"),
                                         QLineEdit::Normal,"如:123456789",&ok);
    if(!ok||newpwd.isEmpty()){
        QMessageBox::information(NULL,"warning","输入不能为空",QMessageBox::Ok);

        return;
    }
    // QString as="a";

    QString data=modifypass+"+"+name+"+"+newpwd;
    tcpSocket->write(data.toUtf8());
}
