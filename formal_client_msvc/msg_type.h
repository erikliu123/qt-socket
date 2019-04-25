#ifndef MSG_TYPE_H
#define MSG_TYPE_H
#include <QString>
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
qint16 port =5050;
#endif // MSG_TYPE_H
