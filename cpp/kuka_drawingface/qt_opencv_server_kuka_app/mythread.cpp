#include "mythread.h"
#include <QThread>

mythread::mythread(int ID, QObject *parent) : QThread(parent)
{
    this-> socketDescriptor = ID;

}

void mythread::getrestartserver(){
//    qDebug()<< "got restart server!!!#$%#$%";

    isrestarted = 1;
    wasfinished = false;
//    else isrestarted = 0;
}
void mythread::getFlag_mythread(){
    if (flag == false)
        flag = true;
    else flag = false;
}
void mythread::getZ(QString str){
    Z = str;
}
// no longer need you
void mythread:: run(){

    qDebug() << socketDescriptor <<"  Starting thread..";
    QString s = QString::number(socketDescriptor);
    emit(sendLog(s+"  Starting thread.."));
    socket = new QTcpSocket();
    if(!socket -> setSocketDescriptor(this -> socketDescriptor)){
        emit error(socket -> error());
        return;
    }

    //    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);
    s = QString::number(socketDescriptor);
    qDebug() << socketDescriptor << " Client connected";
    emit(sendLog(s+" Client connected"));

    while(true){
        while(wasfinished == true){}
//        isrestarted = 0;
        emit(sendstart());
        vector<double> vecX;
        vector<double> vecY;
        QString path = absolutePath + "points.txt";
        QByteArray ba = path.toLocal8Bit();
        const char *c_str2 = ba.data();
        ifstream file(c_str2);  //read points
        string first;
        string second;
        string entire;
        double x1;
        double y1;
        double x2;
        double y2;
        if (file.is_open()) {
            while (getline(file, entire))
            {
                int pos = entire.find(" ");
                entire = entire.substr(pos+1, entire.size()-1);
                pos = entire.find("&");
                first = entire.substr(0, pos);
                second = entire.substr(pos+1, entire.size()-1);
                pos = first.find(" ");
                x1 = atof(first.substr(0,pos).c_str());
                y1 = atof(first.substr(pos+1, first.size()-1).c_str());
                pos = second.find(" ");
                x2 = atof(second.substr(0,pos).c_str());
                y2 = atof(second.substr(pos+1, second.size()-1).c_str());
                vecX.push_back(x1);
                vecX.push_back(x2);

                vecY.push_back(y1);
                vecY.push_back(y2);


            }
        }else{
            qDebug() << "cannot open file!";
            emit(sendLog("cannot open file!"));
            return;
        }

        uint counterForVec = 0;

        while(counterForVec != vecX.size()-2){
            while(flag == false){

            }
            emit(sendprogbar(counterForVec/(vecX.size()-1)*100));
            while(counter2 < 2){
                out ="<Server><Pos2><X>" + to_string(vecX.at(counterForVec)) + "</X><Y>"+ to_string(vecY.at(counterForVec))+"</Y><Z>"+  Z.toUtf8().constData() +"</Z><A>65.75</A><B>-81.44</B><C>150.0</C><S>2</S><T>3</T></Pos2></Server>";
                strcpy(buf, out.c_str());
                counterForVec++;
                socket->write(buf);
                counter +=1;
                counter2++;
                s = "";

                while(s ==""){
                    socket->waitForReadyRead(100);
                    Data = socket->readAll();
                    s = Data.data();
                    if(s != ""){
                        QString st = QString::number(counter);
                        QString s_buf =st + " from client: " + s;
                        emit(sendLog(s_buf));
                    }
                }
                qDebug() <<"from client: " + s;
            }
            if(isrestarted == 1){

                break;
            }
            while(s != "<Robot><Cmd>100</Cmd></Robot>") {

                socket->waitForReadyRead(100);
                Data = socket->readAll();
                s = Data.data();
                if(s == "<Robot><Cmd>100</Cmd></Robot>"){
                    QString s_buf = "got flag: " + s;
                    counter2 = 0;
                    qDebug()<< "Got flag: "<< s;
                    emit(sendLog(s_buf));
                }
            }
        }
        if(isrestarted == 1){
            counter = 0;
            isrestarted = 0;
            file.close();
            emit(sendLog("restarting process..."));
            continue;
        }

        emit(sendprogbar(100));
        qDebug() << "myThread: I have finished! ";
        emit(sendfinish());
        wasfinished = true;
    }
}


void mythread::disconnected(){

    qDebug() << socketDescriptor <<"  Disconnected thread..";
    QString s = QString::number(socketDescriptor);
    emit(sendLog( s + "  Disconnected thread.."));
    socket->deleteLater(); // delete object
    exit(0);
}

///////////////////////
