/*!
\file
\brief this file contains QMainWindow class and its dependencies.

Данный файл содержит в себе определения основных
классов, используемых в демонстрационной программе
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QBitmap>
#include <QMainWindow>
#include "serverproxy.h"
#include "opencv.h"
#include "enums_constants.h"
using namespace::std;
namespace Ui {

class MainWindow;
}

/*!

    \brief the meaning of this class is to maintain all GUI components(buttons, lists, etc), handle all signals and slots
    \author Mx
    \version 1.0
    \date February 5, 2020
    \warning nothing
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /*!
    * \brief creates server when createServer button was pushed
    */
    void on_start_clicked();

    /*!
    * \brief gets an image from an opencv thread, attaches it
    */
    void listenQImg(QImage);

    /*!
    * \brief create an openCV thread when startCam was pushed
    */
    void on_portrait_clicked();

    /*!
    * \brief the exit button
    */
    void on_pushButton_clicked();

    /*!
    * \brief gets a percentage of finished work( how many percents of sent coordinates to the robot controller)
    */
    void getprogbar(int);


    /*!
    * \brief if all coordinates were sent to the robotic controller, sets text "Done"
    */
    void getfinish();

    /*!
    * \brief changes text from "Done" to ""
    */
    void getstart();

    /*!
    * \brief this method is called when the downloadImg button was pushed
    */
    void on_portrait_2_clicked();


    /*!
    * \brief gets logs from all threads and displays them
    */void getLog(QString);


    /*!
    * \brief gets logs from all threads and displays them
    */
    void getLog2(QString);

    /*!
    * \brief this method sends changes of the threshold slider
    */
    void on_sliderdown_valueChanged(int value);

    /*!
    * \brief this method sends changes of the threshold slider
    */
    void on_slidertop_valueChanged(int value);

    /*!
    * \brief this method sends changes of the regime( first for x and then first for y)
    */
    void on_XYregime_clicked();

    /*!
    * \brief this method sends changes of the regime( first for x or y)
    */
    void on_Yregime_clicked();

    /*!
    * \brief this method sends changes of the regime( first for x or y)
    */
    void on_Xregime_clicked();

    /*!
    * \brief this method sends changes of the regime , sends new regime to the openCV class
    */
    void on_two_clicked();

    /*!
    * \brief this method sends changes of the regime, sends new regime to the openCV class
    */
    void on_full_clicked();

    /*!
    * \brief this method is called when the restartServer button was pushed, restarts the server
    */
    void on_pushButton_2_clicked();

    /*!
    * \brief this method is called when the clear button was pushed, clears log table
    */
    void on_clear_clicked();

    /*!
    * \brief this method is called when the sendZ button was pushed, sends Z to the server
    */
    void on_sendZ_clicked();

    /*!
    * \brief sets default settings
    */
    void defaultSettings();



private:
    /*!
    * \brief represent current regime( two or all points regime)
    */
    CurrentRegime currentRegime = TWO_ELEM_REGIME;

    /*!
    * \brief for some logic of changing text of the button
    */
    int counter = 0;

    /*!
    * \brief shows if server was started
    */
    bool serverwasstarted = false;

    /*!
    * \brief path to the folder with exe file
    */
    QString absolutePath = "";
    Ui::MainWindow *ui;

signals:
    /*!
    * \brief  gets a Z coordinate
    */
    void sendZ(QString);
    /*!
     * \brief sends current regime(2 or all points line image)
     */
    void sendcurrentRegime(int);

    /*!
     * \brief if some push takePortrait == sendingFlag is true then an image will sent to the MainWindow( here it will be displayed)
     */
    void takePortrait();

    /*!
    * \brief gets & sends pause protocol flag futher
    */
    void sendFlag_mythread();


    /*!
     * \brief sends the top threshold for the Canny algorithm
     */
    void sendtopborder(int);

    /*!
     * \brief sends the bottom threshold for the Canny algorithm
     */
    void sendbottomborder(int);

    /*!
    * \brief  sends changes of the regime(first for x or y)
    */
    void sendregime(int);

    /*!
    * \brief sends a flag telling whether an image was attached( it happens then a takePortrait button was pushed)
    */
    void sendAttachedImageFlag(int);

    /*!
    * \brief sends restart server flag further to restart server
    */
    void sendrestartserver();
    /*!
    * \brief emitted by the exit button, terminates the application
    */
    void aboutToQuit();
};

#endif // MAINWINDOW_H
