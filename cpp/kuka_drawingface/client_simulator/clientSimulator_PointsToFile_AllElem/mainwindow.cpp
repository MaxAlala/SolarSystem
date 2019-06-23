#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QTextCodec>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(sockReady()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisc()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    socket->connectToHost("127.0.0.1", 59152);
}

void MainWindow::sockReady(){
    QString path = QCoreApplication::applicationDirPath()+ "/fullPointList.txt";
    QFile file(path); // the download path is equal to the directory where the exe file is placed
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "Ошибка открытия";
    }
    QTextStream stream( &file );
    QByteArray data;
    while (socket->waitForReadyRead(3000))
    {
        while(socket->bytesAvailable() > 0)
        {
            data.append(socket->readAll());
            qDebug() << "Final Testing is size = " << data.size();
            socket->flush();
        }
    }
    stream << data;
}

void MainWindow::sockDisc(){
    qDebug() << "disconnected";
    socket->deleteLater();
}











