//UserUi.cpp
#include "userUi.h"
#include "ui_userUi.h"
#include <random>
#include <time.h>
#include <QTcpSocket>

#include <QMap>
#include <QSet>
#include <QMessageBox>

#include <QtNetwork>
#include <QTimer>

#include <QHostAddress>

#include <QUdpSocket>
#include <QHostInfo>
#include <QScrollBar>
#include <QDateTime>
#include <cstdio>
#include <QFileDialog>


/*QString  SbCreatServer= "h";//�����·����
QString   MesError   =  "i";
QString   FileSend = "j";
QString  MesNormal  =  "k";//����
QString   MesToAll   =  "l";//ȫ��
//QString   OnLineUser =  "m";
QString   FIN="z";*/



UserUi::UserUi(QWidget *parent,QTcpSocket *pTcpSocket,QString _name, qint16 _port) :
    QMainWindow(parent),tcpSocket(pTcpSocket),name(_name),myport(_port),
    ui(new Ui::UserInterface)
{
    QIcon icon("src/Me.png");
    setWindowIcon(icon);
    ui->setupUi(this);
    this->setWindowTitle("welcome, "+_name);
    this->setParent(parent);
    ui->textEdit->setReadOnly(true);
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessages()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(sendLeave()));
    myip=pTcpSocket->localAddress().toString();// ȡ�ͻ���IP
    // srand((unsigned short)time(NULL));
    //myport=6000+rand()%1000;

    qDebug()<<"myport and ip:"<<myport<<myip;

    //�����ͻ��˵ļ���
    this->person=new QTcpServer();
    if(!person->listen(QHostAddress::Any,myport))
    {
        qDebug()<<" port failure";
        close();
        return;
    }
    else qDebug()<<"successfully open my port";
    // connect(tcpSocket,SIGNAL(newConnection()),this,SLOT(acceptConnection()));//����

    connect(person,SIGNAL(newConnection()),this,SLOT(acceptConnection()));

    socket *s=new socket;
    s->theip=myip;
    s->port=myport;
    QString abc,b2;
    //b2=
    abc=QString::number(myport);
    //char b='+';
    //int len=sizeof(SbCreatServer)+sizeof(name)+2;
    QString a=SbCreatServer+"+"+name+'+'+myip+ "+"+ abc+ "+true+ " ;
    qDebug()<<a;

    tcpSocket->write(a.toUtf8());
    //tcpSocket->write(hh.toLatin1());


}

void UserUi::sendLeave(){
    QString leave="leave+"+name;

     tcpSocket->write(leave.toUtf8());
     tcpSocket->close();
     qDebug()<<leave;
}
void UserUi::closeEvent(QCloseEvent *){

    sendLeave();
    delete ui;
    // *mylist->erase(oppositeName);
    close();
}
void UserUi::acceptConnection()
{
    QTcpSocket *tcp=person->nextPendingConnection();//��������˿�

    QString ip=tcp->peerAddress().toString();
    int port=tcp->peerPort();
    qDebug()<<ip<<port;
    //tcp->write(ip.toLatin1());
    connect(tcp,SIGNAL(readyRead()),this,SLOT(readMessages3()));   //**********

}
void UserUi::opponentHasLeave(QString &name){//TODO���ر�tcpsocket
    const QString str=name+" �Ѿ�����";
    QMessageBox::information(NULL,"�Է�����",str,QMessageBox::Ok);
}

void UserUi::readMessages3(){
    QTcpSocket *tempTcp=static_cast<QTcpSocket*>(sender());//������ܶ�
    QString data=tempTcp->readAll();
    qDebug()<<"server UserUi::readMessages3 "<<data;
    //  QByteArray temp=tcpSocket->readAll();
    //QString data=QString::fromLocal8Bit(temp);

    QStringList list=data.split("+");
    if(list[0]=="privatechat"){
        connect(tempTcp,SIGNAL(disconnected()),this,SLOT(opponentHasLeave(list[1])));
        lastSendName=list[1];
        if(!pdList.contains(list[1]))
        {

            PersonalDialog *newdig=new PersonalDialog(this,tempTcp,list[1],name,&pdList);
            pdList.insert(list[1],newdig);
            newdig->show();
        }
       pdList[list[1]]->messageLen=list[2].toInt();
       qDebug("message len=%d", list[2].toInt());
       pdList[list[1]]->getMessage(list[1],getList(list));

    }
    else{

        //pdList[list[1]]->getMessageWithNoHead("",data);
        pdList[lastSendName]->getMessageWithNoHead("",data);
    }
}

QTcpSocket* UserUi::createP2PSocket(QString &str){
    QTcpSocket *temp=new QTcpSocket;
    socket ts=pp[str];
    QString ip;
    qint16 port;
    ip=QString(ts.theip);
    port=ts.port;
    temp->abort();   //ȡ�����е�����
    temp->connectToHost(ip,port);//hh�ǲ�����Ҫ�޸�
    qDebug()<<"createP2PSocket triggered";
    return temp;
}
QString UserUi::getList(QStringList &list){
    QString temp;
    for(int i=3;i<list.size();++i){
        temp+=list[i];
        if(i!=(list.size()-1)) temp+="+";
    }
    return temp;
}

UserUi::~UserUi()
{

    delete ui;
    qDebug()<<"exit user UI";

}
void UserUi::readMessages2(){/*���ຯ��*/

    QString data=hh->readAll();//���յ�ȫ����Ϣ
    qDebug()<<"client UserUi::readMessages2 "<<data;
    //  QByteArray temp=tcpSocket->readAll();
    //QString data=QString::fromLocal8Bit(temp);

    QStringList list=data.split("+");
    if(list[0]=="privatechat"){
        if(!pdList.contains(list[1]))
        {

            PersonalDialog *newdig=new PersonalDialog(this,hh,list[1],name,&pdList);
            connect(hh,SIGNAL(readyRead()),this,SLOT(readMessages2()));
            pdList.insert(list[1],newdig);
            newdig->show();
        }
        pdList[list[1]]->getMessage(list[1],getList(list));

    }
    else{
        pdList[list[1]]->getMessageWithNoHead(list[1],data);
    }

}

void UserUi::on_listWidget_doubleClicked(const QModelIndex &index)//�����´���
{

    QString str=onlineUser.at(index.row());  //��öԷ��û���
    //QString message="f+"+str;
    //tcpSocket->write(message.toLatin1());
    hh=new QTcpSocket;
    socket ts=pp[str];
    QString ip;
    qint16 port;
    ip=QString(ts.theip);
    port=ts.port;
    hh->abort();   //ȡ�����е�����
    hh->connectToHost(ip,port);

    qDebug()<<ip<<port;

    connect(hh,SIGNAL(readyRead()),this,SLOT(readMessages3()));
    PersonalDialog *temp=new PersonalDialog(this,hh,str,name,&pdList);
    //QMap<QString,PersonalDialog*> pdList;
    pdList.insert(str,temp);
    pdList[str]->show();
    pdList[str]->setNameText(str);
    //while(1) ;

}



//ֻ�ܷ���������Ϣ��
void UserUi::readMessages()
{
    int i;
    QByteArray temp=tcpSocket->readAll();
    //QString data=QString::fromLocal8Bit(temp);//��֧��UTF8!!
    QString data=QString::fromUtf8(temp);
    qDebug()<<"UserUi::readMessage"<<data;

    //QString data=tcpSocket->readAll();

    QStringList list=data.split("+");


    if(list[0]=="c")//�������Է���������Ϣ�Ļ�Ӧ
    {
        if(list[1]=="false"){
            ui->textEdit->append("-------������Ϣ����ʧ�ܣ��޸��û�");
            //QMessageBox::information(NULL,"����","���û�������",QMessageBox::Ok);
            //QMessageBox::information(NULL,"����","���û�������",QMessageBox::Ok);
            //QMessageBox::information(NULL,"����","���û�������",QMessageBox::Ok);
            //QMessageBox::information(NULL,"����","���û�������",QMessageBox::Ok);

        }
        else if(list[1]=="online")//��������Ϣ�����������˱�������
        {
            ui->textEdit->append("-------����Ҳ��û��б�˫��������������");
            // ui->textEdit->clear();
            QMessageBox::information(NULL,"����","���û�����",QMessageBox::Ok);
        }

    }

    else if(list[0]=="d")//���տͻ��б�
    {
        ui->listWidget->clear();
        onlineUser.clear();
        for(int i=1;i<list.size();i++)
        {
            if(list[i]==name)
                continue;
            ui->listWidget->addItem(list[i]);
            onlineUser.append(list[i]);
        }
    }


    else if(list[0]==SbCreatServer){//SbcreateServer + username + ip + port + ...(ѭ��)
           int k=(list.size()-1)/4;
           for(int i=0; i<k; ++i){
               if(list[1+4*i]!=name){
                   socket temp;

                   qint16 w=list[3+4*i].toInt();
                   temp={list[2+4*i],w};
                   bool flag=true;
                   bool changetcp=false;
                   QMap<QString,  socket>::iterator tt=pp.begin();
                   while(tt!=pp.end()){
                       if(tt.key()!=list[1+4*i])   ++tt;
                       else {
                           if(tt.value()==temp){
                               //��ͬsoket������ɾ��
                               flag=false;

                           }
                           else{
                               changetcp=true;
                               pp.remove(tt.key());//��ͬsoket��ɾ��ԭ��������
                               flag=true;
                           }
                           break;
                       }
                       qDebug()<<"SbCreatServer  "<<temp.theip<<temp.port;

                   }
                   if(flag){
                       pp.insert(list[1+4*i],temp);
                       qDebug()<<"SbCreatServer"<<temp.theip<<temp.port;
                   }
                   if(changetcp){//PersonalDialog �����tcpsocketò���ô�����ֻҪ��privatechat����Ϣ����ȷ��socket����
                       if(pdList.contains(list[1])){
                           PersonalDialog *s=pdList[list[1]];
                           QTcpSocket *ss=createP2PSocket(list[1]);
                           s->changeSocket(ss);


                       }
                   }
               }
           }


       }

       else if(list[0]=="e")//����P2P��(�����Ǻͷ������ĶԻ�)���Ե�ǰ�����ǲ������¼�
       {
           //�жϷ�����Ϣ�û����Ƿ���pdList���棬������ڣ��½�һ��PersonalDialog����
           if(!pdList.contains(list[1]))
           {

               PersonalDialog *newdig=new PersonalDialog(this,tcpSocket,list[1],name,&pdList);
               pdList.insert(list[1],newdig);
               newdig->show();
           }
           pdList[list[1]]->getMessage(list[1],list[3]);
       }
       else if(list[0]=="privatechat"){//����P2P�ģ��Ե�ǰ�����ǲ������¼�
           if(!pdList.contains(list[1]))
           {

               PersonalDialog *newdig=new PersonalDialog(this,tcpSocket,list[1],name,&pdList);
               pdList.insert(list[1],newdig);
               newdig->show();
           }
           pdList[list[1]]->getMessage(list[1],list[3]);

       }
       else if(list[0]=="f")//������Ϣ
       {

           for(i=0;list[2*i]!="";i++)
           {
               if(list[2*i]=="f")
               {
                   list[1]=list[2*i+1];
                   ui->textEdit->append(list[1]);
               }
               else
                   break;
           }

       }
    else if(list[0]=="g")//�����ļ����յ���Ϣ
    {
        int port1=list[2].toInt();// messages="g+"+str1+"+"+str2;//��ַ + �˿�
        Tport=port1;
        QString tlist=list[1];
        QString sonlist;
        if(tlist[0]!=':')
            sonlist=tlist;
        else
            sonlist=tlist.mid(7);

        QHostAddress ip1(sonlist);

        Tip=ip1;//��ʼΪ�����IP

        qDebug()<<port1<<ip1;
        if(Tport)
        {
            QMessageBox::information(NULL,"��ʾ","�ɹ���ȡ�û���Ϣ��",QMessageBox::Ok);
        }
        else
        {
            QMessageBox::information(NULL,"warning","��ȡ�û�ʧ��",QMessageBox::Ok);

        }
    }
    else if(list[0]=="h")
    {
        QMessageBox::information(NULL,"new file",list[1]);

        QString name ="";
        while (name=="")
        {
            name = QFileDialog::getSaveFileName(0,tr("�����ļ�"),list[1]);
        }
        qDebug()<<name<<Tip<<Tport;
        /*
        if(send)delete send;
        send=0;
        if(rec)delete rec;
        */
        rec=0;
        length=list[2].toInt();
        rec = new receiver(this,Tip,name,length);
        rec->show();
    }

    else if(list[0]=="inquiry")
    {

        int port1=list[2].toInt();
        Tport=port1;
        QString sonlist=list[1];
        QHostAddress ip1(sonlist);
        Tip=ip1;

        qDebug()<<port1<<ip1;//��ȡ�Է���IP + port
        if(Tport)
        {
            QMessageBox::information(NULL,"��ʾ","���ӳɹ���",QMessageBox::Ok);

        }
        else
        {
            QMessageBox::information(NULL,"warning","����ʧ��",QMessageBox::Ok);

        }
    }
    else
        return;
}


void UserUi::on_pushButton_clicked()//����������Ϣ
{
    QString str1=ui->lineEdit->text();
    QString str2=ui->lineEdit_2->text();

    if(str2=="")
        QMessageBox::information(NULL,"warning","������Է��û���",QMessageBox::Ok);


    else{
        QDateTime time = QDateTime::currentDateTime();//��ȡϵͳ���ڵ�ʱ��
        QString str = time.toString("yyyy-MM-dd hh:mm:ss"); //������ʾ��ʽ
        ui->textEdit->append("<font color=#F5E2EC> "+name+"\t\t"+str+"</font>");
        ui->textEdit->append(str1);

        QString message="c+"+name+"+"+str2+"+"+str1;//c+��������+��������+���͵���Ϣ
        QByteArray data=message.toUtf8();/*******/
        tcpSocket->write(data);
        //tcpSocket->write(message.toLatin1());
        ui->lineEdit->clear();
    }

}

void UserUi::on_refreshBtn_clicked()//�û��б�
{
    QString message="e+getUserList";
    tcpSocket->write(message.toUtf8());

}


void UserUi::on_pushButton_2_clicked()
{
    QString message="f+"+name;
    tcpSocket->write(message.toUtf8());
}

void UserUi::on_pushButton_3_clicked()//�����ļ�
{
    qDebug()<<"waiting for sending files";
    QString str1=ui->lineEdit_2->text();

    QString senddata="inquiry+"+str1;//�����û�������

    tcpSocket->write(senddata.toUtf8());


}


void UserUi::on_openFileBtn_clicked()//���ļ�
{
    // ����������������.
    #if _MSC_VER >= 1600
    #pragma execution_character_set("utf-8")
    #endif


    filename=QFileDialog::getOpenFileName(this);
    FILE *fp=fopen(filename.toUtf8(),"r");
    QString re=ui->lineEdit_2->text();
    qDebug()<<fp;
    if(!fp)
    {

        QMessageBox::information(NULL,"��ʾ","�ļ���ȡʧ�ܣ�");
        return;
    }
    fseek(fp,0,SEEK_END);
    length=ftell(fp);//�õ��ļ�λ��ָ�뵱ǰλ��������ļ��׵�ƫ���ֽ�����

    QString curFile="file+"+re+"+"+filename.right(filename.size()-filename.lastIndexOf('/')-1)+"+"+QString::number(length);//�ļ���Ϣ

    QString cFilename=filename.right(filename.size()-filename.lastIndexOf('/')-1);

    ui->filepath->isReadOnly();
    ui->filepath->setText(cFilename);
    tcpSocket->write(curFile.toUtf8());
    fclose(fp);
    fp=0;

}

void UserUi::on_pushButton_4_clicked()//��ʼ�����ļ�
{
    //QMessageBox::information(NULL,"��ʾ","ȷ�Ϸ���");

    /*
     *
   */

    /* if(send)delete send;
    //send=0;
    if(rec)delete rec;*/
    //rec=0;
    qDebug()<<Tip<<Tport<<filename<<length;
    send = new senders(this,Tip,filename,length);//�ļ�����

    send->show();
    qDebug()<<"send is called";

    send->gbn();
    qDebug()<<"gbn is called";
}
