#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "enums_constants.h"
using namespace::std;

class mythread : public QThread
{
    Q_OBJECT
public:

    explicit mythread(int ID, QObject *parent = 0, CurrentX reg = TWO_ELEM_REGIME);
    void run();
    QString& getAbsolutePath();
signals:
    void error(QTcpSocket::SocketError socketerror);
    void sendprogbar(int);
    void sendfinish();
    void sendstart();
    void sendLog(QString);
public slots:
    void getFlag_mythread();
    void disconnected();
    void getrestartserver();
    void getZ(QString);
    void sockReady();
    void getcurrentX(int);
private:
    void startTransferTwoElement();
    void startTransferAllElement();
    int someFunCounter = 0;
    CurrentX elemcountregime;
    QTcpSocket *socket;
    int socketDescriptor; //sock id
    QByteArray Data;
    QString s = "<Server><Pos2><X>1.0</X><Y>1.0</Y><Z>0.65</Z><A>51.15</A><B>-79.44</B><C>148.0</C><S>2</S><T>3</T></Pos2></Server>";
    int counter = 0;
    int counter2 = 0;
    char buf[4096];
    string out = "<Server><Pos2><X>1.0</X><Y>1.0</Y><Z>0.65</Z><A>51.15</A><B>-79.44</B><C>148.0</C><S>2</S><T>3</T></Pos2></Server>";
    string in = "";
    QString Z = "0.15";
    volatile bool flag = true;
    int isrestarted = 0;
    bool wasfinished = false;
    QString absolutePath = "";

};

#endif // MYTHREAD_H
