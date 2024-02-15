#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H

#include<QSqlQuery>
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
QT_CHARTS_USE_NAMESPACE
class Equipement
{
    QString type,nom;
    int code,quantite;
public:
    //constructeurs
    Equipement();
    Equipement(int,QString,QString,int);
    //Getters
    QString getNOM(){return nom;}
    QString getTYPE(){return type;}
    int getCODE(){return code;}
    int getQUANTITE(){return quantite;}
    //setters
    void setNOM(QString n){nom=n;}
    void setTYPE(QString t){type=t;}
    void setCODE(int c){this->code=c;}
    void setQUANTITE(int q){this->quantite=q;}
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
     bool modifier(int);
     QSqlQueryModel *chercher(int);
     QSqlQueryModel *sortid();
     QSqlQueryModel  *sortquantite();


};

#endif
