#include "notepad.h"
#include "ui_notepad.h"

notepad::notepad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::notepad)
{
    ui->setupUi(this);
}

notepad::~notepad()
{
    delete ui;
}

void notepad::on_actionNew_triggered()
{
    currentFile.clear();
        ui->textEdit->setText(QString());
}

void notepad::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    currentFile=fileName;
    if(!file.open(QIODevice::ReadOnly|QFile::Text)){
       QMessageBox::warning(this,"Warning","Cannot open file:"+file.errorString());
         return;
        }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text=in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void notepad::on_actionSave_as_triggered()
{
    QString fileName=QFileDialog::getSaveFileName(this,"Save as");
        QFile file(fileName);
        if(!file.open(QFile::WriteOnly|QFile::Text)){
            QMessageBox::warning(this,"Warning","Cannot save file:"+file.errorString());

            return;

        }
        currentFile=fileName;
        setWindowTitle(fileName);
        QTextStream out(&file);
        QString text=ui->textEdit->toPlainText();
        out<<text;
        file.close();
}

void notepad::on_actionPrint_triggered()
{
    QPrinter printer;
        printer.setPrinterName("Printer Name");
        QPrintDialog pDialog (&printer,this);

        if(pDialog.exec()==QDialog::Rejected)
        {
            QMessageBox::warning(this,"Warning","Cannot access printer ");
            return;


        }
        ui->textEdit->print(&printer);
}

void notepad::on_actionExit_triggered()
{
    hide();
}

void notepad::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void notepad::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void notepad::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void notepad::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void notepad::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}
