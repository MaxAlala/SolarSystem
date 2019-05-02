#include "mythread.h"
#include <QThread>

mythread::mythread(int ID, QObject *parent) : QThread(parent)
{

    this-> socketDescriptor = ID;

}

// no longer need you
void mythread:: run(){

emit(sendstart());
    vector<double> vecX;
    vector<double> vecY;
ifstream file("C:\\Users\\X\\Desktop\\ws\\opencv\\KUKA-face-picturing\\qt_opencv_server_kuka_app\\points.txt");  //read points
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
//     cout << first << " fs " << second << endl;
        // process pair (a,b)
     pos = first.find(" ");
     x1 = atof(first.substr(0,pos).c_str());
     y1 = atof(first.substr(pos+1, first.size()-1).c_str());
     pos = second.find(" ");
     x2 = atof(second.substr(0,pos).c_str());
     y2 = atof(second.substr(pos+1, second.size()-1).c_str());
// cout << x1 << " fir " << y1 << endl;
//  cout << x2 << " sec " << y2 << endl;
     vecX.push_back(x1);
     vecX.push_back(x2);

     vecY.push_back(y1);
     vecY.push_back(y2);


    }
    }else{
        qDebug() << "cannot open file!";
        return;
    }

    qDebug() << socketDescriptor <<"  Starting thread..";
    socket = new QTcpSocket();
    if(!socket -> setSocketDescriptor(this -> socketDescriptor)){
        emit error(socket -> error());
        return;
    }

//    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);

qDebug() << socketDescriptor << " Client connected";
int counterForVec = 0;
double percentage = 0;

while(counterForVec != vecX.size()-2){
    qDebug() << counterForVec << " " << vecX.size();
    emit(sendprogbar((double)counterForVec/(vecX.size()-1)*100));
   while(counter2 < 2){
//QString  qs =  "<Server><Pos2><X>1.000000</X><Y>0.000000</Y><Z>0.000000</Z><A>0.000000</A><B>0.000000</B><C>0.000000</C><S>2</S><T>3</T></Pos2></Server>";
//QByteArray qba = qs.toUtf8();
//qDebug() << qba;
       out ="<Server><Pos2><X>" + to_string(vecX.at(counterForVec)) + "</X><Y>"+ to_string(vecY.at(counterForVec))+"</Y><Z>-0.6</Z><A>65.75</A><B>-81.44</B><C>165.0</C><S>2</S><T>3</T></Pos2></Server>";
//        out = "<Server><Pos2><X>1.000000</X><Y>0.000000</Y><Z>0.000000</Z><A>0.000000</A><B>0.000000</B><C>0.000000</C><S>2</S><T>3</T></Pos2></Server>";
 strcpy(buf, out.c_str());
 counterForVec++;
    socket->write(buf);
//<Server><Pos2><X>0.000000</X><Y>0.000000</Y><Z>0.000000</Z><A>0.000000</A><B>0.000000</B><C>0.000000</C><S>0</S><T>0</T></Pos2></Server>"
//<Server><Pos2><X>74.400000</X><Y>5.000000</Y><Z>30</Z><A>0</A><B>0</B><C>0</C><T>1</T><S>3</S></Pos2></Server>

    counter +=1;
     counter2++;
     s = "";
while(s ==""){
      socket->waitForReadyRead(100);
       Data = socket->readAll();
       s = Data.data();
}
       qDebug()<<counter <<" from client: " <<s;
     }

   while(s != "<Robot><Cmd>100</Cmd></Robot>") {

             socket->waitForReadyRead(100);
              Data = socket->readAll();
              s = Data.data();
              if(s == "<Robot><Cmd>100</Cmd></Robot>"){
                   counter2 = 0;
                   qDebug()<<"Got flag "<< s;


              }
}
}
 emit(sendprogbar(100));
qDebug() << "myThread: I have finished! ";
emit(sendfinish());
file.close();
exec();
}
//void mythread::readyRead(){
//    QByteArray Data = socket -> readAll();
//    qDebug() << socketDescriptor << " Data in: "<< Data;
//    socket -> write(Data);
//}
void mythread::disconnected(){

    qDebug() << socketDescriptor <<"  Disconnected thread..";

    socket->deleteLater(); // delete object
    exit(0);
}

///////////////////////
