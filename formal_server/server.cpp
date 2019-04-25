//tcpserver.cpp
#include "server.h"
#include "ui_tcpserver.h"
#include "db.h"
#include <QCryptographicHash>
#include <QDateTime>
#include <QMutex>
#pragma execution_character_set("utf-8")
QMutex userMessageMutex;
const int port=5050; //服务器的监听端口
qint16 vport=6120;//UDP传输文件的端口

QString  MesLog  =  "a";//请求注册
QString  MesLogin   =  "b";//请求登录
QString  SbLogin="c";
QString  MesLogError   = "d";//注册失败
QString  MesLogSuc   =  "e";//注册成功

QString  forgetpass   =  "forget";//忘记密码
QString  modifypass   =  "hhh";//修改密码

QString  LoginSuc   =  "f";//登录成功
QString  Loginerror =  "g";//登录失败
QString  SbCreatServer= "server";//创建新服务端

QString   MesError   =  "i";
QString   FileSend = "j";
QString  MesNormal  =  "k";//单人
QString   MesToAll   =  "l";//全体
QString   OnLineUser =  "m";
QString   FIN="z";

TcpServer::TcpServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcpServer)
{
    ui->setupUi(this);
    this->tcpServer=new QTcpServer(this);
    //connect(tcpServer,SIGNAL(newConnection()),this,SLOT(newConnect()));
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
    connect(this,SIGNAL(userNumChange()),this,SLOT(sendUserList()));
    QMysql=new MySql(SQL::MYSQL);
    connect(this,SIGNAL(sbLogin()),this,SLOT(sendUsertcp()));
}

void TcpServer::acceptConnection()
{
    QTcpSocket *tcp=tcpServer->nextPendingConnection();//多个监听端口
    QString ip=tcp->peerAddress().toString();
    int port=tcp->peerPort();
    qDebug()<<ip<<port;
    //tcp->write(ip.toUtf8());
    connect(tcp,SIGNAL(readyRead()),this,SLOT(readData()));   //**********

}
std::string TcpServer::gethostMac()
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
    return strMacAddr.toStdString();
}
TcpServer::~TcpServer()
{
    tcpServer->close();
    delete ui;
}
bool TcpServer::checkHasSign(QString name, QString passward,QString mail)
{
    MySql *mysql=new MySql();

    QByteArray Pwdname=name.toUtf8();
    QByteArray PwdnameMd5=QCryptographicHash::hash(Pwdname,QCryptographicHash::Md5);
    QString nameMd5=PwdnameMd5.toHex();

    QByteArray Pwdpassward=passward.toUtf8();
    QByteArray PwdpasswardMd5=QCryptographicHash::hash(Pwdpassward,QCryptographicHash::Md5);
    QString passwardMd5=PwdpasswardMd5.toHex();

    bool ret=mysql->signup(nameMd5,passwardMd5,mail);
    return ret;
}
bool TcpServer::checkExist(QString name)
{
    MySql *mysql=new MySql();

    QByteArray Pwdname=name.toUtf8();

    QByteArray ass=name.toUtf8();

    QByteArray PwdnameMd5=QCryptographicHash::hash(Pwdname,QCryptographicHash::Md5);
    QString nameMd5=PwdnameMd5.toHex();
    qDebug()<<"UTF-8:"<<ass;
    qDebug()<<Pwdname<<nameMd5;
    bool ret=mysql->exist(nameMd5);

    return ret;
}

void TcpServer::removeUserFormList()
{
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    tcpMAC.remove(socket);

    userMessageMutex.lock();
    QString name=userMessage[socket];
    QList<QListWidgetItem*> list;
    list=ui->listWidget->findItems(name,Qt::MatchCaseSensitive);
    QListWidgetItem *sel=list[0];
    int r=ui->listWidget->row(sel);
    QListWidgetItem *item=ui->listWidget->takeItem(r);
    ui->listWidget->removeItemWidget(item);
    delete item;


    userMessage.remove(socket);//此处已经有了remove！//tcp和用户的映射
    userMessageMutex.unlock();
    socket->close();
    usertcp.remove(name);

    emit userNumChange();
}

void TcpServer::sendUsertcp()//用户创建自己的服务器时使用
{

    QMap<QString,  socket>::iterator tempp=usertcp.begin();
    QMap<QTcpSocket*,QString>::iterator it=userMessage.begin();
    QString message="";
    while(tempp!=usertcp.end()){
        qDebug()<<"loop usertcp::  "<<tempp.key()<<tempp.value().theip<<tempp.value().port;
        ++tempp;
    }
    QMap<QString,  socket>::iterator temp;
    socket s;
    temp=usertcp.begin();
    while(temp!=usertcp.end()){
        s=temp.value();
        //intochar=QString::number(s.port);
        message=message + SbCreatServer + "+" + temp.key()+ "+" + s.theip + "+" +QString::number(s.port)+"+";
        ++temp;
        qDebug()<<message;
    }
    it=userMessage.begin();
    while(it!=userMessage.end()){
        it.key()->write(message.toUtf8());

        qDebug()<<"-->"<<it.value()<<"  usertcp::  "<<message;
        it++;

    }

}

void TcpServer::sendUserList()
{
    QString message="d";

    userMessageMutex.lock();
    QMap<QTcpSocket*,QString>::iterator it=userMessage.begin();
    while(it!=userMessage.end())
    {
        message+="+";
        message+=it.value();
        ++it;
    }
    if(message=="d"){
        //需要释放锁
        userMessageMutex.unlock();
        return;
    }
    it=userMessage.begin();
    while(it!=userMessage.end())
    {
        it.key()->write(message.toUtf8());
        ++it;
    }
    userMessageMutex.unlock();
    qDebug()<<"sendUserList:    "<<message;
}


bool TcpServer::checkSignIn(QString name,QString passward)
{
    MySql *mysql=new MySql();

    QByteArray Pwdname=name.toUtf8();
    QByteArray PwdnameMd5=QCryptographicHash::hash(Pwdname,QCryptographicHash::Md5);
    QString nameMd5=PwdnameMd5.toHex();

    QByteArray Pwdpassward=passward.toUtf8();
    QByteArray PwdpasswardMd5=QCryptographicHash::hash(Pwdpassward,QCryptographicHash::Md5);
    QString passwardMd5=PwdpasswardMd5.toHex();

    bool ret=mysql->loguser(nameMd5,passwardMd5);//加密， 检查登录是否匹配
    if(ret)
    {
        ui->listWidget->addItem(name);//界面加入用户名字
    }
    return ret;

}

bool TcpServer::checkMail(QString name,QString mail)
{
    MySql *mysql=new MySql();

    QByteArray Pwdname=name.toUtf8();
    QByteArray PwdnameMd5=QCryptographicHash::hash(Pwdname,QCryptographicHash::Md5);
    QString nameMd5=PwdnameMd5.toHex();

    bool ret=mysql->checkmail(nameMd5,mail);
    qDebug()<<ret;
    return ret;
}

bool TcpServer::checkReset(QString name,QString newpass)
{
    MySql *mysql=new MySql();

    QByteArray Pwdname=name.toUtf8();
    QByteArray PwdnameMd5=QCryptographicHash::hash(Pwdname,QCryptographicHash::Md5);
    QString nameMd5=PwdnameMd5.toHex();

    QByteArray Pwdpassward=newpass.toUtf8();
    QByteArray newpwdMd5=QCryptographicHash::hash(Pwdpassward,QCryptographicHash::Md5);
    QString passMd5=newpwdMd5.toHex();

    bool ret=mysql->reset(nameMd5,passMd5);
    qDebug()<<ret;
    return ret;
}

void TcpServer::on_closeBtn_clicked()
{
    ui->startBtn->setEnabled(true);
    ui->closeBtn->setEnabled(false);
    qDebug()<<"ok,ready for close";
    //ui->close();
    tcpServer->close();
    //qDebug()<<"ok,ready for close";
}



void TcpServer::readData()
{
    QTcpSocket *tempTcp=static_cast<QTcpSocket*>(sender());//多个接受端
    QString data=tempTcp->readAll();
    qDebug()<<data;
    QStringList list=data.split("+");
    bool ret=0;
    bool flag=0;
    /*
     * QString  MesLog  =  "a";//请求注册
    QString   MesLogin   =  "b";//请求登录
    QString  SbLogin="c";
    QString   MesLogError   = "d";//注册失败
    QString   MesLogSuc   =  "e";//注册成功

    QString   forgetpass   =  "forget";//忘记密码
    QString  modifypass   =  "hhh";//修改密码

    QString  LoginSuc   =  "f";//登录成功
    QString  Loginerror =  "g";//登录失败
    QString  = "h";//创建新服务端
     * */
    if(list[0]==MesLog) {
        ret=checkHasSign(list[1],list[2],list[3]);
        qDebug()<<"i check sign up";
    }//注册
    else if(list[0]=="mac"){

        if(tcpMAC.contains(tempTcp)) tcpMAC.remove(tempTcp);
        tcpMAC.insert(tempTcp,list[1]);
        if(QMysql->checkMAC(list[1])==false){
            QString lockscreen="lock+";
            tempTcp->write(lockscreen.toUtf8());
        }

    }
    else if(list[0]=="leave"){
        /** userMessageMutex.lock();
           userMessage.remove(tempTcp);// tempTcp被移走后，会导致登录时的connect自爆？ connect(tempTcp,SIGNAL(disconnected()),this,SLOT(removeUserFormList()));
            userMessageMutex.unlock();*/
        qDebug()<<"remove(tempTcp)";
        //emit userNumChange();// connect(this,SIGNAL(userNumChange()),this,SLOT(sendUserList()));
        //tempTcp->abort();
        qDebug()<<"abort();";
        return ;

    }
    else if(list[0]==MesLogin)  //登录
    {
        ret=checkSignIn(list[1],list[2]);

        if (ret)
        {
            //TODO:
            //这个list[1]应该唯一
            userMessage.insert(tempTcp,list[1]);//TCP+用户名
            connect(tempTcp,SIGNAL(disconnected()),this,SLOT(removeUserFormList()));
            QMysql->updateMAC(tcpMAC[tempTcp],true);
            //用户断开连接时发出信号刷新服务器用户列表
            //相当于java 的？ await状态？
        }
        else{
            QMysql->updateMAC(tcpMAC[tempTcp],false);
            if(QMysql->checkMAC(tcpMAC[tempTcp])==false){
                QString lockscreen="lock+";
                tempTcp->write(lockscreen.toUtf8());
                return ;
            }

        }

    }
    else if(list[0]==SbCreatServer){//记录下IP + port， TODO:客户端应当更新<用户名， socket>键值对
        socket *temp=new socket;
        quint16 w;
        w=(quint16)list[3].toInt();

        *temp={list[2],w};

        //QMap<QString,  socket>::iterator tt=usertcp.begin();
        usertcp.insert(list[1],*temp);//list[1]可能重复，重新登录了
        sendUsertcp();
        qDebug()<<"SbCreatServer"<<(*temp).theip<<(*temp).port;

    }

    else if(list[0]==forgetpass){//请求重置密码
        bool ret=checkMail(list[1],list[2]);//用户名+邮箱
        QString temp;
        if(ret){
            temp=forgetpass +'+' +list[1]+"+true+";
            tempTcp->write(temp.toUtf8());

        }
        else {
            temp=forgetpass +'+' + list[1]+"+false+";
            tempTcp->write(temp.toUtf8());
        }
        qDebug()<<temp;


    }
    else if(list[0]==modifypass)//重置密码
    {
        QString temp;
        bool ret=checkReset(list[1],list[2]);
        if(ret){
            temp=modifypass+'+'+list[1]+"+true+";
            tempTcp->write(temp.toUtf8());
        }
        else {
            temp= modifypass +'+'+ list[1]+"+false+";
            tempTcp->write(temp.toUtf8());
        }
        qDebug()<<temp;


    }


    else if(list[0]=="c")//发送离线消息
    {
        bool flag1=0;
        QString Message1="c+false";
        ret=checkExist(list[2]);
        qDebug()<<"checkExist:"<<ret;
        QMap<QTcpSocket*,QString>::iterator it=userMessage.begin();
        while(it!=userMessage.end())
        {
            if(it.value()==list[2])
            {
                flag1=1;
                break;
            }
            ++it;
        }
        if(ret&&!flag1)//用户存在但离线
        {
            QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
            QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd"); //设置显示格式
            QString data=list[1]+"+\t\t"+str+" \n:"+list[3];//发送人+消息存储
            qDebug()<<"离线消息："<<data;
            QFile file(list[2]+".txt");
            if(file.open(QIODevice::Text|QIODevice::WriteOnly|QIODevice::Append)){//写入文件
                QTextStream stream( &file );
                stream <<data<<"\n";
            }
            file.close();
            return;
        }
        else//用户在线
        {
            if(flag1){
                Message1="c+online";
                flag1=0;
            }
            qDebug()<<Message1<<flag;
            tempTcp->write(Message1.toUtf8());

            return;
        }
        return;
    }

    else if(list[0]=="d")//这个不是点对点通信，是在线服务器转接信息,TODO:DELETE
    {

        QMap<QTcpSocket*,QString>::iterator it=userMessage.begin();
        QTcpSocket *tcp=NULL;
        while(it!=userMessage.end())
        {
            if(it.value()==list[2])
            {
                tcp=it.key();
                break;
            }
            ++it;
        }
        if(tcp==NULL)
            return;
        QString mes="e+"+list[1]+"+"+list[2]+"+"+list[3];//不大理解？？send pri
        qDebug()<<mes;
        tcp->write(mes.toUtf8());
        return;
    }

    else if(list[0]=="e")//用户刷新列表
    {
        qDebug()<<"sendUserList ";
        sendUserList();
        return;
    }

    else if(list[0]=="f")//发送离线信息 f+(发送人，时间，消息)
    {
        QMap<QTcpSocket*,QString>::iterator it=userMessage.begin();
        QTcpSocket *tcp=NULL;
        while(it!=userMessage.end())
        {
            if(it.value()==list[1])
            {
                tcp=it.key();
                break;
            }
            ++it;
        }

        if(tcp==NULL){
            return;
        }
        QByteArray datasend;
        QString filename=list[1]+".txt";
        QFile file(filename);
        if ( file.open(QIODevice::ReadOnly) ) {
            qDebug()<<"open the file";
            QTextStream stream( &file );
            QString line;
            while ( !stream.atEnd() ) {
                line = stream.readLine();
                datasend="f+"+line.toUtf8()+"+";
                qDebug()<<datasend;
                tcp->write(datasend);
                while(!tcp->waitForBytesWritten()){
                }
            }
            file.close();
            //file.open(QIODevice::WriteOnly);
            //file.close();
        }
        return;
    }

    /*inquiry + 用户名*/
    else if(list[0]=="inquiry")//获取对方的UDP！
    {
        QMap<QTcpSocket*,QString>::iterator it=userMessage.begin();
        QTcpSocket *tcp=NULL;//新的tcp

        while(it!=userMessage.end())
        {
            if(it.value()==list[1])
            {
                tcp=it.key();
                break;
            }
            ++it;
        }

        if(tcp==NULL){
            return;}

        QString sen1=tempTcp->peerAddress().toString();
        QString sen2=QString("%1").arg(tempTcp->peerPort());

        QString receive="inquiry+"+sen1+"+"+sen2;//地址 + 端口

        tcp->write(receive.toUtf8());//接收方收到发送方的地址+端口

        QString str1=tcp->peerAddress().toString();
        QString str2=QString("%1").arg(tcp->peerPort());
        QString messages="g+"+str1+"+"+str2;//地址 + 端口
        qDebug()<<messages;

        tempTcp->write(messages.toUtf8());//发送方收到接受方的地址+端口
        return;
    }
    else if(list[0]=="file")
    {
        QMap<QTcpSocket*,QString>::iterator it1=userMessage.begin();
        QTcpSocket *tcp1=NULL;
        while(it1!=userMessage.end())
        {
            if(it1.value()==list[1])
            {
                tcp1=it1.key();//得到对方的socket
                break;
            }
            ++it1;
        }
        QString fileinfo="h+"+list[2]+"+"+list[3]+"+";//向list[2]发送文件名
        qDebug()<<fileinfo;
        if(tcp1==NULL)
        {
            qDebug()<<"error occur!";
            return;
        }
        else
            tcp1->write(fileinfo.toUtf8());//文件基本信息的可靠传输
        return;
    }
    else
        return;
    //QString sendData=list[0];//原封不动，发送该指令的真假
    QString sendData;
    if(list[0]==MesLog || list[0]==MesLogin){
        if(ret){
            if(list[0]==MesLogin){
                QString vportchar;
                vportchar=QString::number(vport);
                ++vport;
                sendData=list[0]+"+"+list[1]+"+true+" +vportchar;
            }
            else{
                sendData=list[0]+"+"+list[1]+"+true";
            }


        }


        else
        {
            sendData=list[0]+"+"+list[1]+"+false";
        }
        qDebug()<<ret<<" "<<sendData;
        tempTcp->write(sendData.toUtf8());
    }



}

void TcpServer::on_startBtn_clicked()
{
    ui->startBtn->setEnabled(false);
    ui->closeBtn->setEnabled(true);
    if(!tcpServer->listen(QHostAddress::Any,port))
    {
        qDebug()<<tcpServer->errorString();
        close();
        return;
    }
    else{
        qDebug()<<"ok, listening";
    }
}







