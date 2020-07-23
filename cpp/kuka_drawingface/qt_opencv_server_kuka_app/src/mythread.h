#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "enums_constants.h"
using namespace::std;

/*!
    \brief the meaning of this class is to create and maintain the connection with a client
*/
class mythread : public QThread
{
    Q_OBJECT
public:

    explicit mythread(int ID, QObject *parent = 0, CurrentRegime reg = TWO_ELEM_REGIME);

    /*!
    * \brief this method is called when a server has an incoming connection, creates connection with a client and sends coordinates
    */
    void run();

    /*!
    * \brief path to the folder with exe file
    */
    QString& getAbsolutePath() ;
signals:
    void error(QTcpSocket::SocketError socketerror);

    /*!
      * \brief gets & sends progress bar information
      */
    void sendprogbar(int);

    /*!
    * \brief if all coordinates were sent to the robotic controller, sets text "Done"
    */
    void sendfinish();

    /*!
    * \brief  gets logs and sends it further
    */
    void sendLog(QString);

    /*!
    * \brief changes text from Done to ""
    */
    void sendstart();
public slots:

    /*!
    * \brief gets stop protocol flag futher
    */
    void getFlag_mythread();

    /*!
    * \brief closes a thread then a socket is closed
    */
    void disconnected();

    /*!
    * \brief gets restart server flag to restart server
    */
    void getrestartserver();

    /*!
    * \brief gets a Z coordinate
    */
    void getZ(QString);


    /*!
    * \brief gets current regime(2 or all points line image)
    */
    void getcurrentRegime(int);
private:

    /*!
    * \brief sends coordinates from txt file == if you chose TWO regime(line that is described by 2 points)
    */
    void startTransferTwoElement();

    /*!
    * \brief sends txt file with points == if you chose full regime(line that consists from many points)
    */
    void startTransferAllElement();

    /*!
    * \brief sends txt file with points == if you chose full regime(line that consists from many points)
    */
    CurrentRegime elemcountregime;


    /*!
    * \brief is a socket instance;
    */
    QTcpSocket *socket;

    /*!
    * \brief id of an incoming socket
    */
    int socketDescriptor; //sock id

    /*!
    * \brief is a buffer where we will read data
    */
    QByteArray Data;

    /*!
    * \brief is a buffer in string format
    */
    QString s = "<Server><Pos2><X>1.0</X><Y>1.0</Y><Z>0.65</Z><A>51.15</A><B>-79.44</B><C>148.0</C><S>2</S><T>3</T></Pos2></Server>";
    /*!
      * \brief  for the protocol
      */
    int counter = 0;

    /*!
      * \brief  a counter for protocol logic
      */
    int counter2 = 0;

    /*!
    * \brief buffer to send some data away
    */
    char buf[4096];

    /*!
    * \brief message to send away
    */
    string out = "<Server><Pos2><X>1.0</X><Y>1.0</Y><Z>0.65</Z><A>129.4</A><B>-77.86</B><C>148.09</C><S>2</S><T>3</T></Pos2></Server>";

    /*!
     * \brief z coordinate of the resulted point
     */
    QString Z ="-15";

    /*!
     * \brief some important flag for the protocol
     */
    volatile bool flag = true;

    /*!
    * \brief this variable becomes one if the restartServer button was pushed that restarts the server
    */
    int isrestarted = 0;

    /*!
    * \brief did the protocol do its job?
    */
    bool wasfinished = false;

    /*!
    * \brief path to the folder with exe file
    */
    QString absolutePath = "";

};

#endif // MYTHREAD_H
