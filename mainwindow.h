#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"employes.h"
#include <QMainWindow>
#include<ui_mainwindow.h>
#include "camera.h"
#include"stat_combo.h"
#include"notepad.h"
#include"historique.h"
#include"arduino.h"
#include"equipement.h"
#include"espace.h"
#include"facture.h"
#include"histo.h"
#include"client.h"
#include<QString>
#include<QtWidgets>
#include<QTableView>
#include <QDialog>
#include<QAbstractItemModel>
#include<QString>
#include<QMessageBox>
#include<QTableView>
#include<QSqlQueryModel>
#include <QDialog>
#include <QAbstractItemModel>
#include <QMainWindow>
#include <QFileDialog>
#include <QMainWindow>
#include <QVariant>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //void on_pushButton_clicked();

    //void on_pushButton_2_clicked();

    void on_pb_ajouter_clicked();

    //void on_pushButton_3_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    int on_pb_rh_clicked();

    void on_pb_finance_clicked();

    void on_pb_client_clicked();

    void on_pb_espace_clicked();

    void on_pb_equip_clicked();

    void on_pb_afficher_clicked();
    //void login_modifier_afficher_tab();

    void on_tableView_clicked(const QModelIndex &index);





    void on_le_CINa_textChanged(const QString &arg1);

    void on_le_CINs_textChanged(const QString &arg1);

    void on_comboBox_19_currentTextChanged(const QString &arg1);

    void on_comboBox_5_currentTextChanged(const QString &arg1);



    void on_pb_imprimer_clicked();



    void  browse();

    void sendMail();

    void mailSent(QString status);

    void on_pb_camera_clicked();




    void on_tableView_rh_clicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_pb_excel_clicked();



    void on_comboBox_rh_currentTextChanged(const QString &arg1);

    void on_le_CINa_2_textChanged(const QString &arg1);

    void on_pushButton_19_clicked();

    void on_pushButton_clicked();



    void on_tabWidget_rh_currentChanged(int index);

    void on_tabWidget_rh_tabBarClicked(int index);






    void on_notepad_clicked();




    void on_logout_clicked();

    void show_from_arduino();

    void on_pushButton_lcd_clicked();

    void on_pushButton_lcd_2_clicked();

    void on_pushButton_lcd_3_clicked();

    void on_pushButton_lcd_4_clicked();

    void on_pushButton_lcd_5_clicked();



    void on_pushButton_lcd_6_clicked();

    void on_pushButton_3_clicked();

    void on_pb_ajouter_2_clicked();

    void on_pb_modifier_2_clicked();

    void on_pb_supprimer_2_clicked();

    void on_pushButton_rechercher_clicked();

    void on_pushButton_trier_clicked();

    void on_pushButton_PDF_clicked();

    void on_calendarWidget_clicked(const QDate &date);



    void on_sendBtn_3_clicked();

    void on_statsmed_clicked();

    void on_qrcodegen_2_clicked();

    void on_pushButton_trier_2_clicked();

    void on_pb_ajouter_3_clicked();

    void on_pb_supprimer_3_clicked();

    void on_pb_modifier_3_clicked();

    void on_pushButton_Ajouterfacture_2_clicked();

    void on_pushButton_modifierfact_2_clicked();

    void on_pushButton_supprimer_2_clicked();

    void on_tableView_facture_clicked(const QModelIndex &index);

    void on_pushButton_recherche_clicked();

    void on_pushButton_Reset_2_clicked();

    void on_pushButton_tri_2_clicked();

    void on_pushButton_statestique_2_clicked();

    void on_pushButton_pdf_clicked();

    void on_pushButton_afficherfacture_2_clicked();

    void on_pushButton_excel_2_clicked();



    void on_tableView_4_clicked(const QModelIndex &index);



    void on_tab_espace_2_clicked(const QModelIndex &index);

    void on_le_numsalle_supp_textChanged(const QString &arg1);

    void on_lineEdit_rechercher_2_textChanged(const QString &arg1);

    void on_ajouterClient_4_clicked();

    void on_supprimerClient_4_clicked();

    void on_modifierClient_4_clicked();

    void on_rechercherClient_4_clicked();

    void on_afficherHisto_clicked();

    void on_tri_clicked();

    void on_pdf_6_clicked();

    void on_plus_clicked();

    void on_tricard_clicked();

    void on_pb_supprimer_4_clicked();



private:
    Ui::MainWindow *ui;
    Employes Emp;
    QStringList files;
    camera *c;
    notepad *n;
    historique hismp;
    QByteArray data;
    Arduino A;
    Equipement E;
    Equipement *EP;
    Espace Es;
    Facture F ;
    Client Etmp;

    histo histor;
    histo histor1;
    histo histor2;
signals:
    void setCenter(QVariant, QVariant);
    void addMarker(QVariant, QVariant);

};

#endif // MAINWINDOW_H
