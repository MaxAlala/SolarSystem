#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QDebug>
#include "mythread.h"

class myserver : public QTcpServer
{
    Q_OBJECT
public:
    explicit myserver(QObject *parent = nullptr);
    void StartServer();
signals:
    void sendprogbar(int);
    void sendfinish();
    void sendstart();

public slots:
   void getprogbar(int);
   void getstart();
   void getfinish();

protected:
    void incomingConnection(int socketDescriptor);

};

#endif // MYSERVER_H
