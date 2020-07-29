#ifndef SERVERPROXY_H
#define SERVERPROXY_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include "myserver.h"
using namespace::std;

/*!
    \brief the meaning of this class is to enable the creation of many
    threads of servers( if something happenes with one server u can start another one)
*/

class serverproxy : public QThread
{
    Q_OBJECT
public:
    explicit serverproxy(QObject *parent = nullptr);
    void run();
signals:

    /*!
    * \brief  gets Z coordinate and sends it further
    */
    void sendZ(QString);

    /*!
    * \brief gets & sends progress bar information
    */
    void sendprogbar(int);

    /*!
    * \brief if all coordinates were sent to the robotic controller, sets text "Done"
    */
    void sendfinish();

    /*!
    * \brief sends flag that changes text from "Done" to ""
    */
    void sendstart();

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
    * \brief sends current regime(2 or all points line image)
    */
    void sendcurrentRegime(int);
public slots:

    /*!
    * \brief gets current regime(2 or all points line image)
    */
    void getcurrentRegime(int);

    /*!
    * \brief  gets Z coordinate and sends it further
    */
    void getZ(QString);

    /*!
    * \brief gets & sends progress bar information
    */
    void getprogbar(int);

    /*!
    * \brief changes text from "Done" to ""
    */
    void getstart();

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
    * \brief gets & sends an absolute path
    */
    QString& getabsolutePath();
private:

    /*!
    * \brief represent current regime( two or all points regime)
    */
    CurrentRegime currentRegime = TWO_ELEM_REGIME;

    /*!
    * \brief path to the folder with exe file
    */
    QString absolutePath = "";
};

#endif // SERVERPROXY_H
//////////
