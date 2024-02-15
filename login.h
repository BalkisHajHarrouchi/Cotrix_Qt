#ifndef LOGIN_H
#define LOGIN_H
#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    login(QString,QString);
    bool auth();

    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_pushButton_clicked();

    void on_pb_eye_clicked();

private:
    Ui::login *ui;
    MainWindow *mainwindow;
    QString username,password;
protected :
};

#endif // LOGIN_H
