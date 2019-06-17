#ifndef OPENCVPROXY_H
#define OPENCVPROXY_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include "opencv.h"

class opencvproxy : public QThread
{
    Q_OBJECT
public:
    explicit opencvproxy(QObject *parent = nullptr);
void run();
signals:
    void sendImg(QString);
public slots:
   void listenImg(QString);

private:
    opencv *ocv;
};

#endif // OPENCVPROXY_H
