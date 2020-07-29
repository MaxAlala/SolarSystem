#include "myserver.h"

myserver::myserver(QObject *parent) : QTcpServer(parent)
{

}
/*!
* \brief gets current regime(2 or all points line image)
*/
void myserver::getcurrentRegime(int i){
    qDebug()<< "myserver getcurrentx";
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
* \brief gets & sends logs
*/
void myserver::getLog(QString str){
    //    qDebug()<< str + "GETLOG";
    emit(sendLog(str));
}

/*!
* \brief starts server, now it begins to listen if there is a client incoming request for connection
*/
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

/*!
* \brief gets & sends an absolute path
*/
QString& myserver::getAbsolutePath(){
    return absolutePath;
}

/*!
* \brief gets & sends progress bar information
*/
void myserver::getprogbar(int i){
    emit(sendprogbar(i));
}

/*!
* \brief gets & sends stop protocol flag futher
*/
void myserver::getFlag_mythread(){
    emit(sendFlag_mythread());
}

/*!
* \brief sends restart server flag further to restart server
*/
void myserver::getrestartserver(){
    emit(sendrestartserver());
}

/*!
* \brief  gets Z coordinate and sends it further
*/
void myserver::getZ(QString str){
    emit(sendZ(str));
}

/*!
* \brief this method is called when the there is an incoming connection, it creates a thread for each connection
*/
void myserver::incomingConnection(int socketDescriptor)
{
    qDebug() << socketDescriptor << " Connecting ..";
    QString s = QString::number(socketDescriptor);
    emit(sendLog( s + " Connecting .."));
    mythread *thread = new mythread(socketDescriptor, this);
    thread->getAbsolutePath() = absolutePath;
    connect(this, SIGNAL(sendcurrentRegime(int)),thread,SLOT(getcurrentRegime(int)));
    connect(this, SIGNAL(sendZ(QString)),thread,SLOT(getZ(QString)));
    connect(thread, SIGNAL(sendLog(QString)),this,SLOT(getLog(QString)));
    connect(this, SIGNAL(sendFlag_mythread()),thread,SLOT(getFlag_mythread()));
    connect(this, SIGNAL(sendrestartserver()),thread,SLOT(getrestartserver()));
    connect(thread, SIGNAL(sendprogbar(int)), this, SLOT(getprogbar(int)));
    connect(thread, SIGNAL(sendfinish()),this,SLOT(getfinish()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread -> start();
    emit(sendcurrentRegime(currentRegime));
}

/*!
* \brief sends finish flag further
*/
void myserver::getfinish(){
    emit(sendfinish());
}

void myserver::getstart(){
    emit(sendstart());
}



