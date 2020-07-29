#include "mythread.h"
#include <QThread>
#include <QFile>
#include <QDataStream>
mythread::mythread(int ID, QObject *parent, CurrentRegime reg) : QThread(parent)
{
    this->elemcountregime = ALL_ELEM_REGIME;
    this-> socketDescriptor = ID;
}

QString& mythread::getAbsolutePath (){
    return absolutePath;
}

void mythread::getcurrentRegime(int i){
    switch (i) {
    case ALL_ELEM_REGIME:
        qDebug()<< "hello_all_elem";
        elemcountregime = ALL_ELEM_REGIME;
        break;
    case TWO_ELEM_REGIME:
        qDebug()<< "hello_two_elem";
        elemcountregime = TWO_ELEM_REGIME;
        break;
    }
}

void mythread::getrestartserver(){
    isrestarted = 1;
    wasfinished = false;
}

void mythread::getFlag_mythread(){
    qDebug()<<"flag";
    if (flag == false)flag = true;
    else flag = false;
    qDebug()<< flag << " now!";
    emit(sendLog(flag+" current flag"));
}

void mythread::getZ(QString str){
    Z = str;
}

/*!
* \brief this method is called when a server has an incoming connection, creates connection with a client and sends coordinates
*/
void mythread:: run(){
    qDebug() << socketDescriptor <<"  Starting thread..";
    QString s = QString::number(socketDescriptor);
    emit(sendLog(s+"  Starting thread.."));
    socket = new QTcpSocket(this);

    if(!socket -> setSocketDescriptor(this -> socketDescriptor)){
        emit error(socket -> error());
        return;
    }
    connect(socket, SIGNAL(readyRead()), this, SLOT(sockReady()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    s = QString::number(socketDescriptor);
    qDebug() << socketDescriptor << " Client connected";
    emit(sendLog(s+" Client connected"));

    if(elemcountregime == TWO_ELEM_REGIME){
        startTransferTwoElement();
    }else {
        startTransferTwoElement();
        qDebug()<< " hello";
    }
}

/*!
* \brief sends txt file with points == if you chose full regime(line that is described by many points)
*/
void mythread::startTransferAllElement(){
    QString path = absolutePath +"pointsFull.txt";
    QFile file(path);

    if(file.open(QIODevice::ReadWrite | QIODevice::Text)){
        QDataStream socketStream(socket);
        QTextStream fileStream(&file);
        QByteArray mydata=file.readAll();
        qDebug() << "Final Testing is size = " << mydata.size();
        socket->write(mydata);
    }
    socket->waitForBytesWritten();

}

/*!
* \brief sends coordinates from txt file == if you chose TWO regime(line that is described by 2 points)
*/
void mythread::startTransferTwoElement(){
    while(wasfinished != true){
        while(wasfinished == true){qDebug()<< "finished!///////////////";}
        emit(sendstart());
        vector<double> vecX;
        vector<double> vecY;
        QString path = absolutePath + "pointsFull.txt";
        QByteArray ba = path.toLocal8Bit();
        const char *c_str2 = ba.data();
        ifstream file(c_str2);  //read points
        string first;
        string second;
        string entire;
        int numberOfColor = 3;
        double x1;
        double y1;
        double x2;
        double y2;
        volatile int counterForVec = 0; // counts current point
        if (file.is_open()) {   // read all points from the file
            while (getline(file, entire))
            {
                int pos = entire.find(" ");
                entire = entire.substr(pos+1, entire.size()-1); // get rid of a counter
                pos = entire.find(" ");
                first = entire.substr(0, pos);
                second = entire.substr(pos+1, entire.size()-1);

                x1 = atof(first.c_str());
                y1 = atof(second.c_str());
                //                qDebug() << x1 << " " << y1 << endl;
                vecX.push_back(x1);
                //                vecX.push_back(x2);
                vecY.push_back(y1);

                //                vecY.push_back(y2);
            }
        }else{
            qDebug() << "cannot open file!";
            emit(sendLog("cannot open file!"));
            return;
        }
        // qDebug() << vecX.size() << "SIZW!";
        string a = "44";
        string b = "-77.86";
        string c = "142.09";
        while(static_cast<int>(counterForVec) != static_cast<int>(vecX.size()-1)){
            //             qDebug() << vecX << " SIZEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE222!";
            if(flag == true){ // pause the process
                //            qDebug() << vecX << " SIZEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE111!";
                emit(sendprogbar(static_cast<double>(counterForVec)/(vecX.size()-1)*100));

                while(s == ""){ // waits for a flag
                    socket->waitForReadyRead(100);
                    Data = socket->readAll();
                    s = Data.data();

                    if(s != ""){
                        QString st = QString::number(counter);
                        QString s_buf =st + " from client: " + s;

                        emit(sendLog(s_buf));
                    }
                }
                string currentColor = "";

                //                 emit(sendLog(QString::fromStdString(std::to_string(counterForVec))));
                if(counterForVec % 10 == 0){ // if new package check if u need to change angles
                    if(numberOfColor == 3){
                        if( static_cast<double>(counterForVec)/(vecX.size()-1)*100 < 33){
                            currentColor = "1";//left
                            a = "14.4";
                            b = "-81";
                            c = "172";
                        }else if( static_cast<double>(counterForVec)/(vecX.size()-1)*100 < 66){
                            a = "44";
                            b = "-77";
                            c = "142";
                            currentColor = "2";//cental
                        }else if( static_cast<double>(counterForVec)/(vecX.size()-1)*100 <= 100){// right
                            a = "63";
                            b = "-69";
                            c = "121";
                            currentColor = "3";
                        }
                    }
                }
                qDebug()<< vecX.size() - 1 << " "<<counterForVec;
                if(vecX.size() - 1 < counterForVec){

                    qDebug("ERROR will occur!");
                    break;
                }
                out = "<Server><Pos2><X>" + to_string(vecX.at(counterForVec)) + "</X><Y>"+ to_string(vecY.at(counterForVec)+30)+"</Y><Z>"+  Z.toUtf8().constData() +"</Z><A>" + a + "</A><B>" + b + "</B><C>" + c + "</C></Pos2></Server>";
                strcpy(buf, out.c_str());
                counterForVec++;
                qDebug() << QString::fromStdString(out) << "want to send this message";
                socket->write(buf);
                counter +=1;
                counter2++;
                s = "";
            }
            qDebug("ERROR will occur4!");

            if(isrestarted == 1){
                break;
            }
        }
        qDebug("ERROR will occur3!");
        if(isrestarted == 1){
            counter = 0;
            isrestarted = 0;
            file.close();
            emit(sendLog("restarting process..."));
            continue;
        }

        qDebug("ERROR will occur2!");

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
    //    emit(sendLog("Close connection. Stop server. "));
    socket->deleteLater(); // delete object
    this->exit(0);
    //    exit(0);
}
