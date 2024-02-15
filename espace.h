#ifndef ESPACE_H
#define ESPACE_H

#include <QString>
#include <QSqlQueryModel>

class Espace
{
public:
    Espace();
    Espace(int,int,QString,QString,QString);
    int getnumsalle();
    int getcapacite();
    QString getbloc();
    QString gettype();
    QString getetat();
    void setnumsalle(int);
    void setcapacite(int);
    void setbloc(QString);
    void settype(QString);
    void setetat(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int);
private:
    int numsalle,capacite;
    QString bloc,type,etat;
};

#endif // ESPACE_H
