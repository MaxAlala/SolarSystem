#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace::std;

class mythread : public QThread
{
    Q_OBJECT
public:
    enum ElemCountRegime{
        TwoElem, AllElem
    };
    explicit mythread(int ID, QObject *parent = 0, ElemCountRegime reg = TwoElem);
    void run();
    QString absolutePath = "";

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
ElemCountRegime  elemcountregime;
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
    bool flag = true;
    int isrestarted = 0;
    bool wasfinished = false;

};



#endif // MYTHREAD_H
