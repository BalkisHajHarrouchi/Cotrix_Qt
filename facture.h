#ifndef FACTURE_H
#define FACTURE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QDate>

class Facture

{
public:
    Facture();
    Facture(int,QString,QString,int,QDate);
    int getnum();
    int getprix();
    QString getnom();
    QString getprenom();
    QDate getdate();



    void setnum(int);
    void setprix(int);
    void setnom(QString);
    void setprenom(QString);
    void setdate(QDate);


    bool ajouterfacture();
    QSqlQueryModel* afficherfacture();
    bool supprimerfacture(int num);
    bool modifierfacture(int,QString,QString,int,QDate);
    QSqlQueryModel* Recherchefacture(QString);
    bool supprimerTout();
    QSqlQueryModel * trierfactureparnumfacture();
    QSqlQueryModel * trierfactureParprix();
    QSqlQueryModel * trierfacturepardate();
    void telechargerPDF();

private:
    int num,prix;
    QString nom,prenom;
    QDate date;
};


#endif // FACTURE_H
