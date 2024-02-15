#include "employes.h"
#include<QSqlQuery>
#include<QtDebug>
#include<ui_mainwindow.h>
#include<QMessageBox>
#include"agent.h"
#include<iostream>
using namespace std;
Employes::Employes()
{
    ht=0;
    hs=0;
    salaire=0;
}
Employes::Employes(int CIN,QString nom,QString prenom,int tel,QString email,int num_aff,QString role,QString sexe,QString etat_civil,QString date_naiss,int matricule,QString password)
{
    this->CIN=CIN;
    this->nom=nom;
    this->prenom=prenom;
    this->tel=tel;
    this->email=email;
    this->num_aff=num_aff;
    this->role=role;
    this->sexe=sexe;
    this->etat_civil=etat_civil;
    this->date_naiss=date_naiss;
    this->matricule=matricule;
    this->password=password;
//    this->ht=ht;
//    this->hs=hs;
//    this->prix_ht=prix_ht;
//    this->prix_hs=prix_hs;
//    this->salaire=salaire;
    //this->date_naiss=date_naiss;
}
Employes::Employes(int CIN,QString nom,QString prenom,int tel,QString email,int num_aff,QString role,QString sexe,QString etat_civil,QString date_naiss,int matricule,int ht,int hs,int prix_ht,int prix_hs,int conge)//,int ht,int hs,float prix_ht,float prix_hs,float salaire
{
    this->CIN=CIN;
    this->nom=nom;
    this->prenom=prenom;
    this->tel=tel;
    this->email=email;
    this->num_aff=num_aff;
    this->role=role;
    this->sexe=sexe;
    this->etat_civil=etat_civil;
    this->date_naiss=date_naiss;
    this->matricule=matricule;
    this->ht=ht;
    this->hs=hs;
    this->prix_ht=prix_ht;
    this->prix_hs=prix_hs;
    this->conge=conge;
    this->salaire=(this->hs*this->prix_hs+this->ht*this->prix_ht);
//    this->salaire=salaire;
    //this->date_naiss=date_naiss;
}
bool Employes::ajouter()
{
   // bool test=false;
    QSqlQuery query;
   // QString CIN_string=QString::number(CIN);
          query.prepare("INSERT INTO employes (CIN, nom, prenom, num_tel, email, num_aff, role, sexe, etat_civil, matricule, date_naiss, password) ""VALUES (:CIN, :nom, :prenom, :num_tel, :email, :num_aff, :role, :sexe, :etat_civil, :matricule, :date_naiss, :password)");//ken values kbal yani lezm baedha nafs l nidham mta tableau w kemlin methode 2:
          query.bindValue(":CIN", CIN);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":num_tel", tel);
          query.bindValue(":email", email);
          query.bindValue(":num_aff", num_aff);
          query.bindValue(":role", role);
          query.bindValue(":sexe", sexe);
          query.bindValue(":etat_civil", etat_civil);
          query.bindValue(":matricule", matricule);
          query.bindValue(":date_naiss", date_naiss);
          query.bindValue(":password", password);

          return query.exec();


    //return test;
}





QSqlQueryModel *Employes::afficher(){
QSqlQueryModel *model=new QSqlQueryModel();
model->setQuery("select CIN, matricule, nom, prenom, presence, num_tel, sexe, etat_civil, email, date_naiss, num_aff,role from Employes");//pour afficher un champ specifique "select champ1 champ2 from Employes" on peut choisir l'ordre , "select * from Employes" : * pour afficher kolchay

return model;
}
QSqlQueryModel *Employes::afficher2(){
QSqlQueryModel *model2=new QSqlQueryModel();
model2->setQuery("select CIN, nom, prenom, ht, prix_ht, hs, prix_hs, conge, salaire from Employes");//pour afficher un champ specifique "select champ1 champ2 from Employes" on peut choisir l'ordre , "select * from Employes" : * pour afficher kolchay

return model2;
}
bool Employes::supprimer(QString CIN)
{


    QSqlQuery query;
    //QSqlQuery *query2=new QSqlQuery;
    //QString CIN_string=QString::number(CIN);
//    query2->prepare("select * from employes where CIN=:CIN");
//    query2->bindValue(":CIN", CIN);
//    query2->exec();
//    if(query2->numRowsAffected()==0)
//    {

//       QMessageBox::warning(nullptr, QObject::tr("database is open"),
//                   QObject::tr("employe introuvable .\n"
//                               "Click Cancel to exit."), QMessageBox::Cancel);
//       return false;

//  }
//    else{
//        query2->prepare("select * from employes where CIN=:CIN");
//        query2->exec();
//        cout<<query2->numRowsAffected();
          query.prepare("Delete from employes where CIN=:CIN");
          query.bindValue(":CIN", CIN);
          return query.exec();
    //}
}
bool Employes::supprimer1(int CIN)
{


    QSqlQuery query;
    QString CIN_string=QString::number(CIN);
          query.prepare("Delete from employes where CIN=:CIN");
          query.bindValue(":CIN", CIN);
          return query.exec();
}

bool Employes::modifier(int CIN)
{
    QSqlQuery query;
           QString res=QString::number(CIN);


             query.prepare("UPDATE employes "" SET CIN=:CIN, matricule=:matricule, nom=:nom, prenom=:prenom, num_tel=:num_tel, email=:email, num_aff=:num_aff, role=:role, sexe=:sexe, etat_civil=:etat_civil, date_naiss=:date_naiss where CIN='"+res+"' ");


                   query.bindValue(":CIN", res);//bindValue=remplir(relier) la valeur de la requette sql à partir de qt  d'une maniere sécurisée
                   query.bindValue(":matricule", matricule);
                   query.bindValue(":nom", nom);
                   query.bindValue(":prenom", prenom);
                   query.bindValue(":num_tel", tel);
                   query.bindValue(":email", email);
                   query.bindValue(":num_aff", num_aff);
                   query.bindValue(":role", role);
                   query.bindValue(":sexe", sexe);
                   query.bindValue(":etat_civil", etat_civil);
                   query.bindValue(":date_naiss", date_naiss);





               return query.exec();
}
bool Employes::modifier2(int CIN)
{
    QSqlQuery query;
           QString res=QString::number(CIN);


             query.prepare("UPDATE employes "" SET CIN=:CIN, matricule=:matricule, nom=:nom, prenom=:prenom, num_tel=:num_tel, email=:email, num_aff=:num_aff, role=:role, sexe=:sexe, etat_civil=:etat_civil, date_naiss=:date_naiss, ht=:ht, hs=:hs, prix_ht=:prix_ht, prix_hs=:prix_hs, conge=:conge, salaire=:salaire where CIN='"+res+"' ");


                   query.bindValue(":CIN", res);//bindValue=remplir(relier) la valeur de la requette sql à partir de qt  d'une maniere sécurisée
                   query.bindValue(":matricule", matricule);
                   query.bindValue(":nom", nom);
                   query.bindValue(":prenom", prenom);
                   query.bindValue(":num_tel", tel);
                   query.bindValue(":email", email);
                   query.bindValue(":num_aff", num_aff);
                   query.bindValue(":role", role);
                   query.bindValue(":sexe", sexe);
                   query.bindValue(":etat_civil", etat_civil);
                   query.bindValue(":date_naiss", date_naiss);
                   query.bindValue(":ht", ht);
                   query.bindValue(":hs", hs);
                   query.bindValue(":prix_ht", prix_ht);
                   query.bindValue(":prix_hs", prix_hs);
                   query.bindValue(":conge", conge);
                   query.bindValue(":salaire", salaire);




               return query.exec();
}
bool Employes ::chercher(QTableView *table,int CIN )
     {
         QSqlQueryModel *model= new QSqlQueryModel();

         QSqlQuery *query=new QSqlQuery;
         QString CIN_string=QString::number(CIN);

         query->prepare("SELECT * FROM employes WHERE (reference  LIKE "+CIN_string+  ")");
         query->exec();

         if(query->exec())
         {
         model->setQuery(*query);
         table->setModel(model);
         table->show();
         return true;
         }


         if(query->numRowsAffected()==0)
         {

            QMessageBox::warning(nullptr, QObject::tr("database is open"),
                        QObject::tr("employe introuvable .\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            return false;

       }

     }
/*QSqlQueryModel * Employes:: afficher_calendar(QMultiMap<QString, QString>::iterator i,QTextEdit *t)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    t->append()
    return model;
}*/



//tri : ask:ordre croissant /desc:ordre decroissant
//methode 2 selectionner l tableview et cocher sorting enabled
