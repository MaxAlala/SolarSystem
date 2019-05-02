#ifndef OPENCV_H
#define OPENCV_H

#include <QObject>
#include <QDebug>
#include <opencv2/face.hpp>
#include<opencv2/core/core.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <QThread>
using namespace std;
using namespace cv;
using namespace cv::face;

class opencv : public QThread
{
    Q_OBJECT
public:
    explicit opencv(QObject *parent = nullptr);
    void startopencv();
    void run();
    void drawSplines(   Mat &im,
                        vector<double> &vecX,
                        vector<double> &vecY,
                        bool isClosed = false,
                          bool yOrX = false);


signals:
    void sendImg(QString);
public slots:
};

#endif // OPENCV_H
