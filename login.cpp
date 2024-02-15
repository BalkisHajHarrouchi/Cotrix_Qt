#include "login.h"
#include "ui_login.h"
#include<QPixmap>
#include "mainwindow.h"
#include "QSqlQuery"
#include "historique.h"
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    QPixmap pixlogo("C:/Users/MSI/Desktop/esprit2A31/projet c++/logoapp.PNG");
    int w=ui->label_logo->width(),h=ui->label_logo->height();
    ui->label_logo->setPixmap(pixlogo.scaled(w,h,Qt::KeepAspectRatio));

    QPixmap pixbg("C:/Users/MSI/Desktop/esprit2A31/projet c++/login_bg2.PNG");
    int w3=ui->label_logo_3->width(),h3=ui->label_logo_3->height();
    ui->label_logo_3->setPixmap(pixbg.scaled(w3,h3,Qt::KeepAspectRatio));

    QPixmap pixlogop("C:/Users/MSI/Desktop/esprit2A31/projet c++/powered.PNG");
    int w2=ui->label->width(),h2=ui->label->height();
    ui->label->setPixmap(pixlogop.scaled(w2,h2,Qt::KeepAspectRatio));

    QPixmap pixnoeye("C:/Users/MSI/Desktop/esprit2A31/projet c++/hide.PNG");
    int we=ui->label_eye->width(),he=ui->label_eye->height();
    ui->label_eye->setPixmap(pixnoeye.scaled(we,he,Qt::KeepAspectRatio));
}


login::~login()
{
    delete ui;
}
login::login(QString user,QString pass){
    username=user;
    password=pass;


}
void login::on_pushButton_clicked()
{
    QString user = ui->username->text();
    QString pass = ui->password->text();
    if(pass==NULL || user==NULL)
        QMessageBox::critical(nullptr,QObject::tr("Connection failed"),QObject::tr("Unvalid mail or password"),QMessageBox::Cancel);
    else
    {
        login L(user,pass);
    if (L.auth()){
        hide();
        mainwindow = new MainWindow(this);
        mainwindow->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

      mainwindow ->show();
        }
}
}



bool login::auth(){
    bool test = false;
    QSqlQuery query1,qry;
    printf("possible");
query1.prepare("select * from agent where username=:username");
query1.bindValue(":username",username);
if(query1.exec()){
    query1.next();
    if(query1.value(1).toString() == password){
         test = 2;
         int action=1;
         QString res=QString::number(action);
         query1.prepare("UPDATE agent "" SET action=:action  where username='"+username+"' ");
           query1.bindValue(":action",res);
           query1.exec();


    }else {
         test = 0;

    }
}else {
    test = 0;
}
return test;

}

void login::on_pb_eye_clicked()
{
    if(ui->password->echoMode()==2){
          ui->password->setEchoMode(QLineEdit::Normal);
          QPixmap pixeye("C:/Users/MSI/Desktop/esprit2A31/projet c++/show.PNG");
          int w=ui->label_eye->width(),h=ui->label_eye->height();
          ui->label_eye->setPixmap(pixeye.scaled(w,h,Qt::KeepAspectRatio));
       }
       else{
           ui->password->setEchoMode(QLineEdit::Password);
           QPixmap pixnoeye("C:/Users/MSI/Desktop/esprit2A31/projet c++/hide.PNG");
           int w=ui->label_eye->width(),h=ui->label_eye->height();
           ui->label_eye->setPixmap(pixnoeye.scaled(w,h,Qt::KeepAspectRatio));
       }
}
