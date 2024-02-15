#ifndef AGENT_H
#define AGENT_H
#include "QString"
#include <QSqlDatabase>
#include <QSqlQueryModel>
class Agent
{
    QString username,pass,action,type;
 public:
    Agent();
    Agent(QString, QString,QString,QString);
    QString getusername(){return username;}
    QString getpass(){return pass;}
    QString getaction(){return action;}
    QString gettype(){return type;}
    void setusername(QString u){username=u;}
    void setpass(QString upass){pass=upass;}
    void setaction(QString uaction){action=uaction;}
    void settype(QString utype){type=utype;}
    QString getid();
    int role();
    bool ajouter();

};

#endif // AGENT_H
