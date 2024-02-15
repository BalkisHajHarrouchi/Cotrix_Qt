#ifndef EMPLOYES_H
#define EMPLOYES_H
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<ui_mainwindow.h>
#include<map>
class Employes
{

    QString nom,prenom,email,date_naiss,role,sexe,etat_civil,rfid,password;
    int CIN,tel,num_aff,matricule,hs,ht,conge,prix_hs,prix_ht,salaire;
    //float salaire;//prix_hs,prix_ht,
public:
    //constructeurs
    Employes();
    Employes(int,QString,QString,int,QString,int,QString,QString,QString,QString,int,QString);//int,int,float,float,float
    Employes(int,QString,QString,int,QString,int,QString,QString,QString,QString,int,int,int,int,int,int);
    //Getters
    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    int getCIN(){return CIN;}
    //setters
    void setNom(QString n){nom=n;}
    void setPrenom(QString p){prenom=p;}
    void setCIN(int CIN){this->CIN=CIN;}
    void setSalaire(int s){salaire=s;}
    //void setRFID(){"73 F4 62 A7";}

    //Fonctionnalités de base relatives à l'entité employé
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficher2();
    bool supprimer(QString);
    bool supprimer1(int);
    bool modifier(int CIN);
    bool modifier2(int CIN);
    //void Employes::login_modifier_afficher_tab(ui);
    //void login_modifier_afficher_tab(Ui::MainWindow *ui);
    bool chercher(QTableView *table,int cas );

};

#endif // EMPLOYES_H
