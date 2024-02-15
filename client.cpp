#include "client.h"

Client::Client(int cin, int num, QString nom, QString prenom, QString mail, int card)
{
    this->cin=cin;
    this->num=num;
    this->nom=nom;
    this->prenom=prenom;
    this->mail=mail;
    this->card=0;

    ;

}

bool Client::ajouter()
{



    QSqlQuery query;
    QString res=QString::number(cin);
          query.prepare("INSERT INTO CLIENT (cin, nom, prenom,num,mail) ""VALUES (:cin, :nom, :prenom, :num, :mail)");
          query.bindValue(":cin",res);//INSERT INTO equipement VALUES (val code, nom,type)meme ordre que le table
          query.bindValue(":nom",nom);
          query.bindValue(":prenom",prenom);
          query.bindValue(":num",num);
          query.bindValue(":mail",mail);
    return query.exec();
}

QSqlQueryModel * Client::afficher()
{
    QSqlQueryModel  * model=new QSqlQueryModel();
    model->setQuery("select * from client");
//    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Nom"));
//    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Prenom"));
//    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Cin"));
//    model->setHeaderData(3,Qt::Horizontal,QObject::tr("num"));
//    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Adresse mail"));
    return model;
}

bool Client::supprimer(int cin)
{
    QSqlQuery query;
    QString res=QString::number(cin);

    query.prepare("delete from client where cin= :cin");
    query.bindValue(":cin",res);

    return query.exec();
}

bool Client::modifier()
{
    QSqlQuery query;
    QString res = QString::number(cin);

    query.prepare("UPDATE client SET nom=:nom, prenom=:prenom,num=:num, mail=:mail  WHERE cin=:cin" );

    query.bindValue(":cin",res);
    query.bindValue(":num",num);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":mail",mail);
    return query.exec();
}


// Metiers

QSqlQueryModel * Client::rechercherNom(QString nom)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from client where nom like '" +nom+"'");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Cin"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("num"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Adresse mail"));

    return model;
}


QSqlQueryModel * Client::triNom()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from client order by nom");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Cin"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("num"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Adresse mail"));

    return model;
}



bool Client::update()
{
    QSqlQuery query;

    QString car = QString::number(card);
    car = car+1;

    query.prepare("UPDATE client SET card=:card  WHERE nom=:nom" );
    query.bindValue(":card",card);

    return query.exec();
}


QSqlQueryModel * Client::plus(QString nom)
{

    QSqlQuery query;
    QString c = QString::number(card);
    query.bindValue(":card",c);
    query.prepare("UPDATE client SET card=:card  WHERE cin=:cin" );
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from client where nom like '" +nom+"'");
    return model;
}

QSqlQueryModel * Client::plus2()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from client order by card");
    return model;
}




