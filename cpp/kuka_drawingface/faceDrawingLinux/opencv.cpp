 #include "opencv.h"
#include "spline.h"
//start = 300 lines


/*!
 * \brief function that draws splines
 * \param[out] im resulted image
 * \param[in] vecX x points
 * \param[in] vecY z points
 * \param[in] isClosed whether spline is closed or not
 * \param[in] yOrX flip image
 *
 */
void opencv::drawSplines
(
        cv::Mat &im,
        vector<double> &vecX,
        vector<double> &vecY,
        bool isClosed,
        bool yOrX
        )
{
    tk::spline s; ///< spline instance
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

/*!
 * \brief the constructor that sets a default value
 *
 */
opencv::opencv(QObject *parent)
{
    isimgattached = IMG_UNATTACHED;
}

/*!
 * \brief this method runs when a thread was started
 *
 */
void opencv::run(){
    startopencv();
    //    exec();
}

string& opencv::getAbsolutePath(){
    return absolutePath;
}

/*!
 * \brief if some push takePortrait == sendingFlag is true then an image will sent to the MainWindow( where it will be displayed)
 */
void opencv::getRequestForPortrait(){
    sendingFlag = true;
}

/*!
 * \brief gets the top threshold for the Canny algorithm
 */
void opencv::gettopborder(int x){
    highTh = x;
}

/*!
 * \brief gets the bottom threshold for the Canny algorithm
 */

void opencv::getbottomborder(int x){
    lowTh = x;
}

/*!
 * \brief gets a regime where X means that we have first for that goes through X coordinate of the image then through Y coordinate, XY == result of the regime X +  result of the regime Y
 */
void opencv::getregime(int x){
    switch (x) {
    case 0: current_regime = XY; break;
    case 1: current_regime = X; break;
    case 2: current_regime = Y; break;
    }
}
/*!
 * \brief gets a regime where 0 is a set of straight lines, 1 is a set of curve lines
 */
void opencv::getCurrentRegime(int curX){ // 0 or 1
     qDebug() << "getCurrentRegime! " << curX;
    switch(curX){

    case 0:elemcountregime = TWO_ELEM; break;
    case 1:elemcountregime = ALL_ELEM; break;
    }
};

/*!
* \brief gets a flag telling whether an image was attached( it happens then a takePortrait button was pushed)
*/
void opencv::getAttachedImageFlag(int x){
    switch (x) {
    case 0: isimgattached = IMG_UNATTACHED; break;
    case 1: isimgattached = IMG_ATTACHED; break;
    }
}

/*!
* \brief starts cam, if the takePortrait was pushed then sends resulted coordinates and an image, sends logs
*/

void opencv::startopencv(){
    cv::Mat imgOriginal = cv::imread(absolutePath + "image.jpg");       // input image
    cv::Mat imgGrayscale;       // grayscale image
    cv::Mat imgBlurred;         // blured image
    cv::Mat imgCanny;
    cv::Mat buf;
    cv::Mat mat = cv::Mat::zeros(imgOriginal.size(), CV_8UC1);
    ofstream myfile;

        cv::VideoCapture capWebcam(0);
        if (capWebcam.isOpened() == false)  //  To check if object was associated to webcam successfully
        {
            std::cout << "error: Webcam connect unsuccessful\n"; // if not then print an error message
            return;            // and exit program
        }

        while (capWebcam.isOpened()) {
            if(isimgattached == IMG_UNATTACHED){ // read from webcam

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

            }else if (isimgattached == IMG_ATTACHED) { // read an image from the folder
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
        int counter1 = 0; // common counter to label id of lines

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

//    }
}

/*!
* \brief closes everything that can be closed, sends logs
* \param[out] mat is a resulted image, it is sent to the mainwindow
* \param[in] capWebcam videoCapture camera instance is close camera here
* \param[in] counter1 here to send the number of lines describing the resulted image
*/
void opencv::theendwork(cv::Mat const &mat, ofstream &myfile, cv::VideoCapture &capWebcam, int &counter1){
    sendingFlag = false;
    imwrite(absolutePath + "saved.png", mat);
    QImage qimg2((uchar*)mat.data,mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
    sendQImg(qimg2);
    myfile.close();
    capWebcam.release();
    QString s = QString::number(counter1);
    emit(sendLog2("Number of currentX: " + s));
    cout << counter1 << " COUNTER1!" << endl;
}

/*!
* \brief implemented algorithm to extract coordinates from Canny algorithm output. To better understand this algorithm you can read the corresponding paper. It is the simplest algorithm.
* \param[in] imgCanny is a matrix with a Canny algorithm result, we need in it to extract lines from it
* \param[in] counter1 shows us how many lines( coordinates) we have
* \param[out] myfile file where we will write our coordinates
* \param[out] mat is a matrix where resulted lines will be depicted
* \param[in] regime is a current regime   X(first for is for x), Y(first for if for y), XY( sum of 2 previous results)
*/
void opencv::fourForAlgorithm(cv::Mat &imgCanny, int &counter1, ofstream &myfile, cv::Mat &mat, Regime regime){
    for (int i = 0; i <ij; i++) // divides the pictures into cells
        for (int j = 0; j < ij; j++) // divides the pictures into cells
        {
            cv::Point y2;
            vector<cv::Point> curSixX;
            // 2 fors go through one current cell
            for (int x = i * xy; x < (i + 1) * xy; x++) {
                for (int y = j * xy; y < (j + 1) * xy; y++) {
                    int firstAxis;
                    int secondAxis;
                    if(regime == X){ // first axis means that first 'for ' goes through X or Y
                        firstAxis = x;
                        secondAxis = y;
                    }else {
                        firstAxis = y;
                        secondAxis = x;
                    }

                    if(imgCanny.at<uchar>(firstAxis, secondAxis) > 0) { // if pixel is not equal to 0 then put the max intensity value == max black.
                        imgCanny.at<uchar>(firstAxis, secondAxis) = 255;
                        y2 = cv::Point(firstAxis, secondAxis);
                    }
                }
                if (y2.x == 0 && y2.y == 0) {} // leaves a first pixel. First pixel is a buffer for bad pixels.
                else {
                    curSixX.push_back(y2); // put a satisfying pixel in a vector
                }
                y2.x = 0;
                y2.y = 0;
            }
            qDebug() << curSixX.size() << "\n";
            vector<double> curVecX;
            vector<double> curVecY;
            int scale = 3;
            if( elemcountregime == TWO_ELEM){ // describe line only with two points, put all lines into the file, draw a line on an image.
                qDebug() << "here1";
                if (curSixX.size() != 0 && curSixX.size() > 0&& curSixX.at(0).x != curSixX.at(curSixX.size()-1).x ) {
                    if(curSixX.at(0).x/5.0 < 5.0 ||curSixX.at(0).y/5.0 < 5.0 || curSixX.at(curSixX.size() - 1).x/5.0 < 5.0 || curSixX.at(curSixX.size() - 1).y/5.0 < 5.0){}else{
                        counter1++;
                        myfile <<counter1<< " "<< curSixX.at(0).x/2.5 << " " << curSixX.at(0).y/2.5 << "\n";

                        myfile <<counter1<< " "<<curSixX.at(curSixX.size() - 1).x/2.5 << " " << curSixX.at(curSixX.size() - 1).y/2.5<< "\n";
                        curVecX.push_back(curSixX.at(0).x);
                        curVecY.push_back(curSixX.at(0).y);
                        curVecX.push_back(curSixX.at(curSixX.size()-1).x);
                        curVecY.push_back(curSixX.at(curSixX.size()-1).y);
                        if(regime == Y){drawSplines(mat,curVecY, curVecX, false, false); // draw line with right orientation
                        }else{
                            drawSplines(mat,curVecX, curVecY, false, true);
                        }
                    }
                }
            }else if (elemcountregime == ALL_ELEM){// describe line using all points from curSixX, put all lines into the file, draw a line in an image.
                qDebug() << "here2";
                if (curSixX.size() > 10 ) { // must be at least 5 elements
                    int lessThan = 5;
                    if(curSixX.at(0).x/scale < 5.0 ||curSixX.at(0).y/scale < 5.0 || curSixX.at(curSixX.size() - 1).x/scale< 5.0 || curSixX.at(curSixX.size() - 1).y/scale < 5.0){}else{

                    counter1++;

                    int numberOfPoints = 9;
                    for(uint a = 0; a <= numberOfPoints; a++){

                        if(a == numberOfPoints)
                        {
                            if(curSixX.at(curSixX.size() * a/numberOfPoints - 1).x/scale == 0 )curSixX.at(curSixX.size() * a/numberOfPoints - 1).x = 10;
                            if(curSixX.at(curSixX.size() * a/numberOfPoints - 1).y/scale == 0 )curSixX.at(curSixX.size() * a/numberOfPoints - 1).y = 10;
                            myfile <<counter1<< " " << (curSixX.at(curSixX.size() * a/numberOfPoints - 1).x+50)/scale << " " << curSixX.at(curSixX.size() * a/numberOfPoints - 1).y/scale <<"\n";
                            curVecX.push_back(curSixX.at(curSixX.size() * a/numberOfPoints -1).x);
                            curVecY.push_back(curSixX.at(curSixX.size() * a/numberOfPoints -1).y);
                        } else {

                            if(curSixX.at(curSixX.size() * a/numberOfPoints ).x/scale == 0 )curSixX.at(curSixX.size() * a/numberOfPoints ).x = 10;
                            if(curSixX.at(curSixX.size() * a/numberOfPoints ).y/scale == 0 )curSixX.at(curSixX.size() * a/numberOfPoints ).y = 10;

                            myfile <<counter1<< " "<< (curSixX.at(curSixX.size() * a/numberOfPoints).x+50)/scale << " " << curSixX.at(curSixX.size() * a/numberOfPoints).y/scale <<"\n";

                            curVecX.push_back(curSixX.at(curSixX.size() * a/numberOfPoints).x);
                            curVecY.push_back(curSixX.at(curSixX.size() * a/numberOfPoints).y);
                        }
                    }
                    if(regime == Y){drawSplines(mat,curVecY, curVecX, false, false);
                    }else{
                        drawSplines(mat,curVecX, curVecY, false, true);
                    }
                }
              }
            }
        }
}
