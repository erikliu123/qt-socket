//mysql.h
#ifndef MYSQL_H
#define MYSQL_H

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
namespace SQL
{
    enum
    {
        MYSQL = 1,
        SQLITE = 2
    };
}
class MySql
{
public:
    MySql();
    MySql(int Mysql);
    void initsql();
    void initmysql();
    void createtable();
    bool loguser(QString name,QString passward);
    bool signup(QString name,QString passward,QString mail);
    bool exist(QString name);
    bool checkMAC(QString);
    bool hasMAC(QString);
    bool updateMAC(QString str,bool success);

    bool reset(QString name,QString passward);

    bool checkmail(QString name, QString mail);
    //void removeUserFormList();

//private:
   // QSqlQuery *query;
};

#endif // MYSQL_H
