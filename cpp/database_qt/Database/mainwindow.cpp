#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlError>
#include <QSqlRecord>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("database");
    db.setUserName("root");
    db.setPassword("1234");
    if(!db.open()){
        qDebug() << db.lastError().text();
    } else {
        qDebug() << "success!";
}


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendRequest_clicked()
{
    QSqlQuery query = QSqlQuery(db);
    if(!query.exec("select * from database")){
        qDebug() << query.lastError().databaseText();
        qDebug() << query.lastError().driverText();
        return;

    }

    while(query.next()){
        qDebug() << query.record();
    }

}
