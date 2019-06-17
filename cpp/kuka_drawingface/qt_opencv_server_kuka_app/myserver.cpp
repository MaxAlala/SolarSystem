#include "myserver.h"

myserver::myserver(QObject *parent) : QTcpServer(parent)
{

}

void myserver::getLog(QString str){
//    qDebug()<< str + "GETLOG";
    emit(sendLog(str));
}

void myserver::StartServer()
{
    if(!this->listen(QHostAddress::Any,59152)){
        qDebug() <<"coudnt start server";\
           emit(sendLog("coudnt start server"));

    }else{
        qDebug() << "Listening..";
         emit(sendLog("Listening.."));
    }
}

void myserver::getprogbar(int i){
    emit(sendprogbar(i));
}

void myserver::getFlag_mythread(){
    emit(sendFlag_mythread());
}
void myserver::getrestartserver(){
    emit(sendrestartserver());
}
void myserver::getZ(QString str){
    emit(sendZ(str));
}
void myserver::incomingConnection(int socketDescriptor)
{
    qDebug() << socketDescriptor << " Connecting ..";
    QString s = QString::number(socketDescriptor);
      emit(sendLog( s + " Connecting .."));
    mythread *thread = new mythread(socketDescriptor, this);
     thread->absolutePath = absolutePath;
    connect(this, SIGNAL(sendZ(QString)),thread,SLOT(getZ(QString)));
    connect(thread, SIGNAL(sendLog(QString)),this,SLOT(getLog(QString)));
    connect(this, SIGNAL(sendFlag_mythread()),thread,SLOT(getFlag_mythread()));
    connect(this, SIGNAL(sendrestartserver()),thread,SLOT(getrestartserver()));
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
