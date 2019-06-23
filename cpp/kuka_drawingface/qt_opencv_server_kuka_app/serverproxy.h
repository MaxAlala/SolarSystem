#ifndef SERVERPROXY_H
#define SERVERPROXY_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include "myserver.h"

using namespace::std;
class serverproxy : public QThread
{
    Q_OBJECT
public:
    explicit serverproxy(QObject *parent = nullptr);
    QString absolutePath = "";
    void run();
signals:
    void sendZ(QString);
    void sendprogbar(int);
    void sendfinish();
    void sendstart();
    void sendFlag_mythread();
    void sendLog(QString);
    void sendrestartserver();
    void sendcurrentX(int);
public slots:
    void getcurrentX(int);
    void getZ(QString);
    void getprogbar(int);
    void getstart();
    void getfinish();
    void getFlag_mythread();
    void getLog(QString);
    void getrestartserver();
private:

};


#endif // SERVERPROXY_H
//////////
