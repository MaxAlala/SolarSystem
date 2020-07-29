#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix(":/img/earth.jpg");
    int w = ui->earth_image->width();
    int h = ui->earth_image->height();
    ui->earth_image->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_progressBar_valueChanged(int value)
{
//    QMessageBox::critical(this, "Title", "Be careful!");
}


void MainWindow::on_signIn_clicked()
{
    QString login = ui->login_->text();
    QString password =ui->password_->text();

    if(login == "vse" && password == "vse")
    {
        ui2 = new MainWindow2(this);

//        dialog = new Dialog(this);
//        dialog -> show();

        ui2->show();
        ui->statusbar->showMessage("Success. Signed in.");
    }else
    {
        ui->statusbar->showMessage("input password or login is wrong. Please, try again.");
    }
}

void MainWindow::on_actionClose_triggered()
{
    QApplication::quit();
}
