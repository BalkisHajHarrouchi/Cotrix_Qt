#include "facture.h"
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QPrinter>
#include <QFileDialog>
#include <QTextDocument>

Facture::Facture()
{

}

Facture::Facture(int num,QString nom,QString prenom ,int prix , QDate date)
{
    this->num=num;
    this->nom=nom;
    this->prenom=prenom ;
    this->prix=prix;
    this->date=date;
}


int Facture::getnum(){return num;}

QString Facture::getnom(){return nom;}
QString Facture::getprenom(){return prenom;}
int Facture::getprix(){return prix;}
QDate Facture::getdate(){return date;}


void Facture::setnum(int num){this->num=num;}
void Facture::setnom(QString nom){this->nom=nom;}
void Facture::setprenom (QString prenom){this->prenom=prenom;}
void Facture::setprix(int prix){this->prix=prix;}
void Facture::setdate(QDate date){this->date=date;}






bool Facture::ajouterfacture()
{

     QSqlQuery query;
     query.prepare("INSERT INTO FACTURE (num,nom,prenom ,prix,datee) VALUES (:num, :nom, :prenom, :prix ,:datee)");// prparation de requette
     query.bindValue(":num", num); //remplir CIN2 dans CIN1
     query.bindValue(":nom", nom);
     query.bindValue(":prenom",prenom);
     query.bindValue(":prix",prix);
     query.bindValue(":datee",date);
     return query.exec();

}


QSqlQueryModel* Facture::afficherfacture()
{
     QSqlQueryModel* model=new QSqlQueryModel();

     model->setQuery("SELECT *  FROM Facture ");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("numero de facture "));//nom entite
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("date"));

     return model;
}



bool Facture::supprimerfacture(int num)
{
    QSqlQuery query;
    query.prepare(" Delete from FACTURE where NUM=:NUM ");
    query.bindValue(":NUM",num);

    return query.exec();
}




bool Facture::modifierfacture(int num,QString nom ,QString prenom  ,int prix , QDate date)
{

        QSqlQuery query;
        query.prepare("update FACTURE set nom=:nom,prenom=:prenom,prix=:prix,datee=:datee where num=:num");
        query.bindValue(":num",num);
        query.bindValue(":nom",nom);
        query.bindValue(":prenom",prenom);
        query.bindValue(":prix",prix);
        query.bindValue(":datee",date);
        return query.exec();

    }

QSqlQueryModel* Facture::Recherchefacture(QString recherche)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("SELECT * FROM Facture WHERE NUM LIKE '"+recherche+"%' ");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("num"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("date"));



return model;
}

bool Facture::supprimerTout()
{
    QSqlQuery query;
    query.prepare("delete from facture ");
    return query.exec();
}

QSqlQueryModel * Facture::trierfactureparnumfacture()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM FACTURE order by num ASC");
           q->exec();
           model->setQuery(*q);
           return model;
}

QSqlQueryModel * Facture::trierfactureParprix()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM FACTURE order by prix ASC");
           q->exec();
           model->setQuery(*q);
           return model;
}


QSqlQueryModel * Facture::trierfacturepardate()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM FACTURE order by datee ASC");
           q->exec();
           model->setQuery(*q);
           return model;
}
void Facture::telechargerPDF()
{
    QPdfWriter pdf("C:/Users/MSI/Desktop/Atelier_Connexion/PDFF.pdf");
                         QPainter painter(&pdf);
                        int i = 4000;
                             painter.setPen(Qt::blue);
                             painter.setFont(QFont("Arial", 30));
                             painter.drawText(1100,1200,"GESTION DE FACTURE");
                             painter.setPen(Qt::black);
                             painter.setFont(QFont("Arial",14));
                             painter.drawRect(100,100,7300,2600);
                             painter.drawRect(0,3000,9600,500);
                             painter.setFont(QFont("Arial",11));
                             painter.drawText(200,3300,"NUM");
                             painter.drawText(1300,3300,"NOM");
                             painter.drawText(2200,3300,"PRENOM");
                             painter.drawText(3200,3300,"PRIX");
                             painter.drawText(5300,3300,"DATEE");

                             QSqlQuery query;
                            // query.prepare("select * from FACTURE where NUM='"+val+"'");
                             query.prepare("select * from FACTURE");
                             query.exec();
                             while (query.next())
                             {
                                 painter.drawText(200,i,query.value(0).toString());
                                 painter.drawText(1300,i,query.value(1).toString());
                                 painter.drawText(2200,i,query.value(2).toString());
                                 painter.drawText(3200,i,query.value(3).toString());
                                 painter.drawText(5300,i,query.value(4).toString());


                                i = i + 500;
                             }}

