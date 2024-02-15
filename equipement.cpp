#include "equipement.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QSqlQueryModel>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QDebug>
#include <qdebug.h>
#include <string>

Equipement::Equipement()
{
    code=0;
    nom="";
    type="";
    quantite=0;
}
Equipement::Equipement(int code,QString nom,QString type,int quantite)
{
    this->code=code;
    this->nom=nom;
    this->type=type;
    this->quantite=quantite;
}
bool Equipement::ajouter()
{
   // bool test=false;
    QSqlQuery query;
    QString code_string=QString::number(code);
    QString quantite_string=QString::number(quantite);
          query.prepare("INSERT INTO equipement (code, nom, type,quantite) ""VALUES (:code, :nom, :type, :quantite)"); //INSERT INTO equipement VALUES (val code, nom,type)meme ordre que le table
          query.bindValue(":code", code_string); //relier la valeur a la variable  d'une maniere securisé(:) //remplir la val de la requette sql
          query.bindValue(":nom", nom);
          query.bindValue(":type", type);
          query.bindValue(":quantite", quantite_string);
          return query.exec();
    //return test;
}

QSqlQueryModel *Equipement::afficher()
{
QSqlQueryModel *model=new QSqlQueryModel();
model->setQuery("select * from Equipement");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("CODE"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("TYPE"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("QUANTITE"));
return model;
}

bool Equipement::supprimer(int code)
{
    QSqlQuery query;
    QString code_string=QString::number(code);
          query.prepare("Delete from equipement where CODE=:code");
          query.bindValue(":code", code_string);
          return query.exec();
}

bool Equipement::modifier(int code)
{
    QSqlQuery query;
           QString res=QString::number(code);
            QString ress=QString::number(quantite);


             query.prepare("UPDATE equipement "" SET code=:code, nom=:nom, type=:type, quantite=:quantite where CODE='"+res+"' ");


                   query.bindValue(":code", res);
                   query.bindValue(":nom", nom);
                   query.bindValue(":type", type);
                    query.bindValue(":quantite", ress);

               return query.exec();
}

QSqlQueryModel *Equipement::chercher(int code)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QString str ;
    //Connexion Conn;
    //Conn.ouvrirConnexion();
    //Conn.openBD();
    if(code== NULL){
        str="SELECT * FROM  EQUIPEMENT";
    }

         str="select * from EQUIPEMENT where code ="+QString::number(code);
        model->setQuery(str);
    //Conn.fermerConnexion() ;
        return model;

}
QSqlQueryModel *Equipement::sortid()
{

    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select *from EQUIPEMENT ORDER BY code");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("code"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("type"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("quantite"));

    return model;
}
QSqlQueryModel *Equipement::sortquantite()
{

    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select *from EQUIPEMENT ORDER BY quantite");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("code"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("type"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("quantite"));

    return model; }
