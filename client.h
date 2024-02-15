#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
//test git


class Client
{
private:
    //Attributs
    int cin,num,card;
    QString nom,prenom,mail;

public:
    //Constructeurs
    Client(){};
    Client(int,int, QString, QString, QString,int);

    //Getters
    int getCin(){return cin;}
    int getnum(){return num;}
    int getcard(){return card;}
    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    QString getAdresseMail(){return mail;}


    //Setters
    void setCin(int cin){this->cin=cin;}
    void setnul_tel(int num){this->num=num;}
    void setNom(QString nom){this->nom=nom;}
    void setPrenom(QString prenom){this->prenom=prenom;}
    void setAdresseMail(QString mail){this->mail=mail;}
    void fid();


    //Methodes
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * rechercherNom(QString);
    QSqlQueryModel * triNom();
    QSqlQueryModel * plus(QString );
    QSqlQueryModel * plus2();
    bool update();


};

#endif // CLIENT_H
