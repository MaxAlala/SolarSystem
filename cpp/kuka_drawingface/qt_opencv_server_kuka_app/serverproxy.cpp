#include "serverproxy.h"


serverproxy::serverproxy(QObject *parent) : QThread(parent)
{
}

QString& serverproxy::getabsolutePath(){
    return absolutePath;
}

void serverproxy::getFlag_mythread(){
    emit(sendFlag_mythread());
}

void serverproxy::getLog(QString str){
    emit(sendLog(str));
}

void serverproxy::getrestartserver(){
    emit(sendrestartserver());
}

void serverproxy::getZ(QString str){
    emit(sendZ(str));
}

void serverproxy::getcurrentX(int i){
    qDebug()<< "serverproxy getcurrentx";
    emit(sendcurrentX(i));
    switch(i){
    case 0:
        currentX = TWO_ELEM_REGIME;
        break;
    case 1:
        currentX = ALL_ELEM_REGIME;
    }
}

void serverproxy:: run(){

    qDebug() <<"  Starting server thread..";
    emit(sendLog("  Starting server thread.."));
    myserver* ms = new myserver();
    ms->getAbsolutePath() = absolutePath;
    connect(this, SIGNAL(sendcurrentX(int)),ms,SLOT(getcurrentX(int)));
    connect(this, SIGNAL(sendZ(QString)),ms,SLOT(getZ(QString)));
    connect(ms, SIGNAL(sendLog(QString)),this,SLOT(getLog(QString)));
    connect(this, SIGNAL(sendFlag_mythread()),ms,SLOT(getFlag_mythread()));
    connect(this, SIGNAL(sendrestartserver()),ms,SLOT(getrestartserver()));
    connect(ms, SIGNAL(sendprogbar(int)),this,SLOT(getprogbar(int)));
    connect(ms, SIGNAL(sendstart()),this,SLOT(getstart()));
    connect(ms, SIGNAL(sendfinish()),this,SLOT(getfinish()));
    connect(ms, SIGNAL(finished()), ms, SLOT(deleteLater()));
    connect(this, SIGNAL(sendrestartserver()),ms,SLOT(getrestartserver()));
    ms->StartServer();
    emit(sendcurrentX(currentX));
    exec();
}

void serverproxy::getprogbar(int i){
    emit(sendprogbar(i));
}

void serverproxy::getfinish(){
    emit(sendfinish());
}

void serverproxy::getstart(){
    emit(sendstart());
}
