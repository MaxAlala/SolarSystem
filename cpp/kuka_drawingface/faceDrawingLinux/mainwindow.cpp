#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
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

/*!
* \brief creates server when createServer button was pushed
*/
void MainWindow::on_start_clicked()
{
    if(ui->start->text() == "createServer"){
        qDebug() <<"  Starting server click..";
        serverproxy *sp = new serverproxy(this);
        sp->getabsolutePath() = absolutePath;
        connect(this, SIGNAL(sendcurrentRegime(int)),sp,SLOT(getCurrentRegime(int)));
        connect(this, SIGNAL(sendFlag_mythread()),sp,SLOT(getFlag_mythread()));
        connect(sp, SIGNAL(sendLog(QString)),this,SLOT(getLog(QString)));
        connect(sp, SIGNAL(sendprogbar(int)),this,SLOT(getprogbar(int)));
        connect(sp, SIGNAL(sendstart()),this,SLOT(getstart()));
        connect(sp, SIGNAL(sendfinish()),this,SLOT(getfinish()));
        connect(this, SIGNAL(sendrestartserver()),sp,SLOT(getrestartserver()));
        connect(this, SIGNAL(sendZ(QString)),sp,SLOT(getZ(QString)));
        sp->start();
        serverwasstarted = true;
        emit(sendcurrentRegime(currentRegime));
//        emit(sendFlag_mythread()); // flag to true
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

/*!
* \brief create an openCV thread when startCam was pushed
*/
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
        opencv* ocv = new opencv();
        ocv->getAbsolutePath() = absolutePath.toUtf8().constData();
        connect(this, SIGNAL(aboutToQuit()), ocv, SLOT(deleteLater()));
        connect(this, SIGNAL(takePortrait()), ocv, SLOT(getRequestForPortrait()));
        connect(ocv, SIGNAL(sendPortrait(QImage)), this, SLOT(listenPortrait(QImage)));
        connect(this, SIGNAL(sendFlagON()),ocv,SLOT(getFlagON()));
        connect(this, SIGNAL(sendtopborder(int)),ocv,SLOT(gettopborder(int)));
        connect(this, SIGNAL(sendbottomborder(int)),ocv,SLOT(getbottomborder(int)));
        connect(this, SIGNAL(sendregime(int)),ocv,SLOT(getregime(int)));
        connect(this, SIGNAL(sendcurrentRegime(int)),ocv,SLOT(getCurrentRegime(int)));
        connect(this, SIGNAL(sendAttachedImageFlag(int)),ocv,SLOT(getAttachedImageFlag(int)));
        connect(ocv, SIGNAL(sendLog2(QString)),this,SLOT(getLog2(QString)));
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

//        emit(sendFlagON());
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
            counter = 0;
            defaultSettings();
        }
}

/*!
* \brief gets an image from an opencv thread, attaches it
*/

void MainWindow::listenQImg(QImage i){
    //        qDebug()<<"ich bin hier-MainW!" << i;
    ui -> label->setPixmap(QPixmap::fromImage(i));
}

/*!
* \brief the exit button
*/
void MainWindow::on_pushButton_clicked()
{
    emit(aboutToQuit());
    close();
}

/*!
* \brief gets logs from all threads and displays them
*/
void MainWindow::getLog(QString str){
    if(str == "Close connection. Stop server. ")
        ui->start->setText("createServer");
    ui->log->appendPlainText(str);
}

/*!
* \brief gets logs from all threads and displays them
*/
void MainWindow::getLog2(QString str){
    ui->log->appendPlainText(str);
}

/*!
* \brief gets a percentage of finished work( how many percents of sent coordinates to the robot controller)
*/
void MainWindow::getprogbar(int i){
    ui->pbar->setValue(i);
}

/*!
* \brief if all coordinates were sent to the robotic controller, sets text "Done"
*/
void MainWindow::getfinish(){
    ui->finish_label->setText("Done.");
}

/*!
* \brief changes text from Done to ""
*/
void MainWindow::getstart(){
    ui->finish_label->setText("");
}


/*!
* \brief this method is called when the downloadImg button was pushed
*/
void MainWindow::on_portrait_2_clicked()
{
    if(ui->portrait_2->text() == "downloadImg"){
        ui->portrait_2->setText("unattachImg");
        emit(sendAttachedImageFlag(1));
    }else if(ui->portrait_2->text() == "unattachImg"){
        ui->portrait_2->setText("downloadImg");
        emit(sendAttachedImageFlag(0));
    }
}

/*!
* \brief this method sends changes of the threshold slider
*/
void MainWindow::on_sliderdown_valueChanged(int value)
{
    emit(sendbottomborder(value));
}

/*!
* \brief this method sends changes of the threshold slider
*/
void MainWindow::on_slidertop_valueChanged(int value)
{
    emit(sendtopborder(value));
}

/*!
* \brief this method sends changes of the regime, change button`s color
*/
void MainWindow::on_XYregime_clicked()
{
    ui->XYregime->setStyleSheet("QPushButton {background-color: #6000DB;color:black;}");
    ui->Xregime->setStyleSheet("");
    ui->Yregime->setStyleSheet("");
    emit(sendregime(0));
}

/*!
* \brief this method sends changes of the regime
*/
void MainWindow::on_Yregime_clicked()
{
    ui->Yregime->setStyleSheet("QPushButton {background-color: #6000DB;color:black;}");
    ui->XYregime->setStyleSheet("");
    ui->Xregime->setStyleSheet("");
    emit(sendregime(2));
}

/*!
* \brief this method sends changes of the regime( first for x or y)
*/
void MainWindow::on_Xregime_clicked()
{
    ui->Xregime->setStyleSheet("QPushButton {background-color: #6000DB;color:black;}");
    ui->XYregime->setStyleSheet("");
    ui->Yregime->setStyleSheet("");
    emit(sendregime(1));
}

/*!
* \brief sets default settings
*/
void MainWindow::defaultSettings()
{
    ui->full->setStyleSheet("");
    ui->XYregime->setStyleSheet("");
    ui->Yregime->setStyleSheet("");
    ui->Xregime->setStyleSheet("");
    ui->portrait_2->setText("downloadImg");
}

/*!
* \brief this method sends changes of the regime , sends new regime to the openCV class
*/
void MainWindow::on_two_clicked()
{
    ui->two->setStyleSheet("QPushButton {background-color: #6000DB;color:black;}");
    ui->full->setStyleSheet("");
    emit(sendcurrentRegime(0));
    currentRegime = TWO_ELEM_REGIME;
}

/*!
* \brief this method sends changes of the regime, sends new regime to the openCV class
*/
void MainWindow::on_full_clicked()
{
    ui->full->setStyleSheet("QPushButton {background-color: #6000DB;color:black;}");
    ui->two->setStyleSheet("");
    emit(sendcurrentRegime(1));
    qDebug() << "current regime send!";
    currentRegime = ALL_ELEM_REGIME;
}

/*!
* \brief this method is called when the restartServer button was pushed, restarts the server
*/
void MainWindow::on_pushButton_2_clicked()
{
    emit(sendrestartserver());
}

/*!
* \brief this method is called when the clear button was pushed, clears log table
*/
void MainWindow::on_clear_clicked()
{
    ui->log->clear();
}

/*!
* \brief this method is called when the sendZ button was pushed, sends Z to the server
*/
void MainWindow::on_sendZ_clicked()
{
    emit(sendZ(ui->inputZ->text()));
}

\
