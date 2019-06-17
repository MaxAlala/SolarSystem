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

class opencv : public QThread
{
    Q_OBJECT
public:
    enum Regime{
        XY,X,Y
    };
    explicit opencv(QObject *parent = nullptr);
    void startopencv();
    void fourForAlgorithm();
    cv::Mat QImage2Mat(QImage const& src);
    void drawSplines(   Mat &im,
                        vector<double> &vecX,
                        vector<double> &vecY,
                        bool isClosed = false,
                        bool yOrX = false);
    void run();
    void fourForAlgorithm(cv::Mat &imgCanny, int &counter1, ofstream &myfile, cv::Mat &mat, Regime regime);
    void theendwork(cv::Mat const &mat, ofstream &myfile, cv::VideoCapture &capWebcam, int &counter1);
    string absolutePath = "";
    QImage qimg;
    QImage lena;
    enum ImgAttached{
       imgAttached, imgUnattached
    };

signals:
    void sendImg(QString);
    void sendQImg(QImage);
    void finished();
    void error(QString err);
    void sendPortrait(QImage);
    void sendLog2(QString);

public slots:
    void getRequestForPortrait();
    void getFlagON();
    void gettopborder(int);
    void getbottomborder(int);
    void getregime(int);
    void getijxy(int,int);
    void getcurrentX(int);
    void getlenaattach(int);
private:
    //    string absolutePath = "C:/Users/X/Desktop/ws/opencv/KUKA-face-picturing/qt_opencv_server_kuka_app/";
    bool sendingFlag = false;
    bool flagON = false;
    int currentXfullor2el = 0; //0 = 2 el, 1 = full;
    int lowTh = 45;
    int highTh = 90;
    Regime current_regime;// 0 - XYRegime, 1 - XRegime, 2- YRegime;
    ImgAttached isimgattached;
    int ij = 30;
    int xy = 16;
};

#endif // OPENCV_H
