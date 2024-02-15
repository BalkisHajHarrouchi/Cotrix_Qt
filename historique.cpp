#include "historique.h"
#include <QSqlQuery>

historique::historique()
{
     user="";action="";
}
historique::historique(QString user,QString action,QDateTime date){
    this->user=user;
    this->dateh=date;
    this->action=action;

}
QSqlQueryModel * historique::afficher()
{

    QSqlQueryModel * modal= new QSqlQueryModel ();
    QSqlQuery*qry=new QSqlQuery();

    qry->prepare("select * from historique");
    qry->exec();
    modal->setQuery(*qry);
    modal->setHeaderData(0,Qt::Horizontal,QObject::tr("User"));
    modal->setHeaderData(1,Qt::Horizontal,QObject::tr("Action"));
     modal->setHeaderData(2,Qt::Horizontal,QObject::tr("Temps"));
return modal;

}
bool historique::supprimer(QDateTime d)
{
QSqlQuery query;

query.prepare("Delete from historique where dateh=:id");
query.bindValue(":id",d);
return query.exec();
}

QSqlQueryModel * historique::afficheragent(QString agent)
{

    QSqlQueryModel * modal= new QSqlQueryModel ();
    QSqlQuery*qry=new QSqlQuery();

    qry->prepare("select * from historique where username=:name");
    qry->bindValue(":name",agent);

    qry->exec();
    modal->setQuery(*qry);
    modal->setHeaderData(0,Qt::Horizontal,QObject::tr("User"));
    modal->setHeaderData(1,Qt::Horizontal,QObject::tr("Action"));
     modal->setHeaderData(2,Qt::Horizontal,QObject::tr("Temps"));
return modal;

}
