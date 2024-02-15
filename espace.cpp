#include "espace.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

Espace::Espace()
{
numsalle=0; capacite=0; bloc=" "; type=" "; etat=" ";
}

Espace::Espace(int numsalle,int capacite,QString bloc,QString type,QString etat)
{
    this->numsalle=numsalle;
    this->capacite=capacite;
    this->bloc=bloc;
    this->type=type;
    this->etat=etat;
}

int Espace::getnumsalle(){return numsalle;}
int Espace::getcapacite(){return capacite;}
QString Espace::getbloc(){return bloc;}
QString Espace::gettype(){return type;}
QString Espace::getetat(){return etat;}
void Espace::setnumsalle(int numsalle){this->numsalle=numsalle;}
void Espace::setcapacite(int capacite){this->capacite=capacite;}
void Espace::setbloc(QString bloc){this->bloc=bloc;}
void Espace::settype(QString type){this->type=type;}
void Espace::setetat(QString etat){this->etat=etat;}

bool Espace::ajouter()
{

                      QString numsalle_string=QString::number(numsalle);
                      QSqlQuery query;
                       query.prepare("INSERT INTO espace (numsalle, capacite, bloc, type, etat) "" VALUES (:numsalle, :capacite, :bloc, :type, :etat)");
                       query.bindValue(":numsalle", numsalle_string);
                       query.bindValue(":capacite", capacite);
                       query.bindValue(":bloc", bloc);
                       query.bindValue(":type", type);
                       query.bindValue(":etat", etat);
                     return  query.exec();


}
bool Espace::supprimer(int numsalle)
{
    QSqlQuery query;
    query.prepare("Delete from espace where numsalle=:numsalle");
    query.bindValue(0, numsalle);


return query.exec();


}

bool Espace::modifier(int numsalle)
{

               //
               QSqlQuery query;

                      QString res=QString::number(numsalle);
                      QString res1=QString::number(capacite);
//                      QString type;
//                      QString etat;
//                      QString bloc;

                      query.prepare("UPDATE ESPACE SET NUMSALLE=:NUMSALLE,CAPACITE=:CAPACITE,BLOC=:BLOC,TYPE=:TYPE,ETAT=:ETAT WHERE NUMSALLE='"+res+"'");
                      query.bindValue(":NUMSALLE",res);
                      query.bindValue(":CAPACITE",res1);
                      query.bindValue(":BLOC",bloc);
                      query.bindValue(":TYPE",type);
                      query.bindValue(":ETAT",etat);


                      return query.exec();
               //


}

QSqlQueryModel* Espace::afficher()
{
   QSqlQueryModel* model=new QSqlQueryModel();


        model->setQuery("SELECT* FROM espace");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Numsalle"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Capacite"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Bloc"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Etat"));

    return model;
}


