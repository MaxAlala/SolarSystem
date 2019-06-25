#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QDebug>
#include "mythread.h"
#include "enums_constants.h"

class myserver : public QTcpServer
{
    Q_OBJECT
public:

    explicit myserver(QObject *parent = nullptr);
    void StartServer();
    QString& getAbsolutePath();
signals:
    void sendprogbar(int);
    void sendfinish();
    void sendstart();
    void sendFlag_mythread();
    void sendLog(QString);
    void sendrestartserver();
    void sendZ(QString);
    void sendcurrentX(int);
public slots:
    void getprogbar(int);
    void getstart();
    void getfinish();
    void getFlag_mythread();
    void getLog(QString);
    void getrestartserver();
    void getZ(QString);
    void getcurrentX(int);
private:
    CurrentX currentX = TWO_ELEM_REGIME;
    QString absolutePath = "";
protected:
    void incomingConnection(int socketDescriptor);

};

#endif // MYSERVER_H
