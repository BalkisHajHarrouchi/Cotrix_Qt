#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include "ui_mainwindow.h"
#include "login.h"
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    //MainWindow w;
    Connection c;
    login l;
    //Ui_MainWindow:: ui->le_CIN->setValidator(new QIntValidator(0,999999 ,ui));
    bool test=c.createconnect();
    if(test)
    {//w.show();
         l.show();
//        QMessageBox::information(nullptr, QObject::tr("database is open"),
//                    QObject::tr("connection successful.\n"
//                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    //else
//        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
//                    QObject::tr("connection failed.\n"
//                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
//bonjour je suis dans la branche employe
