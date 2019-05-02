#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serverproxy.h"
#include "opencv.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pbar->setRange(0,100);
    ui->pbar->setValue(0);
 this->setFixedSize(this->width(),this->height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_clicked()
{
    serverproxy *sp = new serverproxy(this);
    connect(sp, SIGNAL(sendprogbar(int)),this,SLOT(getprogbar(int)));
    connect(sp, SIGNAL(sendstart()),this,SLOT(getstart()));
     connect(sp, SIGNAL(sendfinish()),this,SLOT(getfinish()));
    sp->start();


}

void MainWindow::on_portrait_clicked()
{
    opencv* ocv = new opencv();
    connect(ocv, SIGNAL(sendImg(QString)),this,SLOT(listenImg(QString)));
    ocv ->start();
}

void MainWindow::listenImg(QString str){
    qDebug()<<"ich bin hier-MainW!";
    QPixmap pixmap(str);
    ui -> label->setPixmap(pixmap);
    ui -> label->setMask(pixmap.mask());
    ui ->label ->show();

}

void MainWindow::on_pushButton_clicked()
{
    close();
}

void MainWindow::getprogbar(int i){
qDebug()<<"hey!!!!!!!!!";
ui->pbar->setValue(i);
}


void MainWindow::getfinish(){
    ui->finish_label->setText("Done.");
}

void MainWindow::getstart(){
    ui->finish_label->setText("");
}







