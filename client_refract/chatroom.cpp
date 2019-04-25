#include "chatroom.h"
#include "ui_chatroom.h"
#include "p2p.h"
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
#include <QStackedWidget>
#pragma execution_character_set("utf-8")

int indexOf(QStringList &s, QString str);
QString leavename;
ChatRoom::ChatRoom(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pStackedWidget=new QStackedWidget;
    ui->scrollArea->setWidget(m_pStackedWidget);
	socket_list = new QSet<QTcpSocket *>;

}

ChatRoom::ChatRoom(QWidget *parent,QTcpSocket *pTcpSocket,QString _name, qint16 _port, QString _serverip) :
    QMainWindow(parent),tcpSocket(pTcpSocket),name(_name),myport(_port),serverIP(_serverip),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("welcome, "+_name);
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessages()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(sendLeave()));
    myip=pTcpSocket->localAddress().toString();// 取客户的IP
    // srand((unsigned short)time(NULL));
    //myport=6000+rand()%1000;

    qDebug()<<"myport and ip:"<<myport<<myip;

     m_pStackedWidget=new QStackedWidget;
	 m_pStackedWidget->setMinimumSize(670,630);//需要设置最小大小，否则缩小整个窗口后，仍然不能滑动。
    ui->scrollArea->setWidget(m_pStackedWidget);
    connect(m_pStackedWidget, SIGNAL(widgetRemoved(int index)), this, SLOT(stackchanged(int index)));



    //建立客户端的监听
    this->person=new QTcpServer();
    if(!person->listen(QHostAddress::Any,myport))
    {
        qDebug()<<" port failure";
        close();
        return;
    }
    else qDebug()<<"successfully open my port";
	socket_list = new QSet<QTcpSocket *>;
    connect(person,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
    socket *s=new socket;
    s->theip=myip;
    s->port=myport;

    QString a=SbCreatServer+"+"+name+'+'+myip+ "+"+ QString::number(myport)+ "+true+ " ;
    qDebug()<<a;
    tcpSocket->write(a.toUtf8());

    QThread::msleep(100);

    //获取当前在线用户
  
    //刷新用户
   /* connect(ui->refreshAction,&QAction::triggered,[=]{
        QString message="e+getUserList";
        this->tcpSocket->write(message.toUtf8());
    });*/
    connect(ui->refreshAction,SIGNAL(triggered(bool)),this,SLOT(getUserList()));


}
void ChatRoom::getUserList(){
    QString message="e+getUserList+";
    this->tcpSocket->write(message.toUtf8());
}

ChatRoom::~ChatRoom()
{
    delete ui;
   /* for(auto it=pdList.begin();it!=pdList.end();++it){
        delete *it; //报错	
    }*/
}
void ChatRoom::acceptConnection()
{
    QTcpSocket *tcp=person->nextPendingConnection();//多个监听端口

	socket_list->insert(tcp);
    QString ip=tcp->peerAddress().toString();
    int port=tcp->peerPort();
    qDebug()<<ip<<port;
    connect(tcp,SIGNAL(readyRead()),this,SLOT(readMessages3()));   //**********
	//connect(tcp, SIGNAL(disconnected()), this, SLOT(opponentHasLeave()));
	connect(tcp, SIGNAL(disconnected()), this, SLOT(sendLeave()));

}

void ChatRoom::sendLeave()
{

	QString message = "&leave+"+name+"+";
	QTcpSocket* tcp = static_cast<QTcpSocket*>(sender());
	socket_list->remove(tcp); return;
	tcp->write(message.toUtf8());
	
	//tcp->abort();
	

}
void ChatRoom::opponentHasLeave(){//TODO，关闭tcpsocket
     QTcpSocket* tcp = static_cast<QTcpSocket*>(sender());
     QString ip=tcp->peerAddress().toString();
	 qDebug() << "ip=" << ip<<"tcp->localPort()="<< tcp->localPort()<<" tcp->peer()"<< tcp->peerPort();//"tcp->localPort()=6163,自己的监听端口
	 int port = tcp->peerPort();
      struct socket temp={ip,port};
     for(auto it=pp.begin();it!=pp.end();++it){
        if(*it==temp){
            leavename=it.key();//leavename有可能找不到？？ 172.19.20.147 ::ffff:
			pp.remove(leavename);
            break;
        }
     }
	 int index = indexOf(onlineUser, leavename);
	 if(ui->listWidget->item(index)!=NULL)
		ui->listWidget->item(index)->setText(leavename + "\t[离线]");

    QMessageBox::information(this, "offline","<font color = #00CDCD> 对方离线, 用户:"+leavename+" 已经下线 < / font>",QMessageBox::Ok);
}

int indexOf(QStringList &s,QString str){
    for(int i=0;i<s.size();++i){
        if(s[i]==str) {
            return i;
        }

    }
     return -1;
}

void ChatRoom::readMessages3(){//接收消息
    QTcpSocket *tempTcp=static_cast<QTcpSocket*>(sender());//多个接受端
    QString data=tempTcp->readAll();
    qDebug()<<"server ChatRoom::readMessages3 "<<data;

    QStringList list=data.split("+");

	if (list[0] == "&leave" && list.size()>=2) {//万一&leave是正常的消息？ TODO: 第一次privatechat时，给对面发送一个哈希值？ 退出的时候比较一下hash编码
		leavename = list[1];
		int index = indexOf(onlineUser, leavename);
		QString hash = list[2];
		if (ui->listWidget->item(index) != NULL)
			ui->listWidget->item(index)->setText(leavename + "\t[离线]");
		QMessageBox::information(this, "offline", "<font color = #00CDCD> 对方离线, 用户:" + leavename + " 已经下线 < / font>", QMessageBox::Ok);
		return;
	}
    if(list[0]=="privatechat"){
         int index;
         leavename=list[1];//leavename在这被改了，前面找到对方下线的假象
       
        lastSendName=list[1];
        if(!pdList.contains(list[1]))
        {

            PersonalDialog *newdig=new PersonalDialog(this,tempTcp,list[1],name,&pdList);
           indexOf(onlineUser, list[1]);
            m_pStackedWidget->insertWidget(indexOf(onlineUser, list[1]),newdig);
            qDebug()<<"m_pStackedWidget count="<<m_pStackedWidget->count();
            m_pStackedWidget->removeWidget(m_pStackedWidget->widget(index+1));
            pdList.insert(list[1],newdig);
           //  ui->scrollArea->sete

            qDebug()<<" i have accepted "<<list[1];
           ui->scrollArea->setAutoFillBackground(true);

        }
        //ui->scrollArea->setWidget( pdList[list[1]]);
       // pdList[list[1]]->changeSocket(tempTcp);
        qDebug()<<indexOf(onlineUser, list[1]);
        m_pStackedWidget->setCurrentIndex(index);
       pdList[list[1]]->messageLen=list[2].toInt();
       qDebug("message len=%d", list[2].toInt());
       pdList[list[1]]->getMessage(list[1],getList(list));//BUG

    }
    else{

        //pdList[list[1]]->getMessageWithNoHead("",data);
        pdList[lastSendName]->getMessageWithNoHead("",data);
    }
}

PersonalDialog *ChatRoom::newp2p(QString opponame){

    QTcpSocket *tcp;
    if(tcp=createP2PSocket(opponame)){

        return new PersonalDialog(ui->scrollArea,tcp,opponame,name,&pdList);
    }
    return NULL;

}

void ChatRoom::closeEvent(QCloseEvent *)
{
	for (auto it = socket_list->begin(); it != socket_list->end(); ++it) {
		QString message = "&leave+" + name + "+";
		(*it)->write(message.toUtf8());
	}
}

QTcpSocket* ChatRoom::createP2PSocket(QString &str){
    QTcpSocket *temp=new QTcpSocket;
    if(!pp.contains(str)){
        QMessageBox::information(NULL,"异常,缺少对面服务器IP+ PORT","非法用户 "+str,QMessageBox::Ok);
        delete temp;
        return NULL;
    }
    socket ts=pp[str];
    QString ip=QString(ts.theip);
    qint16 port=ts.port;
    temp->abort();   //取消已有的连接
    temp->connectToHost(ip,port);//hh是不是需要修改
    qDebug()<<"createP2PSocket triggered USER="<<str;
    return temp;
}


//stackWidget改变后处理
void ChatRoom::stackchanged(int index)
{
    qDebug()<<"<m_pStackedWidget->count()="<<m_pStackedWidget->count();
    if(m_pStackedWidget->count()==0){
        //设置scrollWidget为其他窗口
        return ;
    }
    if(index==0) m_pStackedWidget->setCurrentIndex(0);
    else m_pStackedWidget->setCurrentIndex(index-1);
}

QString ChatRoom::getList(QStringList &list){
    QString temp;
    for(int i=3;i<list.size();++i){
        temp+=list[i];
        if(i!=(list.size()-1)) temp+="+";
    }
    return temp;
}


void ChatRoom::on_listWidget_doubleClicked(const QModelIndex &index)//创建新窗口
{
      QString string=onlineUser.at(index.row());  //获得对方用户名;
        qDebug()<<string<<"double clicked";
    if(!pdList[string]){
        PersonalDialog *person;
       if(person=newp2p(string)){
           qDebug()<<"newp2p ";
           pdList.insert(string,person);
           m_pStackedWidget->insertWidget(index.row(),person);
             m_pStackedWidget->setCurrentIndex(index.row());
             return ;

       }
       else{
           return ;
       }
    }
    m_pStackedWidget->setCurrentIndex(index.row());
   // m_pStackedWidget->();D
    return ;
    QString str=onlineUser.at(index.row());  //获得对方用户名; 
     qDebug()<<str<<"double clicked";

    QStringList list=str.split(" ");
    str=list[0];

    if(str.size()==0) return;
    if(pdList.contains(str) && (unsigned long)pdList[str]!=(~0)){
        qDebug() << "pdList[str]=" << pdList[str];
        ui->scrollArea->setWidget(pdList[str]);
//       ui->scrollArea->setAutoFillBackground(true);
       return ;
    }
    //QString message="f+"+str;
    //tcpSocket->write(message.toLatin1());
    QTcpSocket *hh=new QTcpSocket();
    socket ts=pp[str];
    QString ip;
    qint16 port;
    ip=QString(ts.theip);
    port=ts.port;

    hh->connectToHost(ip,port);

    qDebug()<<ip<<port;

    connect(hh,SIGNAL(readyRead()),this,SLOT(readMessages3()));
    //TODO:judge
    QGridLayout *gridLayout=new QGridLayout;
    if(pdList.contains(str)){

        //ui->widget=pdList[str];

         ui->scrollArea->setWidget(pdList[str]);
       // ui->scrollArea->setAutoFillBackground(true);
         //ui->widget->show();
        //ui->widget-

        return ;
    }
	/* str = "2";
	PersonalDialog *temp2 = new PersonalDialog(this, hh, str, name, &pdList);
	pdList.insert(str, temp2);
	 str = "3";*/
    PersonalDialog *temp=new PersonalDialog(ui->scrollArea,hh,str,name,&pdList);
	
    //QMap<QString,PersonalDialog*> pdList;

    //new a dialog
	
    pdList.insert(str,temp);
    pdList[str]->setNameText(str);
     qDebug() << "pdList[str]=" << pdList[str];
    ui->scrollArea->setWidget(pdList[str]);
    //ui->scrollArea->setAutoFillBackground(true);

}



//只管服务器的消息！
void ChatRoom::readMessages()
{
    int i;
    QByteArray temp=tcpSocket->readAll();
    //QString data=QString::fromLocal8Bit(temp);//不支持UTF8!!
    QString data=QString::fromUtf8(temp);
    qDebug()<<"ChatRoom::readMessage"<<data;
    QStringList list=data.split("+");


    if(list[0]=="c")//服务器对发送离线信息的回应
    {
        if(list[1]=="false"){
            //TODO:
            //ui->textEdit->append("-------上条信息发送失败，无该用户");
            QMessageBox::information(NULL,"警告","该用户不存在",QMessageBox::Ok);

        }
        else if(list[1]=="online")//发离线消息，对于在线人报错。。。
        {
              //TODO:
            //ui->textEdit->append("-------请点右侧用户列表双击进行在线聊天");

            QMessageBox::information(NULL,"警告","该用户在线",QMessageBox::Ok);
        }

    }

    else if(list[0]=="d")//接收客户列表
    {
        //ui->listWidget->clear();
        //onlineUser.clear();
        for(int i=1;i<list.size();i++)
        {
            if(list[i]==name)
                continue;
            if(hasLogUser.contains(list[i])) {

                QList<QListWidgetItem *> s=ui->listWidget->findItems(list[i]+"\t[离线]",Qt::MatchExactly);
                for(auto it=s.begin();it!=s.end();++it){
                    (*it)->setText(list[i]+"   [在线]");
                }
                continue;
             }
            hasLogUser.insert(list[i]);

            ui->listWidget->addItem(list[i]+"   [在线]");
            onlineUser.append(list[i]);
              QTcpSocket *tcpP2P=createP2PSocket(list[i]);
                if(!tcpP2P) continue;
             PersonalDialog *newdig=new PersonalDialog(this,tcpP2P,list[i],name,&pdList);
             pdList.insert(list[i],newdig);
            m_pStackedWidget->addWidget(newdig);
        }
    }


    else if(list[0]==SbCreatServer){//SbcreateServer + username + ip + port + ...(循环)
           int k=(list.size()-1)/4;
           for(int i=0; i<k; ++i){//i表示的是第几个用户，而不是第几个字符串
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
                               //相同soket的则不用删除
                               flag=false;

                           }
                           else{
                               changetcp=true;
                               pp.remove(tt.key());//不同soket，删除原来的数据
                               flag=true;
                           }
                           break;
                       }


                   }
                   if(flag){
                       pp.insert(list[1+4*i],temp);
                        qDebug()<<"SbCreatServer  "<<temp.theip<<temp.port;
						
					
                   }
				   //支持离线后重新登录自动更新对面的 socket
                   if(flag||changetcp){//PersonalDialog 里面的tcpsocket貌似用处不大，只要发privatechat的信息到正确的socket即可
					   if (pdList.contains(list[1 + 4 * i])) {
						   PersonalDialog *s = pdList[list[1 + 4 * i] ];
						   QTcpSocket *ss = createP2PSocket(list[1 + 4 * i]);
						   s->changeSocket(ss);
						   qDebug() << "changed SbCreatServer  " << temp.theip << temp.port;


					   }
                   }
               }
           }


       }

       else if(list[0]=="e")//这是P2P的(而不是和服务器的对话)，对当前程序是不可能事件
       {
           //判断发送消息用户名是否在pdList里面，如果不在，新建一个PersonalDialog对象
           if(!pdList.contains(list[1]))
           {

               PersonalDialog *newdig=new PersonalDialog(this,tcpSocket,list[1],name,&pdList);
               pdList.insert(list[1],newdig);
               newdig->show();
           }
           pdList[list[1]]->getMessage(list[1],list[3]);
       }
       else if(list[0]=="privatechat"){//这是P2P的，对当前程序是不可能事件
           if(!pdList.contains(list[1]))
           {

               PersonalDialog *newdig=new PersonalDialog(this,tcpSocket,list[1],name,&pdList);
               pdList.insert(list[1],newdig);
               newdig->show();
           }
           pdList[list[1]]->getMessage(list[1],list[3]);

       }
       else if(list[0]=="f")//离线信息
       {

           for(i=0;list[2*i]!="";i++)
           {
               if(list[2*i]=="f")
               {
                   list[1]=list[2*i+1];
                   //ui->textEdit->append(list[1]);
               }
               else
                   break;
           }

       }
    else if(list[0]=="g")//发送文件方收到信息
    {
        int port1=list[2].toInt();// messages="g+"+str1+"+"+str2;//地址 + 端口
        Tport=port1;
        QString tlist=list[1];
        QString sonlist;
        if(tlist[0]!=':')
            sonlist=tlist;
        else
            sonlist=tlist.mid(7);

        QHostAddress ip1(sonlist);

        qDebug()<<port1<<ip1;
        if(Tport)
        {
            QMessageBox::information(NULL,"提示","成功获取用户信息！",QMessageBox::Ok);
        }
        else
        {
            QMessageBox::information(NULL,"warning","获取用户失败",QMessageBox::Ok);

        }
    }
    else if(list[0]=="h")
    {
        QMessageBox::information(NULL,"new file",list[1]);

        QString name ="";
        while (name=="")
        {
            name = QFileDialog::getSaveFileName(0,tr("保存文件"),list[1]);
        }
        qDebug()<<name<<Tport;
        /*
        if(send)delete send;
        send=0;
        if(rec)delete rec;
        */
        length=list[2].toInt();
    }

    else if(list[0]=="inquiry")
    {

        int port1=list[2].toInt();
        Tport=port1;
        QHostAddress ip1(list[1]);

        qDebug()<<port1<<ip1;//获取对方的IP + port
        if(Tport)
        {
            QMessageBox::information(NULL,"提示","连接成功！",QMessageBox::Ok);

        }
        else
        {
            QMessageBox::information(NULL,"warning","连接失败",QMessageBox::Ok);

        }
    }
    else
        return;
}

