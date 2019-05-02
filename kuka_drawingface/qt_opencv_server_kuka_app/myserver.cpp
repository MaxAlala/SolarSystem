#include "myserver.h"

myserver::myserver(QObject *parent) : QTcpServer(parent)
{

}



void myserver::StartServer()
{
    if(!this->listen(QHostAddress::Any,59152)){
        qDebug() <<"coudnt start server";

    }else{
        qDebug() << "Listening..";
    }
}

void myserver::getprogbar(int i){
    emit(sendprogbar(i));
}

void myserver::incomingConnection(int socketDescriptor)
{


 qDebug() << socketDescriptor << " Connecting ..";
 mythread *thread = new mythread(socketDescriptor, this);
 connect(thread, SIGNAL(sendprogbar(int)), this, SLOT(getprogbar(int)));
 connect(thread, SIGNAL(sendstart()),this,SLOT(getstart()));
  connect(thread, SIGNAL(sendfinish()),this,SLOT(getfinish()));
 connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
 thread -> start();
}

void myserver::getfinish(){
    emit(sendfinish());
}

void myserver::getstart(){
    emit(sendstart());
}
