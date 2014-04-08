#include "notepad.h"
#include "ui_notepad.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

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

void notepad::on_quitButton_clicked()
{
    qApp->quit();
}

void notepad::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
               tr("Text Files (*.txt);;C++ Files (*.cpp *.h);;Document Files (*.doc);;All Files(*.*)"));

       if (!fileName.isEmpty()) {
           QFile file(fileName);
           if (!file.open(QIODevice::ReadOnly)) {
               QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
               return;
           }
           QTextStream in(&file);
           ui->textEdit->setText(in.readAll());
           file.close();
       }
}

void notepad::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(),
                tr("Text Files (*.txt);;C++ Files (*.cpp *.h);;Document Files (*.doc);;All Files(*.*)"));

        if (!fileName.isEmpty()) {

            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                // error message
            } else {
                QTextStream stream(&file);
                stream << ui->textEdit->toPlainText();
                stream.flush();
                file.close();
            }
        }
}
