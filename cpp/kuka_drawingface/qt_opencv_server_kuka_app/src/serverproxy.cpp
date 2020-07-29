#include "serverproxy.h"


serverproxy::serverproxy(QObject *parent) : QThread(parent)
{
}

/*!
* \brief gets & sends an absolute path
*/
QString& serverproxy::getabsolutePath(){
    return absolutePath;
}

/*!
* \brief gets & sends stop protocol flag futher
*/
void serverproxy::getFlag_mythread(){
    emit(sendFlag_mythread());
}

/*!
* \brief  gets logs and sends it further
*/
void serverproxy::getLog(QString str){
    emit(sendLog(str));
}

/*!
* \brief sends restart server flag further to restart server
*/
void serverproxy::getrestartserver(){
    emit(sendrestartserver());
}

/*!
* \brief  gets Z coordinate and sends it further
*/
void serverproxy::getZ(QString str){
    emit(sendZ(str));
}

/*!
* \brief gets current regime(2 or all points line image)
*/
void serverproxy::getcurrentRegime(int i){
    qDebug()<< "serverproxy getcurrentx";
    emit(sendcurrentRegime(i));
    switch(i){
    case 0:
        currentRegime = TWO_ELEM_REGIME;
        break;
    case 1:
        currentRegime = ALL_ELEM_REGIME;
    }
}

/*!
* \brief this method create a server instance
*/
void serverproxy:: run(){

    qDebug() <<"  Starting server thread..";
    emit(sendLog("  Starting server thread.."));
    myserver* ms = new myserver();
    ms->getAbsolutePath() = absolutePath;
    connect(this, SIGNAL(sendcurrentRegime(int)),ms,SLOT(getcurrentRegime(int)));
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
    emit(sendcurrentRegime(currentRegime));
    exec();
}

/*!
* \brief gets & sends progress bar information
*/
void serverproxy::getprogbar(int i){
    emit(sendprogbar(i));
}

/*!
* \brief if all coordinates were sent to the robotic controller, sets text "Done"
*/
void serverproxy::getfinish(){
    emit(sendfinish());
}

/*!
* \brief changes text from "Done" to ""
*/
void serverproxy::getstart(){
    emit(sendstart());
}
