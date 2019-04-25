//mysql.cpp
#include "db.h"
#include <QCryptographicHash>
#include <QMessageBox>
#include <QObject>
#pragma execution_character_set("utf-8")
MySql::MySql()
{
    this->initsql();
    //initmysql();
}

MySql::MySql(int Mysql)
{
    switch (Mysql) {
    case SQL::MYSQL:
         initmysql();
        break;
    case SQL::SQLITE:
        initsql();
        break;
    default:
        break;
    }

}

/*bool MySql::checkSignUp(QString name, QString passward,QString mail)
{
    MySql *mysql=new MySql();

    QByteArray Pwdname=name.toLatin1();
    QByteArray PwdnameMd5=QCryptographicHash::hash(Pwdname,QCryptographicHash::Md5);
    QString nameMd5=PwdnameMd5.toHex();

    QByteArray Pwdpassward=passward.toLatin1();
    QByteArray PwdpasswardMd5=QCryptographicHash::hash(Pwdpassward,QCryptographicHash::Md5);
    QString passwardMd5=PwdpasswardMd5.toHex();

    bool ret=mysql->signup(nameMd5,passwardMd5,mail);
    return ret;
}*/



bool MySql::reset(QString name, QString passward)
{

    QSqlQuery reset_query;

    QString lookfor = "update User set passward = :passward where name = :name";
    reset_query.prepare(lookfor);
    reset_query.bindValue(":passward", passward);
    reset_query.bindValue(":name", name);
    if(!reset_query.exec())
    {
        qDebug() << reset_query.lastError();
        return 0;
    }
    else
    {
        qDebug() << "pass modify!";
        return 1;
    }
}




void MySql::initsql()
{
    QSqlDatabase database;
    if (0 && QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("liujiah.db");
        database.setUserName("liujiahong");
        database.setPassword("123456");
    }

    if(database.open())
        {
            qDebug()<<"Database connected successfully!";
            //createtable();//没表需要补充！
            return;
        }
    else
        {
            qDebug() << "Error: Failed to connect database." << database.lastError();
            return;
        }


}
void MySql::initmysql()
{
    QSqlDatabase database2;
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    database2 = QSqlDatabase::addDatabase("QMYSQL");

    database2.setHostName("193.112.99.178");//指定数据库服务器名称
     database2.setDatabaseName("mac");
    database2.setUserName("root");
    database2.setPassword("liu123");

    if(database2.open())//需要加载MYSQL 的驱动才有效
        {
            qDebug()<<"MYSQL Database connected successfully!";
            //createtable();
            QSqlQuery sql_query;
            QString select_all_sql = "select * from trial";
            sql_query.prepare(select_all_sql);
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                 qDebug() << "MAC映射";
                while(sql_query.next())
                {
                    QString macaddr = sql_query.value(0).toString();
                    QString last_login = sql_query.value(1).toString();
                    QString fail_times = sql_query.value(2).toString();
                    QString consecutive_times = sql_query.value(3).toString();
                    qDebug()<<QString("macaddr:%1    last_login:%2    fail_times:%3  consecutive_times:%4").arg(macaddr).arg(last_login).arg(fail_times).arg(consecutive_times);
                }
            }
            return;
        }
    //createtable();
}

void MySql::createtable()
{
    /*QSqlQuery sql_query;
    QString create_sql = "create table User (name VARCHAR(30) PRIMARY KEY,passward VARCHAR(30),mail VARCHAR(30))";
    sql_query.prepare(create_sql);
    //sql_query.exec("create table User (name VARCHAR(30) PRIMARY KEY UNIQUE NOT NULL,passward VARCHAR(30))");
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create table." << sql_query.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }*/

    QSqlQuery query,sql_query;
    QString select_all_sql = "select * from User";
    sql_query.prepare(select_all_sql);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
         qDebug() << "用户";
        while(sql_query.next())
        {
            QString name = sql_query.value(0).toString();
            QString passward = sql_query.value(1).toString();
            QString mail = sql_query.value(2).toString();
            qDebug()<<QString("name:%1    passward:%2    mail:%3").arg(name).arg(passward).arg(mail);
        }
    }

        if( !query.exec("create table User (name VARCHAR(30) PRIMARY KEY,passward VARCHAR(30),mail VARCHAR(30))") )
        {
            qDebug() << "Error: Fail to create table." << query.lastError();
            //QMessageBox::warning(NULL, "Create Table", ("Create Table error:%1").arg(query.lastError().text()));
        }




}


bool MySql::loguser(QString name, QString passward)
{
    QString str=QString("select * from User where name='%1' and passward='%2'").arg(name).arg(passward);
    QSqlQuery log_query;
    log_query.exec(str);
    qDebug() << log_query.first();
    if(log_query.first())
    {
        return true;
    }
    else
        return false;
}


bool MySql::signup(QString name,QString passward,QString mail)
{
    QString str1=QString("select * from User where name='%1").arg(name);
    QSqlQuery check_query;
    check_query.exec(str1);
    qDebug() << check_query.first();
    if(check_query.first())
    {
        return false;
    }
    else
    {
        QString str2=QString("insert into User  values('%1','%2','%3')").arg(name).arg(passward).arg(mail);
        QSqlQuery sig_query;
        sig_query.prepare(str2);

        bool ret = sig_query.exec();
        qDebug() <<"signup result:" <<ret;
        if(!ret)
        {
            qDebug() << sig_query.lastError();
            return false;
        }
        else
        {
            qDebug() << "register success!";
            return true;
        }
    }

}

bool MySql::exist(QString name)//存在该用户
{
    QString str=QString("select * from  User where name='%1'").arg(name);
    QSqlQuery exi_query;
    exi_query.exec(str);
    qDebug() << exi_query.first();
    if(exi_query.first())
    {
        return true;
    }
    else
        return false;
}

bool MySql::checkMAC(QString mac)//3次以上则返回错误
{
    QString str=QString("select consecutive_times from  trial where macaddr='%1'").arg(mac);
    QSqlQuery exi_query;
    exi_query.exec(str);
    qDebug() <<"checkMAC" <<exi_query.first();
    if(!exi_query.first())
        return true;

    else{
         int times=exi_query.value(0).toInt();
         if(times>3) return false;
         else return true;
    }
    //return false;
}
bool MySql::hasMAC(QString mac)
{
    QString str=QString("select consecutive_times from  trial where macaddr='%1'").arg(mac);
    QSqlQuery exi_query;
    exi_query.exec(str);

    if(exi_query.first())
        return true;

    else
        return false;

}
bool MySql::updateMAC(QString mac, bool success)
{
    initmysql();
    if(success){
        if(hasMAC((mac))){
            QString str=QString("update trial set consecutive_times = 0  where macaddr='%1'").arg(mac);
            QSqlQuery exi_query;
            exi_query.exec(str);
        }

    }
    else{
        QString str;
        QSqlQuery exi_query;
        qDebug()<<"MAC="<<mac;
        if(hasMAC((mac))){
             str=QString("update trial set consecutive_times = consecutive_times+1  where macaddr='%1'").arg(mac);
             exi_query.exec(str);
             str=QString("update trial set fail_times = fail_times+1  where macaddr='%1'").arg(mac);
         }
         else{
            str=QString("insert into trial values('%1',NULL,1,1)").arg(mac);
         }
        exi_query.exec(str);

    }
    return true;
}

bool MySql::checkmail(QString name, QString mail)
{
    initmysql();
    QString str=QString("select * from User  where name='%1' and mail='%3'").arg(name).arg(mail);
    QSqlQuery mail_query;
    mail_query.exec(str);
    qDebug() << "mail_query"<< mail_query.first();
    if(mail_query.first())
    {
        return true;
    }
    else
        return false;
}


