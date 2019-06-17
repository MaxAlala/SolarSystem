#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serverproxy.h"
#include "opencv.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    absolutePath = QCoreApplication::applicationDirPath();
    absolutePath +="/";
    ui->pbar->setRange(0,100);
    ui->pbar->setValue(0);
    ui->slidertop->setRange(0,100);
    ui->sliderdown->setRange(0,100);
    ui->slidertop->setValue(45);
    ui->sliderdown->setValue(90);
    ui->slidertop->setVisible(0);
    ui->sliderdown->setVisible(0);
    ui->Xregime->setVisible(0);
    ui->XYregime->setVisible(0);
    ui->Yregime->setVisible(0);
    ui->full->setVisible(0);
    ui->two->setVisible(0);
    this->setFixedSize(this->width(),this->height());
      this->setWindowTitle("x");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_clicked()

{

    qDebug() <<"  Starting server click..";

    if(serverwasstarted == false){

        serverproxy *sp = new serverproxy(this);
        sp->absolutePath = absolutePath;
        connect(this, SIGNAL(sendFlag_mythread()),sp,SLOT(getFlag_mythread()));
        connect(sp, SIGNAL(sendLog(QString)),this,SLOT(getLog(QString)));
        connect(sp, SIGNAL(sendprogbar(int)),this,SLOT(getprogbar(int)));
        connect(sp, SIGNAL(sendstart()),this,SLOT(getstart()));
        connect(sp, SIGNAL(sendfinish()),this,SLOT(getfinish()));
        connect(this, SIGNAL(sendrestartserver()),sp,SLOT(getrestartserver()));
         connect(this, SIGNAL(sendZ(QString)),sp,SLOT(getZ(QString)));
        sp->start();
        serverwasstarted = true;
    }
    if(ui->start->text() == "createServer"){
        emit(sendFlag_mythread());
        ui->start->setText("Pause");
        ui->start->show();
    }else
        if(ui->start->text() == "Pause"){
            emit(sendFlag_mythread());
            ui->start->setText("Continue");
            ui->start->show();
        }else
            if(ui->start->text() == "Continue"){
                emit(sendFlag_mythread());
                ui->start->setText("Pause");
                ui->start->show();
            }
}


//qDebug() <<"  Starting server thread..";
//ms = new myserver();
//connect(ms, SIGNAL(sendprogbar(int)),this,SLOT(getprogbar(int)));
//connect(ms, SIGNAL(sendstart()),this,SLOT(getstart()));
// connect(ms, SIGNAL(sendfinish()),this,SLOT(getfinish()));
//ms->StartServer();
//exec();
void MainWindow::on_portrait_clicked()
{

    if(counter == 0){
        ui->slidertop->setVisible(1);
        ui->sliderdown->setVisible(1);
        ui->Xregime->setVisible(1);
        ui->XYregime->setVisible(1);
        ui->Yregime->setVisible(1);
        ui->full->setVisible(1);
        ui->two->setVisible(1);
        counter++;
        //        QThread* thread = new QThread;
        opencv* ocv = new opencv();
        ocv->absolutePath = absolutePath.toUtf8().constData();
        //        ocv->moveToThread(thread);void getregime(int);
//        QImage gr(":/lena.jpg");
//        ocv->lena=gr;
//        ui -> label->setPixmap(QPixmap::fromImage(gr));
        //    connect(ocv, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
        connect(this, SIGNAL(takePortrait()), ocv, SLOT(getRequestForPortrait()));
        connect(ocv, SIGNAL(sendPortrait(QImage)), this, SLOT(listenPortrait(QImage)));
        connect(this, SIGNAL(sendFlagON()),ocv,SLOT(getFlagON()));
        connect(this, SIGNAL(sendtopborder(int)),ocv,SLOT(gettopborder(int)));
        connect(this, SIGNAL(sendbottomborder(int)),ocv,SLOT(getbottomborder(int)));
        connect(this, SIGNAL(sendregime(int)),ocv,SLOT(getregime(int)));
        connect(this, SIGNAL(sendcurrentX(int)),ocv,SLOT(getcurrentX(int)));
        connect(this, SIGNAL(sendlenaattach(int)),ocv,SLOT(getlenaattach(int)));
        connect(ocv, SIGNAL(sendLog2(QString)),this,SLOT(getLog2(QString)));

        //    connect(thread, SIGNAL(started()), ocv, SLOT(run()));
        //    connect(ocv, SIGNAL(finished()), thread, SLOT(quit()));
        //    connect(ocv, SIGNAL(finished()), ocv, SLOT(deleteLater()));
        //    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        connect(ocv, SIGNAL(sendImg(QString)),this,SLOT(listenImg(QString)));
        connect(ocv, SIGNAL(sendQImg(QImage)),this,SLOT(listenQImg(QImage)));

        ocv ->start();
    }

    if(ui->portrait->text() == "startCam"){
        ui->slidertop->setVisible(1);
        ui->sliderdown->setVisible(1);
        ui->Xregime->setVisible(1);
        ui->XYregime->setVisible(1);
        ui->Yregime->setVisible(1);
        ui->two->setVisible(1);
        ui->full->setVisible(1);

        emit(sendFlagON());
        ui->portrait->setText("takePortrait");
        ui->portrait->show();
    }else
        if(ui->portrait->text() == "takePortrait"){
            emit(takePortrait());
            ui->Xregime->setVisible(0);
            ui->XYregime->setVisible(0);
            ui->Yregime->setVisible(0);
            ui->slidertop->setVisible(0);
            ui->sliderdown->setVisible(0);
            ui->full->setVisible(0);
            ui->two->setVisible(0);
            ui->portrait->setText("startCam");
            ui->portrait->show();
        }
}



void MainWindow::listenImg(QString str){
    //    qDebug()<<"ich bin hier-MainW!";
    QPixmap pixmap(str);
    ui -> label->setPixmap(pixmap);
    ui -> label->setMask(pixmap.mask());
    ui ->label ->show();

}

void MainWindow::listenQImg(QImage i){
//        qDebug()<<"ich bin hier-MainW!" << i;

    ui -> label->setPixmap(QPixmap::fromImage(i));
    //    ui ->label ->show();

}
void MainWindow::listenPortrait(QImage qi){
    qDebug()<< " listenPortrait!";

    ui -> label->setPixmap(QPixmap::fromImage(qi));
}

void MainWindow::on_pushButton_clicked()
{
    close();
}

void MainWindow::getLog(QString str){
//    qDebug()<< "GOTGOTGOT 3 " << str;
    ui->log->appendPlainText(str);
}
void MainWindow::getLog2(QString str){
//    qDebug()<< "GOTGOTGOT 3 " << str;
    ui->log->appendPlainText(str);
}

void MainWindow::getprogbar(int i){
    ui->pbar->setValue(i);
}


void MainWindow::getfinish(){
    ui->finish_label->setText("Done.");
}

void MainWindow::getstart(){
    ui->finish_label->setText("");
}








void MainWindow::on_portrait_2_clicked()
{

//    QString str = absolutePath+"lenaA.png";
//    QPixmap pixmap(str);

//    emit(sendlenaattach(1));
//    ui -> label->setPixmap(pixmap);
//    ui -> label->setMask(pixmap.mask());
//    ui ->label ->show();
//    if (QFile::exists(absolutePath + "points.txt"))
//    {
//        QFile::remove(absolutePath + "points.txt");
//    }

    if(ui->portrait_2->text() == "downloadImg"){
        ui->portrait_2->setText("unattachImg");
        emit(sendlenaattach(1));
    }else if(ui->portrait_2->text() == "unattachImg"){
        ui->portrait_2->setText("downloadImg");
        emit(sendlenaattach(0));
    }

//    QFile::copy(absolutePath +"lenas_points.txt", absolutePath + "points.txt");
}



void MainWindow::on_sliderdown_valueChanged(int value)
{
emit(sendbottomborder(value));
}

void MainWindow::on_slidertop_valueChanged(int value)
{
emit(sendtopborder(value));
}

void MainWindow::on_XYregime_clicked()
{
    ui->XYregime->setStyleSheet("QPushButton {background-color: #6000DB;color:black;}");
    ui->Xregime->setStyleSheet("");
    ui->Yregime->setStyleSheet("");
    emit(sendregime(0));
}

void MainWindow::on_Yregime_clicked()
{
//    qDebug()<<QCoreApplication::applicationDirPath();

    ui->Yregime->setStyleSheet("QPushButton {background-color: #6000DB;color:black;}");
    ui->XYregime->setStyleSheet("");
    ui->Xregime->setStyleSheet("");
    emit(sendregime(2));
}

void MainWindow::on_Xregime_clicked()
{
    ui->Xregime->setStyleSheet("QPushButton {background-color: #6000DB;color:black;}");
    ui->XYregime->setStyleSheet("");
    ui->Yregime->setStyleSheet("");
    emit(sendregime(1));
}


void MainWindow::on_two_clicked()
{
    ui->two->setStyleSheet("QPushButton {background-color: #6000DB;color:black;}");
    ui->full->setStyleSheet("");
    emit(sendcurrentX(0));
}

void MainWindow::on_full_clicked()
{
    ui->full->setStyleSheet("QPushButton {background-color: #6000DB;color:black;}");
    ui->two->setStyleSheet("");
    emit(sendcurrentX(1));
}

void MainWindow::on_pushButton_2_clicked()
{
emit(sendrestartserver());
}



void MainWindow::on_clear_clicked()
{
        ui->log->clear();
}

void MainWindow::on_sendZ_clicked()
{
emit(sendZ(ui->inputZ->text()));
}
