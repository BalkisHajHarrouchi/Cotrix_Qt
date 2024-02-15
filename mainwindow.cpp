#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include"employes.h"
#include<QMessageBox>
#include<QDateEdit>
#include<QDate>
#include<QTextStream>
#include<QTextDocument>
#include<iostream>
#include<QPixmap>
#include<QtPrintSupport/QPrinter>
#include<QtPrintSupport/QPrintDialog>
#include<QGraphicsDropShadowEffect>
#include"smtp.h"
#include<QFileDialog>
#include<QDir>
#include"exportexcelobject.h"
#include<vector>
#include <stdlib.h>
#include <time.h>
#include<chrono>
#include<thread>
#include<map>
#include<QDesktopServices>
#include<QPdfWriter>
#include"agent.h"
#include <QIntValidator>
#include <QDesktopServices>
#include <QUrl>
#include <QApplication>
#include <QtCore>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<QGraphicsView>
#include<QtPrintSupport/QPrintDialog>
#include<QPdfWriter>
#include "qrcode.hpp"
#include <QPainter>
#include<QtSvg/QSvgRenderer>
#include <QRegExpValidator>
#include<QPdfWriter>
#include<QItemSelectionModel>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslSocket>
#include <QPrintDialog>
#include <QErrorMessage>
#include <QFile>
#include <QDataStream>
#include <QAxBase>
#include <QVariant>
#include "WebAxWidget.h"
#include <QtSvg/QSvgGenerator>
using namespace qrcodegen;
QString days="";
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //arduino
    int ret=A.connect_arduino();
    switch(ret)
    {
    case(0):qDebug()<<"arduino is available and connected to :"<<A.getarduino_port_name();
        break;
    case(1):qDebug()<<"arduino is available but not connected to :"<<A.getarduino_port_name();
        break;
    case(-1):qDebug()<<"arduino is not available";
    }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(show_from_arduino()));



    srand (time(NULL));
    //pour le mailing

    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));
    ui->tableView->setModel(Emp.afficher());
    ui->tableView_3->setModel(Emp.afficher());
    ui->affichageClient->setModel(Etmp.afficher());
    ui->le_CIN->setValidator( new QIntValidator(0, 99999999, this));




    //logo app


    QPixmap pixlogo("C:/Users/MSI/Desktop/esprit2A31/projet c++/logoapp.PNG");
    int w=ui->label_logo->width(),h=ui->label_logo->height();
    ui->label_logo->setPixmap(pixlogo.scaled(w,h,Qt::KeepAspectRatio));
    //photo de profil
    QPixmap pixetat("C:/Users/MSI/Desktop/esprit2A31/projet c++/libre.PNG");
    int wf=ui->label_etat->width(),hf=ui->label_etat->height();
    ui->label_etat->setPixmap(pixetat.scaled(wf,hf,Qt::KeepAspectRatio));
    QPixmap pixetat2("C:/Users/MSI/Desktop/esprit2A31/projet c++/ocupee.PNG");
    int wf2=ui->label_etat_2->width(),hf2=ui->label_etat_2->height();
    ui->label_etat_2->setPixmap(pixetat2.scaled(wf2,hf2,Qt::KeepAspectRatio));


    QPixmap pixpic("C:/Users/MSI/Desktop/esprit2A31/projet c++/pfp3.PNG");
    int w2=ui->label_pic->width(),h2=ui->label_pic->height();
    ui->label_pic->setPixmap(pixpic.scaled(w2,h2,Qt::KeepAspectRatio));

    //photo background

    QPixmap pixbg("C:/Users/MSI/Desktop/esprit2A31/projet c++/backg1.PNG");
    int w3=ui->label_bg_aff->width(),h3=ui->label_bg_aff->height();
    ui->label_bg_modif->setPixmap(pixbg.scaled(w3+200,h3+200,Qt::KeepAspectRatio));
    ui->label_bg_aj->setPixmap(pixbg.scaled(w3+200,h3+200,Qt::KeepAspectRatio));
    ui->label_bg_aff->setPixmap(pixbg.scaled(w3+200,h3+200,Qt::KeepAspectRatio));
    ui->label_bg_mail->setPixmap(pixbg.scaled(w3+200,h3+200,Qt::KeepAspectRatio));
    ui->label_bg_rh->setPixmap(pixbg.scaled(w3+200,h3+200,Qt::KeepAspectRatio));
    //ui->label_bg_mail_2->setPixmap(pixbg.scaled(w3,h3,Qt::KeepAspectRatio));
    ui->label_bg_mail_3->setPixmap(pixbg.scaled(w3+200,h3+200,Qt::KeepAspectRatio));
    ui->label_bg_mail_5->setPixmap(pixbg.scaled(w3+200,h3+200,Qt::KeepAspectRatio));
    QPixmap pixbgs("C:/Users/MSI/Desktop/esprit2A31/projet c++/backgss2.PNG");
    ui->label_bg_mail_4->setPixmap(pixbg.scaled(w3+200,h3+200,Qt::KeepAspectRatio));


    QPixmap pixrobot("C:/Users/MSI/Desktop/esprit2A31/projet c++/r1.PNG");
    int wr=ui->label_2->width(),hr=ui->label_2->height();
    ui->label_2->setPixmap(pixrobot.scaled(wr,hr,Qt::KeepAspectRatio));
    //equipement
    QPixmap pixaj("C:/Users/MSI/Desktop/esprit2A31/projet c++/backg1.PNG");
    int we=ui->bg_eq->width(),he=ui->bg_eq->height();
    ui->bg_eq->setPixmap(pixaj.scaled(we+200,he+200,Qt::KeepAspectRatio));
    ui->bg_eq_2->setPixmap(pixaj.scaled(we+200,he+200,Qt::KeepAspectRatio));
    ui->bg_eq_3->setPixmap(pixaj.scaled(we+200,he+200,Qt::KeepAspectRatio));
    ui->bg_eq_4->setPixmap(pixaj.scaled(we+200,he+200,Qt::KeepAspectRatio));
    ui->bg_eq_5->setPixmap(pixaj.scaled(we+200,he+200,Qt::KeepAspectRatio));
    ui->bg_eq_6->setPixmap(pixaj.scaled(we+200,he+200,Qt::KeepAspectRatio));
    ui->bg_eq_7->setPixmap(pixaj.scaled(we+200,he+200,Qt::KeepAspectRatio));
    ui->bg_eq_8->setPixmap(pixaj.scaled(we+200,he+200,Qt::KeepAspectRatio));
    ui->tableView_2->setModel(E.afficher());
    ui->tableView_4->setModel(E.afficher());

    //espace
    ui->le_numsalle->setValidator (new QIntValidator (0,999, this));
    ui->le_capacite->setValidator (new QIntValidator (0,999, this));
    ui->tab_espace->setModel(Es.afficher());
    ui->tab_espace_2->setModel(Es.afficher());

    QPixmap pixbges("C:/Users/MSI/Desktop/esprit2A31/projet c++/backg1.PNG");


                    ui->label_background4->setPixmap(pixbges.scaled(w3+200,h3+200,Qt::KeepAspectRatio));
                    ui->label_background4_2->setPixmap(pixbges.scaled(w3+200,h3+200,Qt::KeepAspectRatio));

                    QPixmap pixbg5("C:/Users/MSI/Desktop/esprit2A31/projet c++/map.PNG");
                        int wm=ui->label_background5->width(),hm=ui->label_background5->height();
                        ui->label_background5->setPixmap(pixbg5.scaled(wm,hm,Qt::KeepAspectRatio));
     //facture
                        ui->lineEdit_numfacture_2->setValidator( new QIntValidator(0, 99999 , this));
                        ui->lineEdit_prix_2->setValidator( new QIntValidator(2000, 9999, this));


                                    ui->label_bg->setPixmap(pixbg.scaled(w3+200,h3+200,Qt::KeepAspectRatio));

//client
                                    QRegExp rx("[A-Z][a-z]{0,30}");
                                    QRegExp rxM("[a-z]{0,10}@[a-z]{0,10}.[a-z]{0,10}");
                                    ui->ajouter_nom_4->setValidator(new QRegExpValidator(rxM,this));
                                    ui->ajouter_prenom_4->setValidator(new QRegExpValidator(rxM,this));
                                    //employe
                                    ui->le_nom->setValidator(new QRegExpValidator(rxM,this));
                                    ui->le_prenom->setValidator(new QRegExpValidator(rxM,this));
                                                                        ui->ajouter_cin_4->setValidator(new QIntValidator(0,99999999,this));
                                    ui->ajouter_num_4->setValidator(new QIntValidator(0,99999999,this));
                                    ui->ajouter_adresseMail_4->setValidator(new QRegExpValidator(rxM,this));
                                    ui->WebBrowser_2->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");
                                    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                                    QCoreApplication::organizationName(), QCoreApplication::applicationName());

                                        QBarSet *set0 = new QBarSet("num");
                                        *set0 << 1 << 2 << 3 ;
                                        QBarSeries *series = new QBarSeries();
                                        series->append(set0);
                                        QChart *chart = new QChart();
                                        chart->addSeries(series);
                                        chart->setTitle("statistiques des numeros de telph");
                                        chart->setAnimationOptions(QChart::SeriesAnimations);
                                        QStringList categories;
                                        categories << "orange" << "ooredoo" << "telecom" ;
                                        QBarCategoryAxis *axis = new QBarCategoryAxis();
                                        axis->append(categories);
                                        chart->createDefaultAxes();
                                        chart->setAxisX(axis, series);
                                        QChartView *chartView = new QChartView(chart);
                                        chartView->setParent(ui->horizontalFrame_2);
                                        ui->label_69->setPixmap(pixaj.scaled(w3+200,h3+200,Qt::KeepAspectRatio));
                                        ui->label_75->setPixmap(pixaj.scaled(w3+200,h3+200,Qt::KeepAspectRatio));
                                        ui->label_76->setPixmap(pixaj.scaled(w3+200,h3+200,Qt::KeepAspectRatio));
                                        ui->label_78->setPixmap(pixaj.scaled(w3+200,h3+200,Qt::KeepAspectRatio));



    //connect

//    QObject::connect(ui->pb_afficher,&QPushButton::clicked,this,&MainWindow::on_pb_afficher_clicked);
//    QObject::connect(ui->pb_modifier,&QPushButton::clicked,this,&MainWindow::on_pb_modifier_clicked);
//    QObject::connect(ui->pb_supprimer,&QPushButton::clicked,this,&MainWindow::on_pb_supprimer_clicked);
//    QObject::connect(ui->pb_finance,&QPushButton::clicked,this,&MainWindow::on_pb_finance_clicked);
//    QObject::connect(ui->tableView,&QTableView::clicked,this,&MainWindow::on_tableView_clicked);

//    QObject::connect(ui->pb_rh,&QPushButton::clicked,this,&MainWindow::on_pb_rh_clicked);
//    QObject::connect(ui->pb_client,&QPushButton::clicked,this,&MainWindow::on_pb_client_clicked);
//    QObject::connect(ui->pb_espace,&QPushButton::clicked,this,&MainWindow::on_pb_espace_clicked);
//    //QObject::connect(ui->pb_equip,&QPushButton::clicked,this,&MainWindow::on_pb_equip_clicked);
//    QObject::connect(ui->le_CINa,&QLineEdit::textChanged,this,&MainWindow::on_le_CINa_textChanged);
//    QObject::connect(ui->le_CINs,&QLineEdit::textChanged,this,&MainWindow::on_le_CINs_textChanged);
//    QObject::connect(ui->comboBox_19,&QComboBox::currentTextChanged,this,&MainWindow::on_comboBox_19_currentTextChanged);

//    QObject::connect(ui->pb_imprimer,&QPushButton::clicked,this,&MainWindow::on_pb_imprimer_clicked);
//    QObject::connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
//    QObject::connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));
//    QObject::connect(ui->pb_camera,&QPushButton::clicked,this,&MainWindow::on_pb_camera_clicked);

//QObject::connect(ui->tableView_rh,&QTableView::clicked,this,&MainWindow::on_tableView_rh_clicked);
// QObject::connect(ui->pushButton_2,&QPushButton::clicked,this,&MainWindow::on_pushButton_2_clicked);
// QObject::connect(ui->pb_excel,&QPushButton::clicked,this,&MainWindow::on_pb_excel_clicked);
// QObject::connect(ui->comboBox_rh,&QComboBox::currentTextChanged,this,&MainWindow::on_comboBox_rh_currentTextChanged);
//QObject::connect(ui->le_CINa_2,&QLineEdit::textChanged,this,&MainWindow::on_le_CINa_2_textChanged);
//QObject::connect(ui->pushButton_19,&QPushButton::clicked,this,&MainWindow::on_pushButton_19_clicked);

//QObject::connect(ui->tabWidget_rh,&QTabWidget::currentChanged,this,&MainWindow::on_tabWidget_rh_currentChanged);
//QObject::connect(ui->tabWidget_rh,&QTabWidget::tabBarClicked,this,&MainWindow::on_tabWidget_rh_tabBarClicked);
//QObject::connect(ui->notepad,&QPushButton::clicked,this,&MainWindow::on_notepad_clicked);
//QObject::connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::on_pushButton_clicked);
//QObject::connect(ui->pushButton_3,&QPushButton::clicked,this,&MainWindow::on_pushButton_3_clicked);

//************************
Agent ag;
QString res1,r=ag.getid();
QSqlQuery qry;
/*qry.prepare("select * from agent where username='"+r+"' " );
if(qry.exec())
{
    while(qry.next())
    {
        res1=qry.value(2).toString();

    }
}
if(res1=="directer"){
    ui->tableView_4->setModel(hismp.afficher());

    ui->tableView_4->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);}
else{
    ui->tableView_4->setModel(hismp.afficheragent(a.getid()));

    ui->tableView_4->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);}*/

if(ag.role()==0){
    ui->pb_rh->setGeometry(10, 140, 180, 80);
    ui->tabWidget_rh->show();
    ui->tabWidget_es->hide();
    ui->tabWidget_cl->hide();
    ui->tabWidget_eq->hide();
    ui->tabWidget_fa->hide();
    ui->pb_finance->hide();
    ui->pb_client->hide();
    ui->pb_espace->hide();
    ui->pb_equip->hide();

}
else if(ag.role()==1){
    ui->tabWidget_rh->hide();
    ui->tabWidget_es->hide();
    ui->tabWidget_cl->hide();
    ui->tabWidget_eq->hide();
    ui->tabWidget_fa->show();
    ui->pb_rh->hide();
    ui->pb_finance->setGeometry(10, 140, 180, 80);
    ui->pb_finance->show();
    ui->pb_client->hide();
    ui->pb_espace->hide();
    ui->pb_equip->hide();


}
else if(ag.role()==2){
    ui->tabWidget_cl->show();
    ui->tabWidget_rh->hide();
    ui->tabWidget_es->hide();
    ui->tabWidget_eq->hide();
    ui->tabWidget_fa->hide();
    ui->pb_rh->hide();
    ui->pb_finance->hide();
    ui->pb_client->setGeometry(10, 140, 180, 80);
    ui->pb_client->show();
    ui->pb_espace->hide();
    ui->pb_equip->hide();
}
else if(ag.role()==3){
    ui->tabWidget_rh->hide();
    ui->tabWidget_cl->hide();
    ui->tabWidget_eq->hide();
    ui->tabWidget_fa->hide();
    ui->tabWidget_es->show();
    ui->pb_rh->hide();
    ui->pb_finance->hide();
    ui->pb_client->hide();
    ui->pb_espace->setGeometry(10, 140, 180, 80);
    ui->pb_espace->show();
    ui->pb_equip->hide();

}
else if(ag.role()==4){
    ui->tabWidget_eq->show();
    ui->tabWidget_rh->hide();
    ui->tabWidget_cl->hide();
    ui->tabWidget_es->hide();
    ui->tabWidget_fa->hide();
    ui->pb_rh->hide();
    ui->pb_finance->hide();
    ui->pb_client->hide();
    ui->pb_espace->hide();
    ui->pb_equip->setGeometry(10, 140, 180, 80);
    ui->pb_equip->show();

}
else if(ag.role()==5)
{
    ui->tabWidget_rh->show();
    ui->tabWidget_eq->hide();
    ui->tabWidget_es->hide();
    ui->tabWidget_cl->hide();
    ui->tabWidget_fa->hide();
    ui->pb_rh->show();
    ui->pb_rh->setChecked(true);
    ui->pb_finance->show();
    ui->pb_client->show();
    ui->pb_espace->show();
    ui->pb_equip->show();

}
else
    QMessageBox::critical(nullptr,QObject::tr("Connection failed"),QObject::tr("Unvalid mail or password"),QMessageBox::Cancel);

}
//***********************************************



MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::on_pushButton_clicked()
{
   qDebug()<<"boutton ajouter personne appuye";
}*/

/*void MainWindow::on_pushButton_2_clicked()
{
   qDebug()<<"boutton afficher personne appuye";
   //ui->tableView->setModel(Emp.afficher());
}*/

void MainWindow::on_pb_ajouter_clicked()
{
    int CIN=ui->le_CIN->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    int tel=ui->le_tel->text().toInt();
    QString email=ui->le_email->text();
    int num_aff=ui->le_num_aff->text().toInt();
    //QString value = box_role.comboBox.currentText();
    //QString role=ui->box_role->itemData(ui->box_role->currentIndex()).toString();
    QString role = ui->box_role->currentText();
    QString sexe = ui->box_sexe->currentText();
    QString etat_civil = ui->box_etat_civil->currentText();
    QString date = ui->dateEdit->dateTime().toString("dd/MM/yyyy");
    int matricule=ui->le_matricule->text().toInt();
    QString password = ui->le_pwd->text();
    //unicite de CIN to do
    //bool unique=Emp.chercher(ui->tableView_3,CIN);
    /*if(unique==true)
    {
       QMessageBox::critical(nullptr,QObject::tr("not OK"),QObject::tr("Employe existe deja\n""Click Cancel to exit."),QMessageBox::Cancel);
    }
    else
    {*/
    Employes E(CIN,nom,prenom,tel,email,num_aff,role,sexe,etat_civil,date,matricule,password);
    QString mat=QString::number(matricule);
    Agent a(mat,password,role,"0");
    a.ajouter();
    bool test=E.ajouter();

    if(test)
    {
        ui->tableView->setModel(Emp.afficher());
        ui->tableView_3->setModel(Emp.afficher());
        QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Ajout effectué\n""Click Cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),QObject::tr("Ajouter non effectué\n""Click Cancel to exit."),QMessageBox::Cancel);
  //  }
    qDebug()<<QSslSocket::supportsSsl() << QSslSocket::sslLibraryBuildVersionString() << QSslSocket::sslLibraryVersionString();
}

void MainWindow::on_pb_supprimer_clicked()
{
    QModelIndex index=ui->tableView->currentIndex();
    int i;
    i=index.row();
    QModelIndex in=index.sibling(i,0);
    QString val=ui->tableView->model()->data(in).toString();

    int CIN=ui->le_CINs->text().toInt();
    QString sCIN=ui->le_CINs->text();
    if(val==NULL && CIN==NULL)
    {
       QMessageBox::critical(nullptr,QObject::tr("Not ok"),QObject::tr("Veuillez selectionner ou taper le code de l'employe que vous voulez supprimer"),QMessageBox::Cancel);
    }

    else{
        //
        QString CIN_string=QString::number(CIN);
        QSqlQuery queryc;
        QSqlQueryModel *modelc= new QSqlQueryModel();
        queryc.prepare("SELECT * FROM employes WHERE (CIN  LIKE "+CIN_string+  ")");
        if(queryc.exec()){
           modelc->setQuery(queryc);
           }
        if(queryc.numRowsAffected()==0){QMessageBox::warning(nullptr, QObject::tr("Erreur de suppression"),
                                                                   QObject::tr("Employe introuvable .\n"
                                                                               "Click Cancel to exit."), QMessageBox::Cancel);}



       else{
            QMessageBox::StandardButton reply;
              reply = QMessageBox::question(this, "Supprimer", "Supprimer cet employe?",
                                            QMessageBox::Yes|QMessageBox::No);
              if (reply == QMessageBox::Yes) {
                qDebug() << "Yes was clicked";
                bool test=Emp.supprimer(val);
                bool test1=Emp.supprimer1(CIN);



                if(test)
                    {
                        ui->tableView->setModel(Emp.afficher());
                        ui->tableView_3->setModel(Emp.afficher());
                        QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Suppression effectué\n""Click Cancel to exit."),QMessageBox::Cancel);
                    }
                else if(!test)
                        QMessageBox::critical(nullptr,QObject::tr("Not ok"),QObject::tr("Suppression non effectué\n""Click Cancel to exit."),QMessageBox::Cancel);
                else if(test1)
                    {
                        ui->tableView->setModel(Emp.afficher());
                        ui->tableView_3->setModel(Emp.afficher());
                        QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Suppression effectué\n""Click Cancel to exit."),QMessageBox::Cancel);
                    }
                    else
                        QMessageBox::critical(nullptr,QObject::tr("Not ok"),QObject::tr("Suppression non effectué\n""Click Cancel to exit."),QMessageBox::Cancel);
              } else {
                qDebug() << "Yes was *not* clicked";
              }

}}
}


void MainWindow::on_pb_modifier_clicked()
{
        int CIN=ui->le_CIN_m->text().toInt();
        QString nom=ui->le_nom_m->text();
        QString prenom=ui->le_prenom_m->text();
        int tel=ui->le_tel_m->text().toInt();
        QString email=ui->le_email_m->text();
        int num_aff=ui->le_num_aff_m->text().toInt();
        //QString role=ui->box_role->itemData(ui->box_role->currentIndex()).toString();
        QString role = ui->box_role_2->currentText();
        QString sexe = ui->box_sexe_2->currentText();
        QString etat_civil = ui->box_etat_civil_2->currentText();
        QString date = ui->dateEdit_3->dateTime().toString("dd/MM/yyyy");
        int matricule=ui->le_matricule_2->text().toInt();
        QString password=ui->le_pwd_m->text();
        Employes Em(CIN,nom,prenom,tel,email,num_aff,role,sexe,etat_civil,date,matricule,password);
        bool test=Em.modifier(CIN);
        ui->tableView->setModel(Emp.afficher());
        ui->tableView_3->setModel(Emp.afficher());
     if(test){

        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("modification effectué \n""Click Cancel to exit"),QMessageBox::Cancel);
        //cout<<"aaaaa";
//        ui->le_CIN_m->clear();
//        ui->le_nom_m->clear();
//        ui->le_prenom_m->clear();
//        ui->le_tel_m->clear();
//        ui->le_email_m->clear();
//        ui->le_num_aff_m->clear();
//        ui->box_role_2->clear();
//        ui->box_sexe_2->clear();
//        ui->box_etat_civil_2->clear();
//        ui->dateEdit_3->clear();
//        ui->le_matricule_2->clear();
    }else{
         QMessageBox::information(nullptr,QObject::tr("NOT OK"),
                                  QObject::tr("modification non effectué \n""Click Cancel to exit"),QMessageBox::Cancel);



     }



}
// pie chart fl select * rodha count
//check readme , smtp.h(NO NOT CHANGE ANTHING)
//close();

void MainWindow::on_pb_afficher_clicked()
{
    ui->tableView->setModel(Emp.afficher());
    ui->tableView_3->setModel(Emp.afficher());
    ui->tableView_rh->setModel(Emp.afficher2());
}



/*void MainWindow::on_pb_rh_clicked()
{
//    ui->tabWidget_rh->show();
//    //ui->pb_rh->setChecked(false);
//    ui->pb_finance->setChecked(false);
//    ui->pb_client->setChecked(false);
//    ui->pb_espace->setChecked(false);
//    ui->pb_equip->setChecked(false);
}*/

void MainWindow::on_pb_finance_clicked()
{
    ui->tabWidget_rh->hide();
    ui->tabWidget_eq->hide();
    ui->tabWidget_cl->hide();
    ui->tabWidget_es->hide();
    ui->tabWidget_fa->show();
    ui->pb_rh->setChecked(false);
    //ui->pb_finance->setChecked(false);
    ui->pb_client->setChecked(false);
    ui->pb_espace->setChecked(false);
    ui->pb_equip->setChecked(false);
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int i;
    i=index.row();
    QModelIndex in=index.sibling(i,0);
    QString val=ui->tableView->model()->data(in).toString();


    //QString val=ui->tableView->model()->data(index).toString();

        QSqlQuery qry;
        qry.prepare("select * from employes where CIN='"+val+"' or nom='"+val+"' or prenom='"+val+"' or num_tel='"+val+"' or email='"+val+"' or num_aff='"+val+"'or matricule='"+val+"'or password='"+val+"' " );

        if(qry.exec())
        {
            while(qry.next())
            {
                ui->le_CIN_m->setText(qry.value(0).toString());
                ui->le_nom_m->setText(qry.value(2).toString());
                ui->le_prenom_m->setText(qry.value(3).toString());
                ui->le_tel_m->setText(qry.value(4).toString());
                ui->le_email_m->setText(qry.value(7).toString());
                ui->le_num_aff_m->setText(qry.value(9).toString());
                ui->box_role_2->setCurrentText(qry.value(10).toString());
                ui->box_sexe_2->setCurrentText(qry.value(5).toString());
                ui->box_etat_civil_2->setCurrentText(qry.value(6).toString());
                ui->le_matricule_2->setText(qry.value(1).toString());
                ui->le_pwd_m->setText(qry.value(18).toString());

            }
    }
}


void MainWindow::on_pb_client_clicked()
{
    ui->tabWidget_cl->show();
    ui->tabWidget_rh->hide();
    ui->tabWidget_eq->hide();
    ui->tabWidget_es->hide();
    ui->tabWidget_fa->hide();
    ui->pb_rh->setChecked(false);
    ui->pb_finance->setChecked(false);
    //ui->pb_client->setChecked(false);
    ui->pb_espace->setChecked(false);
    ui->pb_equip->setChecked(false);
}

void MainWindow::on_pb_espace_clicked()
{
    ui->tabWidget_es->show();
    ui->tabWidget_rh->hide();
    ui->tabWidget_fa->hide();
    ui->tabWidget_cl->hide();
    ui->tabWidget_eq->hide();
    ui->pb_rh->setChecked(false);
    ui->pb_finance->setChecked(false);
    ui->pb_client->setChecked(false);
    //ui->pb_espace->setChecked(false);
    ui->pb_equip->setChecked(false);
}

void MainWindow::on_pb_equip_clicked()
{
    ui->tabWidget_rh->hide();
    ui->tabWidget_cl->hide();
    ui->tabWidget_es->hide();
    ui->tabWidget_fa->hide();
    ui->tabWidget_eq->show();
    ui->pb_rh->setChecked(false);
    ui->pb_finance->setChecked(false);
    ui->pb_client->setChecked(false);
    ui->pb_espace->setChecked(false);
    //ui->pb_equip->setChecked(false);
}

void MainWindow::on_le_CINa_textChanged(const QString &arg1)
{
    QSqlQueryModel * modal= new QSqlQueryModel ();
        QSqlQuery*qry=new QSqlQuery();
        QString CIN=ui->le_CINa->text();


        if(CIN.isEmpty())
        {
            ui->tableView_3->setModel(Emp.afficher());

        }
        else
        {

            qry->prepare ("SELECT CIN, matricule, nom, prenom, num_tel, sexe, etat_civil, email, date_naiss, num_aff,role from Employes where ( CIN LIKE'%"+CIN+"%' OR nom LIKE'%"+CIN+"%' OR prenom LIKE'%"+CIN+"%'OR matricule LIKE'%"+CIN+"%') ");
            qry->exec();
            modal->setQuery(*qry);
            ui->tableView_3->setModel(modal);

        }
}

void MainWindow::on_le_CINs_textChanged(const QString &arg1)
{
    QSqlQueryModel * modal= new QSqlQueryModel ();
        QSqlQuery*qry=new QSqlQuery();
        QString CIN=ui->le_CINs->text();


        if(CIN.isEmpty())
        {
            ui->tableView->setModel(Emp.afficher());

        }
        else
        {
            //
            qry->prepare ("SELECT CIN, matricule, nom, prenom, num_tel, sexe, etat_civil, email, date_naiss, num_aff,role from Employes where ( CIN LIKE'%"+CIN+"%' OR nom LIKE'%"+CIN+"%' OR prenom LIKE'%"+CIN+"%'OR matricule LIKE'%"+CIN+"%') ");
            qry->exec();
            modal->setQuery(*qry);
            ui->tableView->setModel(modal);
            //qry->prepare("select * from employes where CIN='"+CIN+"'"); //like
            //qry->exec();
            //modal->setQuery(*qry);
            //ui->tableView_3->setModel(modal);
        }
}
//recherche dynamique
void MainWindow::on_comboBox_19_currentTextChanged(const QString &arg1)
{
    QSqlQueryModel * model= new QSqlQueryModel ();
        QSqlQuery*qry=new QSqlQuery();
        QString type=ui->comboBox_19->currentText();
        if (type=="Par defaut")
        {
            qry->prepare("select * from EMPLOYES");
            qry->exec();
            model->setQuery(*qry);
            ui->tableView_3->setModel(model);
        }
            else if (type=="CIN"){
            qry->prepare("select * from EMPLOYES order by CIN");
            qry->exec();
            model->setQuery(*qry);

                ui->tableView_3->setModel(model);


            }
            else if (type=="Matricule"){
            qry->prepare("select * from EMPLOYES order by matricule");
            qry->exec();
            model->setQuery(*qry);

                ui->tableView_3->setModel(model);


            }
            else if (type=="Nom"){
            qry->prepare("select * from EMPLOYES order by nom");
            qry->exec();
            model->setQuery(*qry);

                ui->tableView_3->setModel(model);
            }
        else if (type=="Prenom"){
        qry->prepare("select * from EMPLOYES order by prenom");
        qry->exec();
        model->setQuery(*qry);

            ui->tableView_3->setModel(model);
        }
}
//trie
void MainWindow::on_comboBox_5_currentTextChanged(const QString &arg1)
{
    QSqlQueryModel * model= new QSqlQueryModel ();
        QSqlQuery*qry=new QSqlQuery();
        QString type=ui->comboBox_5->currentText();
        if (type=="Par defaut")
        {
            qry->prepare("select * from EMPLOYES");
            qry->exec();
            model->setQuery(*qry);
            ui->tableView->setModel(model);
        }
            else if (type=="CIN"){
            qry->prepare("select * from EMPLOYES order by CIN");
            qry->exec();
            model->setQuery(*qry);

                ui->tableView->setModel(model);


            }
            else if (type=="Matricule"){
            qry->prepare("select * from EMPLOYES order by matricule");
            qry->exec();
            model->setQuery(*qry);

                ui->tableView->setModel(model);


            }
            else if (type=="Nom"){
            qry->prepare("select * from EMPLOYES order by lower (nom)");
            qry->exec();
            model->setQuery(*qry);

                ui->tableView->setModel(model);
            }
        else if (type=="Prenom"){
        qry->prepare("select * from EMPLOYES order by lower (prenom)");
        qry->exec();
        model->setQuery(*qry);

            ui->tableView->setModel(model);
        }
}


//generation pdf
void MainWindow::on_pb_imprimer_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView->model()->rowCount();
    const int columnCount = ui->tableView->model()->columnCount();



    out <<  "<html>\n"
        "<head >\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("col1")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<table border=1 cellspacing=0 cellpadding=1>\n";

    // headers color
    out << "<thead><tr bgcolor=#9F8EC3>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView->isColumnHidden(column)) {
                QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                //table values color
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete document;


}
//mail
void  MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}
void   MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("balkis.hajharrouchi@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("balkis.hajharrouchi@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("balkis.hajharrouchi@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}




void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}
//camera : the taken image is in the computer "images"
void MainWindow::on_pb_camera_clicked()
{
    c= new camera();
    c->show();
}

//tableau de bord rh
void MainWindow::on_tableView_rh_clicked(const QModelIndex &index)
{
    int i;
    i=index.row();
    QModelIndex in=index.sibling(i,0);
    QString val=ui->tableView_rh->model()->data(in).toString();


    //QString val=ui->tableView->model()->data(index).toString();

        QSqlQuery qry;
        qry.prepare("select * from employes where CIN='"+val+"' or nom='"+val+"' or prenom='"+val+"' or num_tel='"+val+"' or email='"+val+"' or num_aff='"+val+"'or matricule='"+val+"' or ht='"+val+"' or hs='"+val+"' or prix_ht='"+val+"' or prix_hs='"+val+"'or conge='"+val+"'or salaire='"+val+"' " );

        if(qry.exec())
        {
            while(qry.next())
            {
                ui->le_CIN_h->setText(qry.value(0).toString());
                ui->le_nom_h->setText(qry.value(2).toString());
                ui->le_prenom_h->setText(qry.value(3).toString());
                ui->le_tel_h->setText(qry.value(4).toString());
                ui->le_email_h->setText(qry.value(7).toString());
                ui->le_num_aff_h->setText(qry.value(9).toString());
                ui->box_role_2->setCurrentText(qry.value(10).toString());
                ui->box_sexe_2->setCurrentText(qry.value(5).toString());
                ui->box_etat_civil_2->setCurrentText(qry.value(6).toString());
                ui->le_matricule_h->setText(qry.value(1).toString());

                ui->le_ht->setText(qry.value(11).toString());
                ui->le_prix_ht->setText(qry.value(13).toString());
                ui->le_hs->setText(qry.value(12).toString());
                ui->le_prix_hs->setText(qry.value(14).toString());
                ui->le_conge->setText(qry.value(15).toString());
                ui->le_salaire->setText(qry.value(16).toString());

            }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    int CIN=ui->le_CIN_h->text().toInt();
    QString nom=ui->le_nom_h->text();
    QString prenom=ui->le_prenom_h->text();
    int tel=ui->le_tel_h->text().toInt();
    QString email=ui->le_email_h->text();
    int num_aff=ui->le_num_aff_h->text().toInt();
    //QString role=ui->box_role->itemData(ui->box_role->currentIndex()).toString();
    QString role = ui->box_role_2->currentText();
    QString sexe = ui->box_sexe_2->currentText();
    QString etat_civil = ui->box_etat_civil_2->currentText();
    QString date = ui->dateEdit_3->dateTime().toString("dd/MM/yyyy");
    int matricule=ui->le_matricule_2->text().toInt();

    int hs=ui->le_hs->text().toInt();
    int ht=ui->le_ht->text().toInt();
    int prix_ht=ui->le_prix_ht->text().toInt();
    int prix_hs=ui->le_prix_hs->text().toInt();
    int conge=ui->le_conge->text().toInt();
    //int salaire=(hs*prix_hs+ht*prix_ht-conge);
    Employes E(CIN,nom,prenom,tel,email,num_aff,role,sexe,etat_civil,date,matricule,ht,hs,prix_ht,prix_hs,conge);

    bool test=E.modifier2(CIN);
    //E.setSalaire(salaire);
    ui->tableView->setModel(Emp.afficher());
    ui->tableView_3->setModel(Emp.afficher());
    ui->tableView_rh->setModel(Emp.afficher2());
 if(test){

    QMessageBox::information(nullptr,QObject::tr("OK"),
                             QObject::tr("modification effectué \n""Click Cancel to exit"),QMessageBox::Cancel);
}else{
     QMessageBox::information(nullptr,QObject::tr("NOT OK"),
                              QObject::tr("modification non effectué \n""Click Cancel to exit"),QMessageBox::Cancel);


 }
}
//export excel
void MainWindow::on_pb_excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "Tableau de bord RH", ui->tableView_rh);

    //colums to export
    obj.addField(0, "CIN", "char(30)");
    obj.addField(1, "Nom", "char(30)");
    obj.addField(2, "Prenom", "char(30)");
    obj.addField(3, "HT", "char(30)");
    obj.addField(4, "Prix_HT", "char(30)");
    obj.addField(5, "HS", "char(30)");
    obj.addField(6, "Prix_HS", "char(30)");
    obj.addField(7, "Conge", "char(30)");
    obj.addField(8, "Salaire", "char(30)");


    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}

void MainWindow::on_comboBox_rh_currentTextChanged(const QString &arg1)
{
    QSqlQueryModel * model= new QSqlQueryModel ();
        QSqlQuery*qry=new QSqlQuery();
        QString type=ui->comboBox_rh->currentText();
        if (type=="Par defaut")
        {
            qry->prepare("select CIN, nom, prenom, ht, prix_ht, hs, prix_hs, conge, salaire from Employes");
            qry->exec();
            model->setQuery(*qry);
            ui->tableView_rh->setModel(model);
        }
            else if (type=="CIN"){
            qry->prepare("select CIN, nom, prenom, ht, prix_ht, hs, prix_hs, conge, salaire from Employes order by CIN");
            qry->exec();
            model->setQuery(*qry);

                ui->tableView_rh->setModel(model);


            }
        else if (type=="Salaire"){
        qry->prepare("select CIN, nom, prenom, ht, prix_ht, hs, prix_hs, conge, salaire from Employes order by Salaire");
        qry->exec();
        model->setQuery(*qry);

            ui->tableView_rh->setModel(model);
        }
}

void MainWindow::on_le_CINa_2_textChanged(const QString &arg1)
{
    QSqlQueryModel * modal= new QSqlQueryModel ();
        QSqlQuery*qry=new QSqlQuery();
        QString CIN=ui->le_CINa_2->text();


        if(CIN.isEmpty())
        {
            ui->tableView_rh->setModel(Emp.afficher2());

        }
        else
        {
            //
            qry->prepare ("SELECT CIN, nom, prenom, ht, prix_ht, hs, prix_hs, conge, salaire from Employes where ( CIN LIKE'%"+CIN+"%' OR nom LIKE'%"+CIN+"%' OR prenom LIKE'%"+CIN+"%'OR ht LIKE'%"+CIN+"%'OR hs LIKE'%"+CIN+"%') ");
            qry->exec();
            modal->setQuery(*qry);
            ui->tableView_rh->setModel(modal);

        }
}

void MainWindow::on_pushButton_19_clicked()
{
    {
        QString imageFile = QFileDialog ::getOpenFileName(0,"Select Image","/home/","Image Files (*.png)");

          QFileInfo info(imageFile);
        QFileInfo  filename = info.fileName(); //path de l'image

        QPixmap image (imageFile);
          ui->label_pic->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
          image = image.scaled(110,110,Qt::IgnoreAspectRatio,Qt::FastTransformation);
          ui->label_pic->setPixmap(image);
          ui->label_pic->show();

    qDebug()<<QSslSocket::supportsSsl() << QSslSocket::sslLibraryBuildVersionString() << QSslSocket::sslLibraryVersionString();

    //************************************************************************************************************************

    }



    }


//chatBot
void MainWindow::on_pushButton_clicked()
{
    //ui->plainTextEdit->toPlainText();
    QString text,space="";
    QString msg=ui->input->text();
    ui->output->appendPlainText(space);
    ui->output->appendPlainText(msg);
    ui->input->clear();
    QString chemin;



    if(msg=="hi"||msg=="hey"||msg=="yo"){
        QPixmap pixrobot("C:/Users/MSI/Desktop/esprit2A31/projet c++/r1.PNG");
        int wr=ui->label_2->width(),hr=ui->label_2->height();
        ui->label_2->setPixmap(pixrobot.scaled(wr,hr,Qt::KeepAspectRatio));
        text="Hello user, i'm B.E.M.O your chat assistant you can call me Bemo :) ";

    }
    else if(msg=="hello"||msg=="hallo"||msg=="heyo"||msg=="sup")
    {
        QPixmap pixrobot("C:/Users/MSI/Desktop/esprit2A31/projet c++/r1.PNG");
        int wr=ui->label_2->width(),hr=ui->label_2->height();
        ui->label_2->setPixmap(pixrobot.scaled(wr,hr,Qt::KeepAspectRatio));

        text="hey there , how are you feeling today? ";
    }
    else if(msg=="help")
    {
        QPixmap pixrobot("C:/Users/MSI/Desktop/esprit2A31/projet c++/r6.PNG");
        int wr=ui->label_2->width(),hr=ui->label_2->height();
        ui->label_2->setPixmap(pixrobot.scaled(wr,hr,Qt::KeepAspectRatio));
        text=" what's wrong? How can i help you?";
    }
    else if(msg=="calculator" ||msg=="calcul")
    {
        QPixmap pixrobot("C:/Users/MSI/Desktop/esprit2A31/projet c++/r5.PNG");
        int wr=ui->label_2->width(),hr=ui->label_2->height();
        ui->label_2->setPixmap(pixrobot.scaled(wr,hr,Qt::KeepAspectRatio));
        text=" Oh sorry ,i can't do maths but there's already a scientific calculator in the finance space";
    }
    else if(msg=="how are you" ||msg=="hru")
    {
        QPixmap pixrobot("C:/Users/MSI/Desktop/esprit2A31/projet c++/r2.PNG");
        int wr=ui->label_2->width(),hr=ui->label_2->height();
        ui->label_2->setPixmap(pixrobot.scaled(wr,hr,Qt::KeepAspectRatio));
        text="I'm great thank you for asking and how are you! I hope you're doing great";
    }
    else if(msg=="good" ||msg=="great"||msg=="i'm great"||msg=="i'm good"||msg=="doing great")
    {
        QPixmap pixrobot("C:/Users/MSI/Desktop/esprit2A31/projet c++/r2.PNG");
        int wr=ui->label_2->width(),hr=ui->label_2->height();
        ui->label_2->setPixmap(pixrobot.scaled(wr,hr,Qt::KeepAspectRatio));

        text="Good to hear dear employee, have a good day";
    }
    else if(msg=="how to export an excel file" ||msg=="excel")
    {
        QPixmap pixrobot("C:/Users/MSI/Desktop/esprit2A31/projet c++/r4.PNG");
        int wr=ui->label_2->width(),hr=ui->label_2->height();
        ui->label_2->setPixmap(pixrobot.scaled(wr,hr,Qt::KeepAspectRatio));
        text="Go to ""tableau de bord RH"" and click on the button ""exporter""";
    }
    else if(msg=="how to generate a pdf" ||msg=="pdf")
    {
        QPixmap pixrobot("C:/Users/MSI/Desktop/esprit2A31/projet c++/r4.PNG");
        int wr=ui->label_2->width(),hr=ui->label_2->height();
        ui->label_2->setPixmap(pixrobot.scaled(wr,hr,Qt::KeepAspectRatio));
        text="Go to ""Afficher employe"" and click on the button ""imprimer""";
    }
    else if(msg=="sorry" ||msg=="excuse me")
    {
        QPixmap pixrobot("C:/Users/MSI/Desktop/esprit2A31/projet c++/r1.PNG");
        int wr=ui->label_2->width(),hr=ui->label_2->height();
        ui->label_2->setPixmap(pixrobot.scaled(wr,hr,Qt::KeepAspectRatio));
        text="Don't worry about it friend";
    }
    else if(msg=="tell me" ||msg=="talk")
    {
        QPixmap pixrobot("C:/Users/MSI/Desktop/esprit2A31/projet c++/r2.PNG");
        int wr=ui->label_2->width(),hr=ui->label_2->height();
        ui->label_2->setPixmap(pixrobot.scaled(wr,hr,Qt::KeepAspectRatio));
        text="Waht do you want to talk about mate? need help in somthing? or just company?";
    }
    else if(msg=="money" ||msg=="salary")
    {
        QPixmap pixrobot("C:/Users/MSI/Desktop/esprit2A31/projet c++/r4.PNG");
        int wr=ui->label_2->width(),hr=ui->label_2->height();
        ui->label_2->setPixmap(pixrobot.scaled(wr,hr,Qt::KeepAspectRatio));
        text="We all want money don't we? work hard until you deserve it!";
    }
    else if(msg=="bored" ||msg=="i'm bored")
    {
        QPixmap pixrobot("C:/Users/MSI/Desktop/esprit2A31/projet c++/r6.PNG");
        int wr=ui->label_2->width(),hr=ui->label_2->height();
        ui->label_2->setPixmap(pixrobot.scaled(wr,hr,Qt::KeepAspectRatio));
        text="Sorry for that , a cup of coffee would help i guess!";
    }
    else if(msg=="thanks" ||msg=="thank you")
    {
        QPixmap pixrobot("C:/Users/MSI/Desktop/esprit2A31/projet c++/r3.PNG");
        int wr=ui->label_2->width(),hr=ui->label_2->height();
        ui->label_2->setPixmap(pixrobot.scaled(wr,hr,Qt::KeepAspectRatio));
        text="You're welcome i'm alwasy at your service";
    }
    else if(msg=="fuck you" ||msg=="shit"||msg=="fuck"||msg=="damn"||msg=="stupid"||msg=="idiot")
    {
        QPixmap pixrobot("C:/Users/MSI/Desktop/esprit2A31/projet c++/r7.PNG");
        int wr=ui->label_2->width(),hr=ui->label_2->height();
        ui->label_2->setPixmap(pixrobot.scaled(wr,hr,Qt::KeepAspectRatio));
        text="How dare you!Please Do not use cursing words it can hurt others like it did to me!";
    }
    else if(msg=="you are sweet" )
    {
        QPixmap pixrobot("C:/Users/MSI/Desktop/esprit2A31/projet c++/r2.PNG");
        int wr=ui->label_2->width(),hr=ui->label_2->height();
        ui->label_2->setPixmap(pixrobot.scaled(wr,hr,Qt::KeepAspectRatio));
        text="Arigato! Don't tell the others i'm only this sweet with you";
    }
    else if(msg=="i love you" ||msg=="i like you")
    {
        vector<QString>v;
        v.push_back("I love you too <3");
        v.push_back("Oww you're so sweet i love you too");
        v.push_back("Don't tell others, you're my favourite mate ^^ love you~");
        v.push_back("! I love you too, yaay now i finally have a best friend^^");

        int i = rand() % 4;

        QPixmap pixrobot("C:/Users/MSI/Desktop/esprit2A31/projet c++/r3.PNG");
        int wr=ui->label_2->width(),hr=ui->label_2->height();
        ui->label_2->setPixmap(pixrobot.scaled(wr,hr,Qt::KeepAspectRatio));
        text=v[i];
    }
    else if(msg=="" ||msg=="?"||msg==" ")
    {
        vector<QString>v;
        v.push_back("Did you know?The First Computer Weighed More Than 27 Tons");
        v.push_back("Did you know?The First Known Computer Programmer was a Woman");
        v.push_back("Did you know? People Blink Less When They Use Computers");
        v.push_back("Did you know?Hackers Write About 6,000 New Viruses Each Month");

        int i = rand() % 4;

        QPixmap pixrobot("C:/Users/MSI/Desktop/esprit2A31/projet c++/r4.PNG");
        int wr=ui->label_2->width(),hr=ui->label_2->height();
        ui->label_2->setPixmap(pixrobot.scaled(wr,hr,Qt::KeepAspectRatio));
        text=v[i];
    }
    else if(msg=="bye" ||msg=="see you"||msg=="i have to go")
    {
        vector<QString>v;
        v.push_back("Goodbye good luck in your work");
        v.push_back("See you take care mate!");
        v.push_back("Bye! good luck in your shift :)");


        int i = rand() % 3;

        QPixmap pixrobot("C:/Users/MSI/Desktop/esprit2A31/projet c++/r1.PNG");
        int wr=ui->label_2->width(),hr=ui->label_2->height();
        ui->label_2->setPixmap(pixrobot.scaled(wr,hr,Qt::KeepAspectRatio));
        text=v[i];
    }
    else if(msg=="psst" ||msg=="."||msg=="pss")
    {
        vector<QString>v;

        v.push_back("Oh hey friend i'm glad you're here");
        v.push_back("Missed me already?");
        v.push_back("Welcome back!");
        v.push_back("Oh you're here i'd use some company");
        v.push_back("What are you doing here?You should focus on your work!");

        int i = rand() % 5 ;

        QPixmap pixrobot("C:/Users/MSI/Desktop/esprit2A31/projet c++/r2.PNG");
        int wr=ui->label_2->width(),hr=ui->label_2->height();
        ui->label_2->setPixmap(pixrobot.scaled(wr,hr,Qt::KeepAspectRatio));
        text=v[i];
    }
    else if(msg=="hhh" ||msg=="hhhh"||msg=="haha")
    {
        vector<QString>v;

        v.push_back("What's so funny?");
        v.push_back("Are you laughing at me ?");
        v.push_back("Having fun i see!");

        int i = rand() % 3 ;

        QPixmap pixrobot("C:/Users/MSI/Desktop/esprit2A31/projet c++/r2.PNG");
        int wr=ui->label_2->width(),hr=ui->label_2->height();
        ui->label_2->setPixmap(pixrobot.scaled(wr,hr,Qt::KeepAspectRatio));
        text=v[i];
    }
    else{
        QPixmap pixrobot("C:/Users/MSI/Desktop/esprit2A31/projet c++/r5.PNG");
        int wr=ui->label_2->width(),hr=ui->label_2->height();
        ui->label_2->setPixmap(pixrobot.scaled(wr,hr,Qt::KeepAspectRatio));
        text="Sorry i didnt understant , please try again";
    }

    ui->output->appendPlainText(space);
    ui->output->appendPlainText(text);
}




void MainWindow::on_tabWidget_rh_currentChanged(int index)
{
    QSqlQuery q1,q2,q3,q4,q5,q6;
                    qreal tot=0,c1=0,c2=0,c3=0,c4=0,c5=0;
                    int i=-1,j=-1,k=-1,m=-1,n=-1;


                    q2.prepare("SELECT * FROM EMPLOYES WHERE Role='RH'");
                    q2.exec();

                    q3.prepare("SELECT * FROM EMPLOYES WHERE Role='Finance'");
                    q3.exec();

                    q4.prepare("SELECT * FROM EMPLOYES WHERE Role='Equipement' ");
                    q4.exec();

                    q5.prepare("SELECT * FROM EMPLOYES WHERE Role='Espace' ");
                    q5.exec();
                    q6.prepare("SELECT * FROM EMPLOYES WHERE Role='Client' ");
                    q6.exec();

                    //while (q1.next()){tot++;}
                    while (q2.next()){c1++;}
                    while (q3.next()){c2++;}
                    while (q4.next()){c3++;}
                    while (q5.next()){c4++;}
                    while (q6.next()){c5++;}
                   QPieSeries *series=new QPieSeries();


                    series->append("RH",c1);
                    series->append("Finance",c2);
                    series->append("Equipement",c3);
                    series->append("Espace",c4);
                    series->append("Client",c5);

//slice color
//                    QPieSlice *slice = series->slices().at(3);
//                                     slice->setExploded(true);
                                     //slice->setPen(QPen(Qt::darkGreen, 2));
                                     //slice->setBrush(Qt::green);


                    QChart *chart =new QChart();

                    chart->addSeries(series);

                    chart->setTitle("Repartition des employes selon leur role ");
                    QChartView *chartView=new QChartView(chart);
                    //
                    tot = c1+c2+c3+c4+c5;
                                          QString t=QString::number(c1+c2+c3+c4+c5);
                                          QString p1=QString::number(c1/tot*100, 'f', 2)+"%";
                                          QString p2=QString::number(c2/tot*100, 'f', 2)+"%";
                                          QString p3=QString::number(c3/tot*100, 'f', 2)+"%";
                                          QString p4=QString::number(c4/tot*100, 'f', 2)+"%";
                                          QString p5=QString::number(c5/tot*100, 'f', 2)+"%";
                                          QString n1=QString::number(c1);
                                          QString n2=QString::number(c2);
                                          QString n3=QString::number(c3);
                                          QString n4=QString::number(c4);
                                          QString n5=QString::number(c5);
                                          ui->lineEdit_p1->setText(p1);
                                          ui->lineEdit_p2->setText(p2);
                                          ui->lineEdit_p3->setText(p3);
                                          ui->lineEdit_p4->setText(p4);
                                          ui->lineEdit_p5->setText(p5);
                                          ui->lineEdit_n1->setText(n1);
                                          ui->lineEdit_n2->setText(n2);
                                          ui->lineEdit_n3->setText(n3);
                                          ui->lineEdit_n4->setText(n4);
                                          ui->lineEdit_n5->setText(n5);
                                          ui->lineEdit_tot->setText(t);
                                          //QString strValue = QString::number(value, 'f', 3);
                                        if(c1>c2 && c1>c3 && c1>c4&& c1>c5){
                                                        QString type="RH";
                                                         QString max=QString::number(c1);
                                                         ui->lineEdit_4->setText(type);
                                                         ui->lineEdit_5->setText(max);
                                                         j=0;
                                                        }
                                                            else if (c2>c1 && c2>c3 && c2>c4&& c2>c5) {
                                                            QString type="Finance";
                                                             QString max=QString::number(c2);
                                                             ui->lineEdit_4->setText(type);
                                                             ui->lineEdit_5->setText(max);
                                                             j=1;
                                                        }else if (c3>c1 && c3>c2 && c3>c4&& c3>c5) {
                                                            QString type="Equipement";
                                                             QString max=QString::number(c3);
                                                             ui->lineEdit_4->setText(type);
                                                             ui->lineEdit_5->setText(max);
                                                             j=2;
                                                        }
                                                        else if (c4>c1 && c4>c2 && c4>c3&& c4>c5) {
                                                             QString type="Espace";
                                                             QString max=QString::number(c4);
                                                             ui->lineEdit_4->setText(type);
                                                             ui->lineEdit_5->setText(max);
                                                             j=3;
                                                        }else{
                                                            QString type="Client";
                                                             QString max=QString::number(c5);
                                                             ui->lineEdit_4->setText(type);
                                                             ui->lineEdit_5->setText(max);
                                                             j=4;


                                                        }
                                                        if(c1<c2 && c1<c3 && c1<c4&& c1<c5){
                                                        QString type="RH";
                                                         QString max=QString::number(c1);
                                                         ui->lineEdit_6->setText(type);
                                                         ui->lineEdit_7->setText(max);
                                                         i=0;

                                                        }
                                                            else if (c2<c1 && c2<c3 && c2<c4&& c2<c5) {
                                                            QString type="Finance";
                                                             QString max=QString::number(c2);
                                                             ui->lineEdit_6->setText(type);
                                                             ui->lineEdit_7->setText(max);
                                                             i=1;
                                                        }else if (c3<c1 && c3<c2 && c3<c4 && c3<c5) {
                                                            QString type="Equipement";
                                                             QString max=QString::number(c3);
                                                             ui->lineEdit_6->setText(type);
                                                             ui->lineEdit_7->setText(max);
                                                             i=2;
                                                        }else if (c4<c1 && c4<c2 && c4<c3 && c4<c5) {
                                                            QString type="Espace";
                                                             QString max=QString::number(c4);
                                                             ui->lineEdit_6->setText(type);
                                                             ui->lineEdit_7->setText(max);
                                                             i=3;
                                                        }else{
                                                            QString type="Client";
                                                             QString max=QString::number(c5);
                                                             ui->lineEdit_6->setText(type);
                                                             ui->lineEdit_7->setText(max);
                                                             i=4;
                                                        }




                    chartView = new QChartView(chart,ui->horizontalFrame);
                    chartView->setRenderHint(QPainter::Antialiasing);
                    chartView->setMinimumSize(600,380);
                    QPieSlice *slicei = series->slices().at(i);
                    QPieSlice *slicej = series->slices().at(j);
                    slicei->setPen(QPen(Qt::white, 2));
                    slicei->setBrush(Qt::darkMagenta);
                    slicej->setPen(QPen(Qt::white, 2));
                    slicej->setBrush(Qt::cyan);

                      slicei->setExploded(true);






}

void MainWindow::on_tabWidget_rh_tabBarClicked(int index)
{
   // ui->output->clear();
    vector<QString>v;
    v.push_back("What's on your mind?");
    v.push_back("It's good to see you again ^^");
    v.push_back("Need something?");
    v.push_back("Some useful commands: excel,pdf..");
    int i = rand() % 4 ;
    ui->output->setPlainText(v[i]);
    ui->tableView->setModel(Emp.afficher());
    ui->tableView_3->setModel(Emp.afficher());
    ui->tableView_rh->setModel(Emp.afficher2());
}






void MainWindow::on_notepad_clicked()
{
    n=new notepad();
    n->show();
}



void MainWindow::on_logout_clicked()
{
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Logout", "Are you sure you want to quit?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
        QSqlQuery query,qry;

           Agent a;
          QString id=a.getid();
          int action=0;
          QString res=QString::number(action);
          query.prepare("UPDATE agent "" SET action=:action  where username='"+id+"' ");
            query.bindValue(":action",res);
            query.exec();

            qApp->quit();

      } else {
        qDebug() << "Yes was *not* clicked";
      }

}
void MainWindow::show_from_arduino()
{
    data=A.read_from_arduino();
    QString code;
    if(data=="1")
        code="73 F4 62 A7";
    else if(data=="2")
        code="83 32 9D 92";

    QSqlQueryModel *model= new QSqlQueryModel();
    //QSqlQueryModel *model2= new QSqlQueryModel();

    QSqlQuery *query=new QSqlQuery;
    QSqlQuery *query2=new QSqlQuery;
    QString pr="present(e)";


    query->prepare("SELECT * FROM employes WHERE RFID  ='"+code+"'");
    query->exec();
    query2->prepare("UPDATE employes set PRESENCE='"+pr+"' WHERE RFID  ='"+code+"'");
    query2->exec();

    if(query->exec())
    {
    cout<<data.toStdString();
    model->setQuery(*query);
    //model2->setQuery(*query2);
    ui->tableView_arduino->setModel(model);
    //ui->tableView_arduino->setModel(model2);
    ui->tableView_arduino->show();
    //QDate cd = QDate::currentDate();
       QTime ct = QTime::currentTime();
        ui->le_date->setText(ct.toString());


    }

/*
    data=A.read_from_arduino();
    if(data=="1")
    {
    QPixmap pixard("C:/Users/maram/Downloads/res.png");
            int ward=ui->label_etat->width();
            int hard=ui->label_etat->height();
            ui->label_etat->setPixmap(pixard.scaled(ward,hard,Qt::KeepAspectRatio));
    }
    else if(data=="0")
    {
                QPixmap pixard("C:/Users/maram/Downloads/ocupee.png");
                        int ward=ui->label_etat_2->width();
                        int hard=ui->label_etat_2->height();
                        ui->label_etat_2->setPixmap(pixard.scaled(ward,hard,Qt::KeepAspectRatio));
    }
  */

}
void MainWindow::on_pushButton_lcd_clicked()
{
    A.write_to_arduino("3");
}

void MainWindow::on_pushButton_lcd_2_clicked()
{
    A.write_to_arduino("4");
}

void MainWindow::on_pushButton_lcd_3_clicked()
{
    A.write_to_arduino("5");
}

void MainWindow::on_pushButton_lcd_4_clicked()
{
    A.write_to_arduino("6");
}

void MainWindow::on_pushButton_lcd_5_clicked()
{
    A.write_to_arduino("7");
}



void MainWindow::on_pushButton_lcd_6_clicked()
{
    A.write_to_arduino("8");
}

void MainWindow::on_pushButton_3_clicked()
{
    QSqlQuery *query=new QSqlQuery;
    QString pr="absent(e)";

    query->prepare("UPDATE employes set PRESENCE='"+pr+"'");
    query->exec();
    ui->tableView->setModel(Emp.afficher());

}






int MainWindow::on_pb_rh_clicked()
{
        ui->tabWidget_rh->show();
        ui->tabWidget_eq->hide();
        ui->tabWidget_fa->hide();
        ui->tabWidget_cl->hide();
        ui->tabWidget_es->hide();
        //ui->pb_rh->setChecked(false);
        ui->pb_finance->setChecked(false);
        ui->pb_client->setChecked(false);
        ui->pb_espace->setChecked(false);
        ui->pb_equip->setChecked(false);
}

void MainWindow::on_pb_ajouter_2_clicked()
{
    int code=ui->le_code->text().toInt();
    int quantite=ui->sb_quantite->text().toInt();
    QString nom=ui->le_nom_2->currentText();
    QString type=ui->le_type->text();
    Equipement E(code,nom,type,quantite);
    bool test=E.ajouter();
    if(test)
    {
        ui->tableView_2->setModel(E.afficher());
        ui->tableView_4->setModel(E.afficher());
        QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Ajout effectué\n""Click Cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),QObject::tr("Ajouter non effectué\n""Click Cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pb_modifier_2_clicked()
{
    int code=ui->le_code_2->text().toInt();
    int quantite=ui->sb_quantite_2->text().toInt();
    QString nom=ui->le_nom_3->currentText();
    QString type=ui->le_type_2->text();


    Equipement E(code,nom,type,quantite);
    bool test=E.modifier(code);
    ui->tableView_4->setModel(E.afficher());
    ui->tableView_2->setModel(E.afficher());
 if(test){

    QMessageBox::information(nullptr,QObject::tr("OK"),
                             QObject::tr("modification effectué \n""Click Cancel to exit"),QMessageBox::Cancel);
}else{
     QMessageBox::information(nullptr,QObject::tr("Not oK"),
                              QObject::tr("modification non effectué \n""Click Cancel to exit"),QMessageBox::Cancel);
}
}

void MainWindow::on_pb_supprimer_2_clicked()
{
    int code=ui->le_codes->text().toInt();
    bool test=E.supprimer(code);
    QString code_string=QString::number(code);
    QSqlQuery queryc;
    QSqlQueryModel *modelc= new QSqlQueryModel();
    queryc.prepare("SELECT * FROM equipement WHERE (code  LIKE "+code_string+  ")");
    if(queryc.exec()){
       modelc->setQuery(queryc);
       }
    if(queryc.numRowsAffected()==0){QMessageBox::warning(nullptr, QObject::tr("Erreur de suppression"),
                                                               QObject::tr("Equipement introuvable .\n"
                                                                           "Click Cancel to exit."), QMessageBox::Cancel);}



   else{
    if(test)
    {
        if(test)
        {
            ui->tableView_2->setModel(E.afficher());
            ui->tableView_4->setModel(E.afficher());
            QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Suppression effectué\n""Click Cancel to exit."),QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not ok"),QObject::tr("Suppression non effectué\n""Click Cancel to exit."),QMessageBox::Cancel);
    }
}}

void MainWindow::on_pushButton_rechercher_clicked()
{
    int code ;
        QSqlQueryModel *model;
        code = ui->lineEdit_rechercher->text().toInt() ;
         model =EP->chercher (code);
         ui->tableView_2->show() ;
         ui->tableView_2->setModel(model);
}

void MainWindow::on_pushButton_trier_clicked()
{
    ui->tableView_2->setModel( E.sortid());
}

void MainWindow::on_pushButton_PDF_clicked()
{

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                         "/home",
                                                         QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);
             qDebug()<<dir;
             QPdfWriter pdf(dir+"/PdfList.pdf");
                                    QPainter painter(&pdf);
                                   int i = 4000;

                                   painter.drawPixmap(QRect(100,100,2000,2000),QPixmap("C:/Users/Admin/Desktop/msi.png"));
                                       //painter.drawText(900,650,"Tiny hues");

                                        //painter.drawPixmap(QRect(7600,100,2100,2700),QPixmap("C:/Users/Admin/Desktop/msi.png"));

                                        painter.setPen(Qt::red);
                                        painter.setFont(QFont("Time New Roman", 25));
                                        painter.drawText(3000,1450,"Liste Des Equipements");
                                        painter.setPen(Qt::black);
                                        painter.setFont(QFont("Time New Roman", 15));
                                        painter.drawRect(100,100,9400,2500);
                                        painter.drawRect(100,3000,9400,500);
                                        painter.setFont(QFont("Time New Roman", 10));
                                        painter.drawText(300,3300,"Code");
                                        painter.drawText(3000,3300,"Nom");
                                        painter.drawText(5600,3300,"Type");
                                        painter.drawText(8300,3300,"Qunatite");

                                        painter.drawRect(100,3000,9400,10700);


                                        QTextDocument previewDoc;
                                        QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");


                                        QTextCursor cursor(&previewDoc);



                                        QSqlQuery query;
                                        query.prepare("select * from EQUIPEMENT");
                                        query.exec();
                                        while (query.next())
                                        {
                                            painter.drawText(300,i,query.value(0).toString());
                                            painter.drawText(3000,i,query.value(1).toString());
                                            painter.drawText(5600,i,query.value(2).toString());
                                            painter.drawText(8300,i,query.value(3).toString());


                                           i = i +500;
                                        }
                                        int reponse = QMessageBox::question(this, "Générer PDF", " PDF Enregistré ! Voulez Vous Affichez Le PDF ?",
                                                                            QMessageBox::Yes|QMessageBox::No);
                                            if (reponse == QMessageBox::Yes)
                                            {
                                                QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));

                                                painter.end();
                                            }
                                            else
                                            {
                                                 painter.end();
   }
}
void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    days=days+date.toString()+"|";
    ui->les_jours->setText(days);

}



void MainWindow::on_sendBtn_3_clicked()
{
    QString link="https://mail.google.com/mail/u/1/#inbox?compose=new";
            QDesktopServices::openUrl(link);
}

void MainWindow::on_statsmed_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("select * from EQUIPEMENT where NOM='meuble' ");
     int number1=model->rowCount();
     model->setQuery("select * from EQUIPEMENT where NOM='materiel info' ");
     int number2=model->rowCount();
     model->setQuery("select * from EQUIPEMENT where NOM='cuisine' ");
     int number3=model->rowCount(); // calculer le nombre des evenement pour engament
    model->setQuery("select * from EQUIPEMENT where NOM='loisir' ");
          int number4=model->rowCount();
          model->setQuery("select * from EQUIPEMENT where NOM='composant reseau' ");
          int number5=model->rowCount();
     model->setQuery("select * from EQUIPEMENT where NOM='autre' ");
     int number6=model->rowCount();
     int total=number1+number2+number3+number4+number5+number6;
     QString a = QString("meuble"+QString::number((number1*100)/total,'f',2)+"%" );
     QString b = QString("materiel info"+QString::number((number2*100)/total,'f',2)+"%" );
     QString c = QString("cuisine"+QString::number((number3*100)/total,'f',2)+"%" );
     QString d = QString("loisir" +QString::number((number4*100)/total,'f',2)+"%" );

      QString e = QString("composant reseau" +QString::number((number5*100)/total,'f',2)+"%" );

     QString f = QString("autre "+QString::number((number6*100)/total,'f',2)+"%" );

QPieSeries *series = new QPieSeries();
     series->append(a,number1);
     series->append(b,number2);
     series->append(c,number3);
     series->append(d,number4);
     series->append(e,number5);
     series->append(f,number6);
     if (number1!= 0)
     {
         QPieSlice *slice = series->slices().at(0);
         slice->setLabelVisible();
         slice->setPen(QPen());
     }
     if (number2!=0)
     {
              // Add label, explode and define brush for 2nd slice
              QPieSlice *slice1 = series->slices().at(1);
              //slice1->setExploded();
              slice1->setLabelVisible();
     }
     if(number3!=0)
     {
              // Add labels to rest of slices
              QPieSlice *slice2 = series->slices().at(2);
              //slice1->setExploded();
              slice2->setLabelVisible();
     }
     if(number4!=0)
     {
              // Add labels to rest of slices
              QPieSlice *slice3 = series->slices().at(3);
              //slice1->setExploded();
              slice3->setLabelVisible();
     }
     if(number5!=0)
     {
              // Add labels to rest of slices
              QPieSlice *slice4 = series->slices().at(4);
              //slice1->setExploded();
              slice4->setLabelVisible();
     }
     if(number6!=0)
     {
              // Add labels to rest of slices
              QPieSlice *slice5 = series->slices().at(5);
              //slice1->setExploded();
              slice5->setLabelVisible();
     }
             // Create the chart widget
             QChart *chart = new QChart();
             // Add data to chart with title and hide legend
             chart->addSeries(series);
             chart->setTitle("Pourcentage par type des nom"+ QString::number(total));
             chart->legend()->hide();
             // Used to display the chart
             QChartView *chartView = new QChartView(chart);
             chartView->setRenderHint(QPainter::Antialiasing);
             chartView->resize(1000,500);
             chartView->show();

}

void MainWindow::on_qrcodegen_2_clicked()
{
    int tabeq=ui->tableView_2->currentIndex().row();
           QVariant idd=ui->tableView_2->model()->data(ui->tableView_2->model()->index(tabeq,0));
           QString id= idd.toString();
           QSqlQuery qry;
           qry.prepare("select * from EQUIPEMENT where CODE=:code");
           qry.bindValue(":CODE",id);
           qry.exec();
              QString  type,nom,ide;

           while(qry.next()){

               id=qry.value(1).toString();
               nom=qry.value(3).toString();
               type=qry.value(2).toString();



           }
           ide=QString(id);
                  ide="NOM:"+nom+"TYPE:"+type;
           QrCode qr = QrCode::encodeText(ide.toUtf8().constData(), QrCode::Ecc::HIGH);

           // Read the black & white pixels
           QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
           for (int y = 0; y < qr.getSize(); y++) {
               for (int x = 0; x < qr.getSize(); x++) {
                   int color = qr.getModule(x, y);  // 0 for white, 1 for black

                   // You need to modify this part
                   if(color==0)
                       im.setPixel(x, y,qRgb(254, 254, 254));
                   else
                       im.setPixel(x, y,qRgb(0, 0, 0));
               }
           }
           im=im.scaled(200,200);
           ui->qrcodecommande_2->setPixmap(QPixmap::fromImage(im));
}

void MainWindow::on_pushButton_trier_2_clicked()
{
    ui->tableView_2->setModel( E.sortquantite());
}
//ismail
void MainWindow::on_pb_ajouter_3_clicked()
{
    int numsalle=ui->le_numsalle->text().toInt();
    int capacite=ui->le_capacite->text().toInt();
    QString bloc=ui->le_bloc->text();
    QString type=ui->le_type_3->text();
    QString etat=ui->le_etat->text();

    Espace Esp(numsalle,capacite,bloc,type,etat);

    bool test=Esp.ajouter();
    QMessageBox msgBox;

    if(test)
    {  msgBox.setText("Ajout avec succes.");

    ui->tab_espace->setModel(Es.afficher());
    ui->tab_espace_2->setModel(Es.afficher());

    }
    else
        msgBox.setText("Echec d'ajout");
        msgBox.exec();
}

void MainWindow::on_pb_supprimer_3_clicked()
{
    Espace E1;
    E1.setnumsalle(ui->le_numsalle_supp->text().toInt());
    bool test=E1.supprimer(E1.getnumsalle());
    QMessageBox msgBox;

    if(test)
    { msgBox.setText("Suppression avec succes.");

       ui->tab_espace->setModel(Es.afficher());
       ui->tab_espace_2->setModel(Es.afficher());

    }
    else
        msgBox.setText("Echec de suppression");
        msgBox.exec();
}

void MainWindow::on_pb_modifier_3_clicked()
{
    int numsalle=ui->le_numsalle_m->text().toInt();
    int capacite=ui->le_capacite_m->text().toInt();
    QString bloc=ui->le_bloc_m->text();
    QString type=ui->le_type_m->text();
    QString etat=ui->le_etat_m->text();

    Espace Esp(numsalle,capacite,bloc,type,etat);


    bool test=Esp.modifier(numsalle);

    ui->tab_espace->setModel(Es.afficher());
    ui->tab_espace_2->setModel(Es.afficher());
    if(test)
    {  QMessageBox::information(nullptr,QObject::tr("OK"),
                                QObject::tr("Modification avec succee\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);



    }
    else
        QMessageBox::critical(nullptr,QObject::tr(" not OK"),
                                        QObject::tr("Modification echec\n"
                                                    "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_Ajouterfacture_2_clicked()
{
    int num=ui->lineEdit_numfacture_2->text().toInt(); //convertir en entier
    QDate date=ui->lineeditdateTimeEdit_2->date();
    QString nom =ui->lineEdit_name_2->text();
    QString prenom=ui->lineEdit_surname_2->text();
    int prix=ui->lineEdit_prix_2->text().toInt();

   Facture F(num,nom, prenom,prix,date);
        bool test=F.ajouterfacture();
        if(test)
              {    QMessageBox::information(nullptr, QObject::tr("ajout avec succes"),
                                            QObject::tr("ajout successful.\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);
                    ui->tableView_facture->setModel(F.afficherfacture());//mise a jour ecran
              }
                            else
                                QMessageBox::critical(nullptr, QObject::tr("Ajout errer"),
                                            QObject::tr("ajout failed.\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);

             ui->lineEdit_numfacture_2->clear();
             ui->lineEdit_name_2->clear();
             ui->lineEdit_surname_2->clear();
             ui->lineEdit_prix_2->clear();
}

void MainWindow::on_pushButton_modifierfact_2_clicked()
{
    int num=ui->lineEdit_numfacture_2->text().toInt();
    QDate date=ui->lineeditdateTimeEdit_2->date();
    QString name=ui->lineEdit_name_2->text();
    QString prenom=ui->lineEdit_surname_2->text();
    int prix=ui->lineEdit_prix_2->text().toInt();
    Facture F(num,name,prenom,prix,date);

    bool test=F.modifierfacture(F.getnum(),F.getnom(),F.getprenom(),F.getprix(),F.getdate());

    QMessageBox msgBox;

    if(test)
    {
        QMessageBox::information(this, QObject::tr("Modification Succes"),
                           QObject::tr("Modifications mrigla"), QMessageBox::Cancel);
        ui->tableView_facture->setModel(F.afficherfacture());

    }
    else
    {

        QMessageBox::critical(this, QObject::tr("Modification Erreur"),
                           QObject::tr("Erreur de Modifications"), QMessageBox::Cancel);

    }
    ui->lineEdit_numfacture_2->clear();
    ui->lineEdit_name_2->clear();
    ui->lineEdit_surname_2->clear();
    ui->lineEdit_prix_2->clear();
}

void MainWindow::on_pushButton_supprimer_2_clicked()
{
    Facture F1;
    F1.setnum(ui->lineEdit_numvolsupprimer_2->text().toInt());
    bool test=F1.supprimerfacture(F1.getnum());
    QMessageBox msgBox;
    if (ui->lineEdit_numvolsupprimer_2->text()=="")
    {
        QMessageBox::critical(this, QObject::tr("Suppression Errer"),
                           QObject::tr("Echec de Suppression!!!\n""Veuillez remplir la label de CIN"), QMessageBox::Cancel);
    }
    else if (test)
    {
        QMessageBox::information(this, QObject::tr("Suppression avec Succes"),
                           QObject::tr("Suppression avec succes"), QMessageBox::Cancel);
        ui->tableView_facture->setModel(F.afficherfacture());
    }
    ui->lineEdit_numvolsupprimer_2->clear();
}

void MainWindow::on_tableView_facture_clicked(const QModelIndex &index)
{
    ui->lineEdit_numfacture_2->setText(ui->tableView_facture->model()->data(ui->tableView_facture->model()->index(index.row(),0)).toString());
    ui->lineEdit_name_2->setText(ui->tableView_facture->model()->data(ui->tableView_facture->model()->index(index.row(),1)).toString());
    ui->lineEdit_surname_2->setText(ui->tableView_facture->model()->data(ui->tableView_facture->model()->index(index.row(),2)).toString());
    ui->lineEdit_prix_2->setText(ui->tableView_facture->model()->data(ui->tableView_facture->model()->index(index.row(),3)).toString());
}

void MainWindow::on_pushButton_recherche_clicked()
{
    QString rech=ui->lineEdit_recherche_2->text();
    ui->tableView_facture->setModel(F.Recherchefacture(rech));
}

void MainWindow::on_pushButton_Reset_2_clicked()
{
    Facture F1;
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Reset", "Voulez vous supprimer toutes les factures?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
            bool test=F1.supprimerTout();
            QMessageBox msgBox;
            if(test)
                      {    QMessageBox::information(nullptr, QObject::tr("Reset avec succes"),
                                                    QObject::tr("Reset jwwha beehy.\n"
                                                                "Click Cancel to exit."), QMessageBox::Cancel);
                                     ui->tableView_facture->setModel(F.afficherfacture());
                      }
                                    else
                                        QMessageBox::critical(nullptr, QObject::tr("Reset errer"),
                                                    QObject::tr("Reset failed.\n"
                                                                "Click Cancel to exit."), QMessageBox::Cancel);
      } else {
        qDebug() << "Yes was *not* clicked";
      }
//    bool test=F1.supprimerTout();
//    QMessageBox msgBox;
//         if(test)
//          {    QMessageBox::information(nullptr, QObject::tr("Reset avec succes"),
//                                        QObject::tr("Reset jwwha beehy.\n"
//                                                    "Click Cancel to exit."), QMessageBox::Cancel);
//                         ui->tableView_facture->setModel(F.afficherfacture());
//          }
//                        else
//                            QMessageBox::critical(nullptr, QObject::tr("Reset errer"),
//                                        QObject::tr("Reset failed.\n"
//                                                    "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_tri_2_clicked()
{
    if(ui->TRI_2->currentText()=="Tri par NUM")
    {
        ui->tableView_facture->setModel(F.trierfactureparnumfacture());

    }
    else if(ui->TRI_2->currentText()=="Tri par PRIX")
    {
        ui->tableView_facture->setModel(F.trierfactureParprix());

    }
    else
    {
        ui->tableView_facture->setModel(F.trierfacturepardate());
    }
}

void MainWindow::on_pushButton_statestique_2_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                     model->setQuery("select * from FACTURE where PRIX < 5000 ");
                     float prix=model->rowCount();
                     model->setQuery("select * from FACTURE where PRIX  between 5000 and 8000 ");
                     float prixx=model->rowCount();
                     model->setQuery("select * from FACTURE where PRIX > 8000 ");
                     float prixxx=model->rowCount();
                     float total=prix+prixx+prixxx;
                     QString a=QString("moins de 5000 DINARS "+QString::number((prix*100)/total,'f',2)+"%" );
                     QString b=QString("entre 5000 et 8000 DINARS"+QString::number((prixx*100)/total,'f',2)+"%" );
                     QString c=QString("+8000 DINARS"+QString::number((prixxx*100)/total,'f',2)+"%" );
                     QPieSeries *series = new QPieSeries();
                     series->append(a,prix);
                     series->append(b,prixx);
                     series->append(c,prixxx);
             if (prix!=0)
             {QPieSlice *slice = series->slices().at(0);
              slice->setLabelVisible();
              slice->setPen(QPen());}
             if ( prixx!=0)
             {
                      // Add label, explode and define brush for 2nd slice
                      QPieSlice *slice1 = series->slices().at(1);
                      //slice1->setExploded();
                      slice1->setLabelVisible();
             }
             if(prixxx!=0)
             {
                      // Add labels to rest of slices
                      QPieSlice *slice2 = series->slices().at(2);
                      //slice1->setExploded();
                      slice2->setLabelVisible();
             }
                     // Create the chart widget
                     QChart *chart = new QChart();
                     // Add data to chart with title and hide legend
                     chart->addSeries(series);
                     chart->setTitle("Pourcentage Par prix dans la facture :prix des factures "+ QString::number(total));
                     chart->legend()->hide();
                     // Used to display the chart
                     QChartView *chartView = new QChartView(chart);
                     chartView->setRenderHint(QPainter::Antialiasing);
                     chartView->resize(1000,500);
                     chartView->show();
}

void MainWindow::on_pushButton_pdf_clicked()
{
//    QPdfWriter pdf("C:/Users/MSI/Desktop/Atelier_Connexion/PDFF.pdf");

//      QPainter painter(&pdf);
//      int i = 4000;
//             painter.setPen(Qt::red);
//             painter.setFont(QFont("Time New Roman", 25));
//             painter.drawText(3000,1400,"Liste Des vols");
//             painter.setPen(Qt::black);
//             painter.setFont(QFont("Time New Roman", 15));
//             painter.drawRect(100,3000,9400,500);
//             painter.setFont(QFont("Time New Roman", 9));
//             painter.drawText(400,3300,"NUM");
//             painter.drawText(2350,3300,"DATEE");
//             painter.drawText(4200,3300,"NOM");
//             painter.drawText(5400,3300,"PRENOM");
//             painter.drawRect(100,3000,9400,9000);

//             QSqlQuery query;
//             query.prepare("select * from FACTURE");
//             query.exec();
//             while (query.next())
//             {
//                 painter.drawText(400,i,query.value(0).toString());
//                 painter.drawText(2100,i,query.value(1).toString());
//                 painter.drawText(4300,i,query.value(2).toString());
//                 painter.drawText(5400,i,query.value(3).toString());


//                i = i + 350;
//             }
//             QMessageBox::information(this, QObject::tr("PDF EnregistrÃ©!"),
//             QObject::tr("PDF EnregistrÃ©!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    F.telechargerPDF();

             QMessageBox::information(nullptr,QObject::tr("OK"),
                        QObject::tr("Téléchargement terminé"), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_afficherfacture_2_clicked()
{
    ui->tableView_facture->setModel(F.afficherfacture());
}

void MainWindow::on_pushButton_excel_2_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),tr("Excel Files (*.xls)"));
                   if (fileName.isEmpty())
                       return;

                   ExportExcelObject obj(fileName, "mydata", ui->tableView_facture);

                   //colums to export
                   obj.addField(1, "nom", "char(20)");
                   obj.addField(0, "num", "char(20)");
                   obj.addField(2,"prenom", "char(20)");
                   obj.addField(3, "prix", "char(20)");
                   obj.addField(4, "Durée", "char(20)");


                   int retVal = obj.export2Excel();
                   if( retVal > 0)
                   {
                       QMessageBox::information(this, tr("Done"),
                                                QString(tr("%1 records exported!")).arg(retVal)
                                                );
                   }

}

void MainWindow::on_tableView_4_clicked(const QModelIndex &index)
{
    int i;
    i=index.row();
    QModelIndex in=index.sibling(i,0);
    QString val=ui->tableView_4->model()->data(in).toString();


    //QString val=ui->tableView->model()->data(index).toString();

        QSqlQuery qry;
        qry.prepare("select * from equipement where code='"+val+"' or nom='"+val+"' or type='"+val+"' or quantite='"+val+"'  " );

        if(qry.exec())
        {
            while(qry.next())
            {

                ui->le_code_2->setText(qry.value(0).toString());
                ui->le_nom_3->setCurrentText(qry.value(2).toString());
                ui->le_type_2->setText(qry.value(1).toString());
                ui->sb_quantite_2->setSpecialValueText(qry.value(3).toString());


            }
    }
}



void MainWindow::on_tab_espace_2_clicked(const QModelIndex &index)
{
    int i;
    i=index.row();
    QModelIndex in=index.sibling(i,0);
    QString val=ui->tab_espace_2->model()->data(in).toString();


    //QString val=ui->tableView->model()->data(index).toString();

        QSqlQuery qry;
        qry.prepare("select * from espace where numsalle='"+val+"' or capacite='"+val+"' or bloc='"+val+"' or type='"+val+"' or etat='"+val+"'  " );

        if(qry.exec())
        {
            while(qry.next())
            {

                ui->le_numsalle_m->setText(qry.value(0).toString());
                ui->le_capacite_m->setText(qry.value(1).toString());
                ui->le_bloc_m->setText(qry.value(2).toString());
                ui->le_type_m->setText(qry.value(3).toString());
                ui->le_etat_m->setText(qry.value(4).toString());


            }
    }
}

void MainWindow::on_le_numsalle_supp_textChanged(const QString &arg1)
{
    QSqlQueryModel * modal= new QSqlQueryModel ();
        QSqlQuery*qry=new QSqlQuery();
        QString nums=ui->le_numsalle_supp->text();


        if(nums.isEmpty())
        {
            ui->tableView->setModel(Emp.afficher());

        }
        else
        {
            //
            qry->prepare ("SELECT * from espace where ( numsalle LIKE'%"+nums+"%' OR capacite LIKE'%"+nums+"%' OR etat LIKE'%"+nums+"%' OR bloc LIKE'%"+nums+"%'OR type LIKE'%"+nums+"%') ");
            qry->exec();
            modal->setQuery(*qry);
            ui->tab_espace_2->setModel(modal);
            //qry->prepare("select * from employes where CIN='"+CIN+"'"); //like
            //qry->exec();
            //modal->setQuery(*qry);
            //ui->tableView_3->setModel(modal);
        }
}

void MainWindow::on_lineEdit_rechercher_2_textChanged(const QString &arg1)
{
    QSqlQueryModel * modal= new QSqlQueryModel ();
        QSqlQuery*qry=new QSqlQuery();
        QString nums=ui->lineEdit_rechercher_2->text();


        if(nums.isEmpty())
        {
            ui->tableView->setModel(Emp.afficher());

        }
        else
        {
            //
            qry->prepare ("SELECT * from espace where ( numsalle LIKE'%"+nums+"%' OR capacite LIKE'%"+nums+"%' OR etat LIKE'%"+nums+"%' OR bloc LIKE'%"+nums+"%'OR type LIKE'%"+nums+"%') ");
            qry->exec();
            modal->setQuery(*qry);
            ui->tab_espace->setModel(modal);
            //qry->prepare("select * from employes where CIN='"+CIN+"'"); //like
            //qry->exec();
            //modal->setQuery(*qry);
            //ui->tableView_3->setModel(modal);
        }
}

void MainWindow::on_ajouterClient_4_clicked()
{
    QString nom=ui->ajouter_nom_4->text();
    QString prenom=ui->ajouter_prenom_4->text();
    int res=ui->ajouter_cin_4->text().toInt();
    int num_tel=ui->ajouter_num_4->text().toInt();
    QString adresse_mail=ui->ajouter_adresseMail_4->text();
    int card=0;
    Client c(res,num_tel,nom, prenom, adresse_mail,card);
    bool test=c.ajouter();
    if(test)
    {
        ui->affichageClient->setModel(Etmp.afficher());  //Actualiser
        QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Ajout effectué! \n" "Click cancel to exit"),QMessageBox::Cancel);
        histor.save("cin :"+ui->ajouter_cin_4->text(),"num_tel :"+ui->ajouter_num_4->text(),"nom :"+ui->ajouter_nom_4->text(),"prenom :"+ui->ajouter_prenom_4->text(),"adresse mail :"+ui->ajouter_adresseMail_4->text());
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Not OK"),QObject::tr("Ajout non effectué! \n" "Click cancel to exit"),QMessageBox::Cancel);
    }
}

void MainWindow::on_supprimerClient_4_clicked()
{
    int cin =ui->cinClient_8->text().toInt();
    bool test=Etmp.supprimer(cin);

    if(test)
    {
        ui->affichageClient->setModel(Etmp.afficher());  //Actualiser

        QMessageBox::information(nullptr,QObject::tr("OK"), QObject::tr("Suppression effectuée \n" "Click cancel to exit"), QMessageBox::Cancel);
        histor1.save1("SUPPRIMER","cin :"+ui->cinClient_8->text());

    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Suppression non effectuée \n" "Click cancel to exit"), QMessageBox::Cancel);
    }
}

void MainWindow::on_modifierClient_4_clicked()
{
    QString nom=ui->modifier_nom_4->text();
    QString prenom=ui->modifier_prenom_4->text();
    int res=ui->cinClient_8->text().toInt();
    int num_tel=ui->num_8->text().toInt();
    QString adresse_mail=ui->modifier_adresseMail_4->text();
    int card=ui->num_8->text().toInt();
    Client c(res,num_tel,nom, prenom, adresse_mail,card);
    bool test=c.modifier();
    if(test)
    {
        ui->affichageClient->setModel(Etmp.afficher());  //Actualiser
        QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Modification effectuée! \n" "Click cancel to exit"),QMessageBox::Cancel);
        histor.save2("SUPPRIMER","cin :"+ui->cinClient_8->text(),"num_tel :"+ui->num_8->text(),"nom :"+ui->modifier_nom_4->text(),"prenom :"+ui->modifier_prenom_4->text(),"adresse mail :"+ui->modifier_adresseMail_4->text());
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Not OK"),QObject::tr("Modification non effectuée! \n" "Click cancel to exit"),QMessageBox::Cancel);
    }
}

void MainWindow::on_rechercherClient_4_clicked()
{
    QString nom=ui->recherche_4->text();
    if(nom=="")
    {
        QMessageBox::information(nullptr,QObject::tr("Champ vide"),QObject::tr("Veuiller insérer un NOM!"),QMessageBox::Cancel);
        ui->affichageClient->setModel(Etmp.afficher());
    }
    else
    {
        ui->affichageClient->setModel(Etmp.rechercherNom(nom));
    }
}

void MainWindow::on_afficherHisto_clicked()
{
    QFile file("C:/Users/MSI/Desktop/interfacechedly/historique.txt");
        if (!file.open(QIODevice::ReadOnly))
            QMessageBox::information(0,"info",file.errorString());
        QTextStream in(&file);
        ui->textBrowser->setText(in.readAll());
}

void MainWindow::on_tri_clicked()
{
    ui->affichageClient->setModel(Etmp.triNom());
}

void MainWindow::on_pdf_6_clicked()
{
    QPrinter printer;
    printer.setPrinterName("Printer Name");

    QPrintDialog pDialog(&printer, this);

    if(pDialog.exec() == QDialog::Rejected){
        QMessageBox::warning(this, "Warning", "Cannot Access Printer");
        return;
    }
    ui->affichageClient->render(&printer);
}

void MainWindow::on_plus_clicked()
{
    QString nom=ui->recherche_5->text();
    QString prenom=prenom;
    int res=res;
    int num_tel=num_tel;
    int card=card;
    QString adresse_mail=adresse_mail;
    Client c(res,num_tel,nom, prenom, adresse_mail,card);
    bool test=c.update();
    if(test)
    {
        ui->affichageClient_3->setModel(Etmp.plus(nom));
        QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("presence ajoutée! \n" "Click cancel to exit"),QMessageBox::Cancel);
        histor.save2("SUPPRIMER","cin :"+ui->cinClient_8->text(),"num_tel :"+ui->num_8->text(),"nom :"+ui->modifier_nom_4->text(),"prenom :"+ui->modifier_prenom_4->text(),"adresse mail :"+ui->modifier_adresseMail_4->text());
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Not OK"),QObject::tr("Modification non effectuée! \n" "Click cancel to exit"),QMessageBox::Cancel);
    }
}

void MainWindow::on_tricard_clicked()
{
    ui->affichageClient_2->setModel(Etmp.plus2());
}

void MainWindow::on_pb_supprimer_4_clicked()
{
    int code=ui->le_codes->text().toInt();

    QString code_string=QString::number(code);
    QSqlQuery queryc;
    QSqlQueryModel *modelc= new QSqlQueryModel();
    queryc.prepare("SELECT * FROM equipement WHERE (code  LIKE "+code_string+  ")");
    if(queryc.exec()){
       modelc->setQuery(queryc);
       }
    if(queryc.numRowsAffected()==0){QMessageBox::warning(nullptr, QObject::tr("Erreur de suppression"),
                                                               QObject::tr("Equipement introuvable .\n"
                                                                           "Click Cancel to exit."), QMessageBox::Cancel);}



   else{
    bool test=E.supprimer(code);
        if(test)
        {
            ui->tableView_2->setModel(E.afficher());
            ui->tableView_4->setModel(E.afficher());
            QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Suppression effectué\n""Click Cancel to exit."),QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not ok"),QObject::tr("Suppression non effectué\n""Click Cancel to exit."),QMessageBox::Cancel);
    }
}



