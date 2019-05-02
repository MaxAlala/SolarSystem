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

    void run();
signals:
     void sendprogbar(int);
     void sendfinish();
     void sendstart();

public slots:
    void getprogbar(int);
    void getstart();
    void getfinish();

private:
    myserver *ms;

  };


#endif // SERVERPROXY_H
//////////
