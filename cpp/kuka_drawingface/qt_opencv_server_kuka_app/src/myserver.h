#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QDebug>
#include "mythread.h"
#include "enums_constants.h"
/*!
    \brief the meaning of this class is to create a server and a unique thread for each incomming client.
*/

class myserver : public QTcpServer
{
    Q_OBJECT
public:

    explicit myserver(QObject *parent = nullptr);

    /*!
    * \brief starts server, now it begins to listen if there is a client incoming request for connection
    */
    void StartServer();

    /*!
    * \brief gets & sends an absolute path
    */
    QString& getAbsolutePath();
signals:

    /*!
    * \brief gets & sends progress bar information
    */
    void sendprogbar(int);

    /*!
    * \brief if all coordinates were sent to the robotic controller, sets text "Done"
    */
    void sendfinish();

    /*!
    * \brief gets & sends pause protocol flag futher
    */
    void sendFlag_mythread();

    /*!
    * \brief gets & sends logs
    */
    void sendLog(QString);

    /*!
    * \brief sends restart server flag further to restart server
    */
    void sendrestartserver();


    /*!
    * \brief  gets Z coordinate and sends it further
    */
    void sendZ(QString);
    /*!
    * \brief sends flag that changes text from "Done" to ""
    */
    void sendstart();
    /*!
    * \brief sends current regime(2 or all points line image)
    */
    void sendcurrentRegime(int);
public slots:

    /*!
    * \brief gets & sends progress bar information
    */
    void getprogbar(int);

    /*!
    * \brief if all coordinates were sent to the robotic controller, sets text "Done"
    */
    void getfinish();

    /*!
    * \brief gets & sends stop protocol flag futher
    */
    void getFlag_mythread();

    /*!
    * \brief  gets logs and sends it further
    */
    void getLog(QString);

    /*!
    * \brief sends restart server flag further to restart server
    */
    void getrestartserver();

    /*!
    * \brief  gets Z coordinate and sends it further
    */
    void getZ(QString);

    /*!
    * \brief gets current regime(2 or all points line image)
    */
    void getcurrentRegime(int);

    /*!
    * \brief changes text from "Done" to ""
    */
    void getstart();
private:
    /*!
    * \brief represent current regime( two or all points regime)
    */
    CurrentRegime currentRegime = TWO_ELEM_REGIME;

    /*!
    * \brief path to the folder with exe file
    */
    QString absolutePath = "";
protected:

    /*!
    * \brief this method is called when the there is an incoming connection, it creates a thread for each connection
    */
    void incomingConnection(int socketDescriptor);

};

#endif // MYSERVER_H
