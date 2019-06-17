// TesterCv.cpp: определяет точку входа для консольного приложения.
//

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include "spline.h"
using namespace std;
#include <opencv2/face.hpp>
#include<opencv2/core/core.hpp>
#include <WS2tcpip.h>
#include <string>
#include <thread>
#include <chrono>
#include <windows.h>
#include <stdlib.h>
#pragma comment (lib, "ws2_32.lib")
#pragma warning(disable: 4996)
using namespace cv::face;



void drawSplines
(
        cv::Mat &im,
        vector<double> &vecX,
        vector<double> &vecY,
        bool isClosed = false,
        bool yOrX = false
        )
{
    // Gather all points between the start and end indices
    //vector <Point> points;


    tk::spline s;
    s.set_points(vecX, vecY);
    double beg = vecX.at(0);
    double en = vecX.at(vecX.size() - 1);
    //cout << beg << " beg and end " << en << endl;
    double dif = en - beg;
    double step_size = 0.05;
    int step_number = dif/step_size ;
    double cur_y = 0;

    //}
    while (beg < en) {
        beg += step_size;
        cur_y = s(beg);
        if(yOrX == false)
            circle(im, cv::Point(beg, cur_y), 0.5, cv::Scalar(255, 200, 0), 1, 8);
        else circle(im, cv::Point( cur_y, beg), 0.5, cv::Scalar(255, 200, 0), 1, 8);
    }
}

void createServer(int id);
int main(int argc, char *argv[] )
{
    //std:thread th1(createServer, 1);

    ofstream myfile;
    myfile.open("C:\\Users\\X\\Desktop\\ws\\qt_w\\testerCpp\\points.txt");


    cv::Mat frame, gray;
    cv::CascadeClassifier faceDetector("C:\\Users\\X\\Desktop\\ws\\qt_w\\testerCpp\\haarcascade_frontalface_alt2.xml");
    cv::Mat imgOriginal = cv::imread("C:\\Users\\X\\Desktop\\ws\\qt_w\\testerCpp\\lena.jpg");;        // input image
    cv::Mat imgGrayscale;       // grayscale image
    cv::Mat imgBlurred;         // blured image
    cv::Mat imgCanny;           // Canny edge image
    char charCheckForEscKey = 0;
    cv::Mat mat = cv::Mat::zeros(imgOriginal.size(), CV_8UC1);
    int lowTh = 45;
    int highTh = 90;
    // Find face
    vector<cv::Rect> faces;
    cvtColor(imgOriginal, gray, cv::COLOR_BGR2GRAY);
    faceDetector.detectMultiScale(gray, faces);

    cout << imgOriginal.size() << endl;
    double scale = 1;


    cv::cvtColor(imgOriginal, imgGrayscale, cv::COLOR_BGR2GRAY);                   // convert to grayscale
    imwrite( "C:\\Users\\X\\Desktop\\ws\\qt_w\\testerCpp\\grayscaled.jpg", imgGrayscale );

    cv::GaussianBlur(imgGrayscale, imgBlurred, cv::Size(5, 5), 1.8);           // Blur Effect
    //cout << imgGrayscale.size();

    imwrite( "C:\\Users\\X\\Desktop\\ws\\qt_w\\testerCpp\\blurred.jpg", imgBlurred );
    cv::Canny(imgBlurred, imgCanny, lowTh, highTh);       // Canny Edge Image

    imwrite( "C:\\Users\\X\\Desktop\\ws\\qt_w\\testerCpp\\canny.jpg", imgCanny );

    int c;


    //    vector<vector<cv::Point>> allSplines;
    int counter1 = 0;
    //    for (int i = 0; i <30; i++)
    //        for (int j = 0; j < 30; j++)
    //        {
    //            //cout << j;
    //            cv::Point y2;
    //            vector<cv::Point> curSixX;
    //            //cout << curSixX.size() << " sizeC";S
    //            for (int y = i * 16; y < (i + 1) * 16; y++) {
    //                for (int x = j * 16; x < (j + 1) *16; x++) {

    //                    if (imgCanny.at<uchar>(x, y) > 0) {
    //                        imgCanny.at<uchar>(x, y) = 255;
    //                        y2 = cv::Point(x, y);
    //                    }

    //                    else {
    //                        imgCanny.at<uchar>(x, y) = 0;
    //                    }

    //                }
    //                if (y2.x == 0 && y2.y == 0) {}
    //                else {
    //                    curSixX.push_back(y2);
    //                }
    //            }

    //            vector<double> curVecX;
    //            vector<double> curVecY;

    //            if (curSixX.size() != 0 && curSixX.size() > 0&& curSixX.at(0).x != curSixX.at(curSixX.size()-1).x) {

    //                counter1++;
    //                myfile <<counter1<< " "<< (double)curSixX.at(0).x/5.0 << " " << (double)curSixX.at(0).y/5.0 << "&" << (double)curSixX.at(curSixX.size() - 1).x/5.0 << " " << (double)curSixX.at(curSixX.size() - 1).y/5.0 << "\n";

    //                curVecX.push_back(curSixX.at(0).x);
    //                curVecY.push_back(curSixX.at(0).y);
    //                curVecX.push_back(curSixX.at(curSixX.size() - 1).x);
    //                curVecY.push_back(curSixX.at(curSixX.size() - 1).y);

    //                allSplines.push_back(curSixX);
    //                drawSplines(mat, curVecY, curVecX, false);


    //            }
    //            else {}

    //        }
//    for (int i = 0; i <8; i++)
//        for (int j = 0; j < 8; j++)
//        {
//            cv::Point y2;
//            vector<cv::Point> currentX;
//            for (int x = i * 64; x < (i + 1) * 64; x++) {
//                for (int y = j * 64; y < (j + 1) * 64; y++) {
//    for (int i = 0; i <50; i++)
//        for (int j = 0; j < 50; j++)
//        {
//            cv::Point y2 = {999,999};
//            vector<cv::Point> currentX;
//            for (int x = i * 10; x < (i + 1) * 10; x++) {
//                for (int y = j * 10; y < (j + 1) * 10; y++) {

//                    if (imgCanny.at<uchar>(x, y) > 0) {
//                        imgCanny.at<uchar>(x, y) = 255;
//                        y2 = cv::Point(x, y);
//                    }

//                    else {
//                        imgCanny.at<uchar>(x, y) = 0;
//                    }

//                }
//                if (y2.x == 999 || y2.y == 999) {}
//                else {
//                    currentX.push_back(y2);
//                }
//                y2.x = 999;
//                y2.y = 999;
//            }

//            vector<double> curVecX;
//            vector<double> curVecY;

//            if (currentX.size() >4) {
//                cout << currentX.size()<< " size";
//                counter1++;
//                myfile << counter1<< " " << currentX.at(0).x/5 << " " << currentX.at(0).y/5 << "&"<< currentX.at(currentX.size() - 1).x/5 << " " << currentX.at(currentX.size() - 1).y/5 << "\n";
//                for(int z = 0; z < currentX.size(); z++){
//                    curVecX.push_back(currentX.at(z).x);
//                    curVecY.push_back(currentX.at(z).y);
//                    //                curVecX.push_back(curSixX.at(curSixX.size()-1).x);
//                    //                curVecY.push_back(curSixX.at(curSixX.size()-1).y);
//                }
//                cout << "begin: "<< endl;
//                for(int a = 0; a < curVecX.size() ; a++ ){
//                    cout << curVecX.at(a) << endl;
//                }
//                cout << "end: "<< endl;
//                //                allSplines.push_back(curSixX);
//                drawSplines(mat,curVecX, curVecY, false, true);
//            }
//            else {}

//        }

    for (int i = 0; i <50; i++)
        for (int j = 0; j < 50; j++)
        {
            cv::Point y2 = {999,999};
            vector<cv::Point> currentX;
            for (int y = i * 10; y < (i + 1) * 10; y++) {
                for (int x = j * 10; x < (j + 1) * 10; x++) {

                    if (imgCanny.at<uchar>(x, y) > 0) {
                        imgCanny.at<uchar>(x, y) = 255;
                        y2 = cv::Point(x, y);
                    }

                    else {
                        imgCanny.at<uchar>(x, y) = 0;
                    }

                }
                if (y2.x == 999 || y2.y == 999) {}
                else {
                    currentX.push_back(y2);
                }
                y2.x = 999;
                y2.y = 999;
            }

            vector<double> curVecX;
            vector<double> curVecY;

            if (currentX.size() >4) {
                cout << currentX.size()<< " size";
                counter1++;
                myfile << counter1<< " " << currentX.at(0).x/5 << " " << currentX.at(0).y/5 << "&"<< currentX.at(currentX.size() - 1).x/5 << " " << currentX.at(currentX.size() - 1).y/5 << "\n";
                for(int z = 0; z < currentX.size(); z++){
                    curVecX.push_back(currentX.at(z).x);
                    curVecY.push_back(currentX.at(z).y);
                    //                curVecX.push_back(curSixX.at(curSixX.size()-1).x);
                    //                curVecY.push_back(curSixX.at(curSixX.size()-1).y);
                }
                cout << "begin: "<< endl;
                for(int a = 0; a < curVecX.size() ; a++ ){
                    cout << curVecX.at(a) << endl;
                }
                cout << "end: "<< endl;
                //                allSplines.push_back(curSixX);
                drawSplines(mat,curVecY, curVecX, false, false);
            }
            else {}

        }
    cout << counter1 << " COUNTER1!" << endl;
    imwrite( "C:\\Users\\X\\Desktop\\ws\\qt_w\\testerCpp\\result.jpg", mat );

    imshow("splines", imgCanny);
    imshow("origin", imgOriginal);
    imshow("origin", mat);

    cv::waitKey(0);
    return 0;
}


