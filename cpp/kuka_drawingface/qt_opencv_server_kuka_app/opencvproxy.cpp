#include "opencvproxy.h"

opencvproxy::opencvproxy(QObject *parent ) : QThread(parent)
{

}


void opencvproxy:: run(){

    qDebug() <<"  Starting opencv thread..";
      ocv = new opencv();
//      connect(ocv, SIGNAL(sendImg(QString)),this,SLOT(listenImg(QString)));
      ocv->startopencv();
      exec();

}


void opencvproxy::listenImg(QString str){
    qDebug()<<"ich bin hier ProxyOpencv!";
    emit sendImg(str);
}
