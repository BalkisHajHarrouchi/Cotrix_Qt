#include "agent.h"
#include <QSqlQuery>
Agent::Agent()
{
username="";
pass="";
type="";
action="";
}
Agent::Agent(QString u ,QString p,QString t,QString a)
{
username=u;
pass=p;
type=t;
action=a;
}
QString Agent::getid(){
    QSqlQuery qry;
    int action=1;
    QString res1,res=QString::number(action);

    qry.prepare("select * from agent where action='"+res+"' " );
    if(qry.exec())
    {
        while(qry.next())
        {
            res1=qry.value(0).toString();

        }
    }


    return res1;
}
int Agent::role(){
                  QString res1,r=getid();
                  QSqlQuery qry;
                  qry.prepare("select * from agent where username='"+r+"' " );
                  if(qry.exec())
                  {
                      while(qry.next())
                      {
                          res1=qry.value(2).toString();

                      }
                  }
if(res1=="admin"){
return 5;

}
if(res1=="RH"){
return 0;



}
if(res1=="Finance"){
    return 1;


}
if(res1=="Client"){
    return 2;



}
if(res1=="Espace"){
    return 3;



}
if(res1=="Equipement"){
    return 4;



}
else
    return -1;
}
bool Agent::ajouter()
{
    QSqlQuery query2;
    // QString CIN_string=QString::number(CIN);
    query2.prepare("INSERT INTO agent ( username, password, type, action) ""VALUES ( :username, :password, :type, :action)");
    query2.bindValue(":username", username);
    query2.bindValue(":password", pass);
    query2.bindValue(":type", type);
    query2.bindValue(":action", action);
    return query2.exec();
}
