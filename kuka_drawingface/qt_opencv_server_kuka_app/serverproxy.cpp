#include "serverproxy.h"


serverproxy::serverproxy(QObject *parent) : QThread(parent)
{

}


void serverproxy:: run(){

    qDebug() <<"  Starting server thread..";
    ms = new myserver();
   connect(ms, SIGNAL(sendprogbar(int)),this,SLOT(getprogbar(int)));
    connect(ms, SIGNAL(sendstart()),this,SLOT(getstart()));
     connect(ms, SIGNAL(sendfinish()),this,SLOT(getfinish()));
    ms->StartServer();
   exec();
}
//////////////////

void serverproxy::getprogbar(int i){
    emit(sendprogbar(i));
}


void serverproxy::getfinish(){
    emit(sendfinish());
}
void serverproxy::getstart(){
    emit(sendstart());
}
