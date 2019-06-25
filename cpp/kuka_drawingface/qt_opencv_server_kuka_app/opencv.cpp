#include "opencv.h"
#include "spline.h"
//start = 300 lines

void opencv::drawSplines
(
        cv::Mat &im,
        vector<double> &vecX,
        vector<double> &vecY,
        bool isClosed,
        bool yOrX
        )
{
    tk::spline s;
    s.set_points(vecX, vecY);
    double beg = vecX.at(0);
    double en = vecX.at(vecX.size() - 1);
    double dif = en - beg;
    double step_size = 0.05;
    //    int step_number = dif/step_size ;
    double cur_y = 0;
    while (beg < en) {
        beg += step_size;
        cur_y = s(beg);
        if(yOrX == false)
            circle(im, cv::Point(beg, cur_y), 0.5, cv::Scalar(255, 200, 0), 1, 8);
        else circle(im, cv::Point( cur_y, beg), 0.5, cv::Scalar(255, 200, 0), 1, 8);
    }
}

opencv::opencv(QObject *parent)
{
    isimgattached = IMG_UNATTACHED;
}

void opencv::run(){
    startopencv();
    //    exec();
}

string& opencv::getAbsolutePath(){
    return absolutePath;
}

void opencv::getRequestForPortrait(){
    sendingFlag = true;
}

void opencv::getFlagON(){
    flagON = true;
}

void opencv::gettopborder(int x){
    highTh = x;
}

void opencv::getbottomborder(int x){
    lowTh = x;
}

void opencv::getregime(int x){
    switch (x) {
    case 0: current_regime = XY; break;
    case 1: current_regime = X; break;
    case 2: current_regime = Y; break;
    }
}

void opencv::getijxy(int ij,int xy){ // always are same
    this->xy = xy;
    this->ij = ij;
};

void opencv::getcurrentX(int curX){ // 0 or 1
    switch(curX){
    case 0:elemcountregime = TWO_ELEM; break;
    case 1:elemcountregime = ALL_ELEM; break;
    }
};

void opencv::getlenaattach(int x){
    switch (x) {
    case 0: isimgattached = IMG_UNATTACHED; break;
    case 1: isimgattached = IMG_ATTACHED; break;
    }
}

cv::Mat opencv::QImage2Mat(QImage const& src)
{
    cv::Mat tmp(src.height(), src.width(), CV_8UC3, (uchar*)src.bits(), src.bytesPerLine());
    cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
    cvtColor(tmp, result, CV_BGR2RGB);
    return result;
}

void opencv::startopencv(){
    cv::Mat imgOriginal = cv::imread(absolutePath + "image.jpg");       // input image
    cv::Mat imgGrayscale;       // grayscale image
    cv::Mat imgBlurred;         // blured image
    cv::Mat imgCanny;
    cv::Mat buf;
    cv::Mat mat = cv::Mat::zeros(imgOriginal.size(), CV_8UC1);
    ofstream myfile;

    if(flagON == true){
        cv::Mat imgOriginal=cv::imread(absolutePath + "image.jpg");       // input image;
        cv::VideoCapture capWebcam(0);
        if (capWebcam.isOpened() == false)  //  To check if object was associated to webcam successfully
        {
            std::cout << "error: Webcam connect unsuccessful\n"; // if not then print an error message
            return;            // and exit program
        }

        while (capWebcam.isOpened()) {

            if(isimgattached == IMG_UNATTACHED){

                imgOriginal = cv::imread(absolutePath + "image.jpg");       // input image
                bool blnFrameReadSuccessfully = capWebcam.read(buf);
                resize(buf, imgOriginal, Size(512, 512), 0, 0, INTER_CUBIC);
                imgGrayscale = cv::Mat::zeros(imgOriginal.size(), CV_8UC1);
                imgBlurred = cv::Mat::zeros(imgOriginal.size(), CV_8UC1);
                imgCanny = cv::Mat::zeros(imgOriginal.size(), CV_8UC1);
                mat = cv::Mat::zeros(imgOriginal.size(), CV_8UC1);

                if (!blnFrameReadSuccessfully || imgOriginal.empty()) {    // if frame read unsuccessfully
                    std::cout << "error: frame can't read \n";      // print error message
                    break;
                }

            }else if (isimgattached == IMG_ATTACHED) {
                imgOriginal = cv::imread(absolutePath+"image.jpg");       // input image
                mat = cv::Mat::zeros(imgOriginal.size(), CV_8UC1);
                imgGrayscale = cv::Mat::zeros(imgOriginal.size(), CV_8UC1);
                imgBlurred = cv::Mat::zeros(imgOriginal.size(), CV_8UC1);
                imgCanny = cv::Mat::zeros(imgOriginal.size(), CV_8UC1);
            }

            cv::cvtColor(imgOriginal, imgGrayscale, COLOR_BGR2GRAY);                   // convert to grayscale
            cv::GaussianBlur(imgGrayscale, imgBlurred, cv::Size(5, 5), 1.8);           // Blur Effect
            cv::Canny(imgBlurred, imgCanny, lowTh, highTh);       // Canny Edge Image
            QImage qimg2((uchar*)imgCanny.data, imgCanny.cols, imgCanny.rows, imgCanny.step, QImage::Format_Grayscale8);
            sendQImg(qimg2);

            if (sendingFlag == true) {
                break;
            }

        }

        if( elemcountregime == TWO_ELEM){
            myfile.open(absolutePath + "points.txt");
        }else {
            myfile.open(absolutePath+"pointsFull.txt");
        }
        int counter1 = 0;

        switch(current_regime){
        case X:
            fourForAlgorithm(imgCanny, counter1, myfile, mat, X);
            break;
        case Y:
            fourForAlgorithm(imgCanny, counter1, myfile, mat, Y);
            break;
        case XY:
            fourForAlgorithm(imgCanny, counter1, myfile, mat, X);
            fourForAlgorithm(imgCanny, counter1, myfile, mat, Y);
            break;
        }
        theendwork(mat, myfile, capWebcam, counter1);

    }
}

void opencv::theendwork(cv::Mat const &mat, ofstream &myfile, cv::VideoCapture &capWebcam, int &counter1){
    //    qDebug()<< "hello!Max";
    sendingFlag = false;
    flagON = false;
    imwrite(absolutePath + "saved.png", mat);
    QImage qimg2((uchar*)mat.data,mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
    sendQImg(qimg2);
    myfile.close();
    capWebcam.release();
    QString s = QString::number(counter1);
    emit(sendLog2("Number of currentX: " + s));
    cout << counter1 << " COUNTER1!" << endl;
}

void opencv::fourForAlgorithm(cv::Mat &imgCanny, int &counter1, ofstream &myfile, cv::Mat &mat, Regime regime){
    for (int i = 0; i <ij; i++)
        for (int j = 0; j < ij; j++)
        {
            cv::Point y2;
            vector<cv::Point> curSixX;

            for (int x = i * xy; x < (i + 1) * xy; x++) {
                for (int y = j * xy; y < (j + 1) * xy; y++) {
                    int firstAxis;
                    int secondAxis;
                    if(regime == X){
                        firstAxis = x;
                        secondAxis = y;
                    }else {
                        firstAxis = y;
                        secondAxis = x;
                    }

                    if(imgCanny.at<uchar>(firstAxis, secondAxis) > 0) {
                        imgCanny.at<uchar>(firstAxis, secondAxis) = 255;
                        y2 = cv::Point(firstAxis, secondAxis);
                    }else{
                        imgCanny.at<uchar>(firstAxis, secondAxis) = 0;
                    }
                }

                if (y2.x == 0 && y2.y == 0) {}
                else {
                    curSixX.push_back(y2);
                }
                y2.x = 0;
                y2.y = 0;
            }
            vector<double> curVecX;
            vector<double> curVecY;

            if( elemcountregime == TWO_ELEM){
                if (curSixX.size() != 0 && curSixX.size() > 0&& curSixX.at(0).x != curSixX.at(curSixX.size()-1).x ) {
                    if(curSixX.at(0).x/5.0 < 5.0 ||curSixX.at(0).y/5.0 < 5.0 || curSixX.at(curSixX.size() - 1).x/5.0 < 5.0 || curSixX.at(curSixX.size() - 1).y/5.0 < 5.0){}else{
                        counter1++;
                        myfile <<counter1<< " "<< curSixX.at(0).x/2.5 << " " << curSixX.at(0).y/2.5 << "&" << curSixX.at(curSixX.size() - 1).x/2.5 << " " << curSixX.at(curSixX.size() - 1).y/2.5 << "\n";
                        curVecX.push_back(curSixX.at(0).x);
                        curVecY.push_back(curSixX.at(0).y);
                        curVecX.push_back(curSixX.at(curSixX.size()-1).x);
                        curVecY.push_back(curSixX.at(curSixX.size()-1).y);
                        if(regime == Y){drawSplines(mat,curVecY, curVecX, false, false);
                        }else{
                            drawSplines(mat,curVecX, curVecY, false, true);
                        }
                    }
                }
            }else if (elemcountregime == ALL_ELEM){
                if (curSixX.size()>4) {
                    counter1++;
                    myfile << "start"<<"\n";
                    for(uint a = 0; a < curSixX.size(); a++){
                        myfile <<counter1<< " "<< curSixX.at(a).x/2.5 << " " << curSixX.at(a).y/2.5<<"\n";
                        curVecX.push_back(curSixX.at(a).x);
                        curVecY.push_back(curSixX.at(a).y);
                    }

                    myfile << "end"<<"\n";

                    if(regime == Y){drawSplines(mat,curVecY, curVecX, false, false);
                    }else{
                        drawSplines(mat,curVecX, curVecY, false, true);
                    }
                }
            }
        }
}
