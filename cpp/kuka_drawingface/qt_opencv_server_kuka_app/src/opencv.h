#ifndef OPENCV_H
#define OPENCV_H

#include <QObject>
#include <QDebug>
#include <opencv2/face.hpp>
#include<opencv2/core/core.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>
//#include <iostream>
#include <QThread>
#include <QImage>
#include <QDebug>
using namespace std;
using namespace cv;
using namespace cv::face;


/*!
    \brief the meaning of this class is to create a list of coordinates from an image.
*/
class opencv : public QThread
{
    Q_OBJECT
public:

    /*!
     * \brief gets a regime where X means that we have first for that goes through X coordinate of the image then through Y coordinate, XY == result of the regime X +  result of the regime Y
     */
    enum Regime{
        XY,X,Y
    };

    /*!
    * \brief says how much points should we use to describe the line (two or many points)
    */
    enum ElemCountRegime{
        TWO_ELEM, ALL_ELEM
    };

    /*!
     * \brief the constructor that sets a default value
     */
    explicit opencv(QObject *parent = nullptr);


    /*!
    * \brief starts cam, if the takePortrait was pushed then sends resulted coordinates and an image, sends logs
    */
    void startopencv();

    /*!
    * \brief implemented algorithm to extract coordinates from Canny algorithm output
    * \param[in] imgCanny is a matrix with a Canny algorithm result, we need in it to extract lines from it
    * \param[in] counter1 shows us how many lines( coordinates) we have
    * \param[out] myfile file where we will write our coordinates
    * \param[out] mat is a matrix where resulted lines will be depicted
    * \param[in] regime is a current regime   X(first for is for x), Y(first for if for y), XY( sum of 2 previous results)
    */
    void fourForAlgorithm();


    /*!
    * \brief path to the folder with exe file
    */
    string& getAbsolutePath();

    /*!
     * \brief function that draws splines
     * \param[out] im resulted image
     * \param[in] vecX x points
     * \param[in] vecY z points
     * \param[in] isClosed whether spline is closed or not
     * \param[in] yOrX flip image
     *
     */
    void drawSplines(   Mat &im,
                        vector<double> &vecX,
                        vector<double> &vecY,
                        bool isClosed = false,
                        bool yOrX = false);

    /*!
     * \brief this method runs when a thread was started
     *
     */
    void run();

    /*!
    * \brief implemented algorithm to extract coordinates from Canny algorithm output
    * \param[in] imgCanny is a matrix with a Canny algorithm result, we need in it to extract lines from it
    * \param[in] counter1 shows us how many lines( coordinates) we have
    * \param[out] myfile file where we will write our coordinates
    * \param[out] mat is a matrix where resulted lines will be depicted
    * \param[in] regime is a current regime   X(first for is for x), Y(first for if for y), XY( sum of 2 previous results)
    */
    void fourForAlgorithm(cv::Mat &imgCanny, int &counter1, ofstream &myfile, cv::Mat &mat, Regime regime);

    /*!
    * \brief closes everything that can be closed, sends logs
    * \param[out] mat is a resulted image, it is sent to the mainwindow
    * \param[in] capWebcam videoCapture camera instance is close camera here
    * \param[in] counter1 here to send the number of lines describing the resulted image
    */
    void theendwork(cv::Mat const &mat, ofstream &myfile, cv::VideoCapture &capWebcam, int &counter1);

    /*!
    * \brief gets a flag telling whether an image was attached( it happens then a takePortrait button was pushed)
    */
    enum ImgAttached{
        IMG_ATTACHED, IMG_UNATTACHED
    };

signals:
    /*!
     * \brief sendQImg sends resulted image to the mainwindow
     */
    void sendQImg(QImage);
    /*!
     * \brief to delete this thread using built-in deleteLater method
     */
    void finished();
    /*!
     * \brief just sends logs to the mainwindow
     */
    void sendLog2(QString);

public slots:
    /*!
     * \brief if some push takePortrait == sendingFlag is true then an image will be sent to the MainWindow( here it will be displayed)
     */
    void getRequestForPortrait();

    /*!
     * \brief gets the top threshold for the Canny algorithm
     */
    void gettopborder(int);

    /*!
     * \brief gets the bottom threshold for the Canny algorithm
     */
    void getbottomborder(int);

    /*!
     * \brief gets a regime where X means that we have first for that goes through X coordinate of the image then through Y coordinate, XY == result of the regime X +  result of the regime Y
     */
    void getregime(int);

    /*!
     * \brief gets a regime where 0 is a set of straight lines, 1 is a set of curve lines
     */
    void getCurrentRegime(int);

    /*!
    * \brief gets a flag telling whether an image was attached( it happens then a takePortrait button was pushed)
    */
    void getAttachedImageFlag(int);
private:
    /*!
    * \brief path to the folder with exe file
    */
    string absolutePath = "";

    /*!
    * \brief param which says what you should send an image to the mainwindow
    */
    bool sendingFlag = false;
    /*!
    * \brief threshold parameter for Canny algorithm
    */
    int lowTh = 45;
    /*!
    * \brief threshold parameter for Canny algorithm
    */
    int highTh = 90;
    /*!
    * \brief current regime( X, Y, XY)
    */
    Regime current_regime = X;// 0 - XYRegime, 1 - XRegime, 2- YRegime;
    /*!
    * \brief says is image attached or not, otherwise use camera`s input
    */
    ImgAttached isimgattached = IMG_UNATTACHED;

    /*!
    * \brief says how much points should we use to describe the line (two or many points)
    */
    ElemCountRegime elemcountregime = TWO_ELEM; //0 = 2 el, 1 = full;

    /*!
    * \brief says us from how many cells will consist an image
    */
    int ij = 30;

    /*!
    * \brief says us from how many cells will consist an image
    */
    int xy = 16;
};

#endif // OPENCV_H
