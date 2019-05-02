#include "opencv.h"
#include "spline.h"

void opencv::drawSplines
(
    cv::Mat &im,
    vector<double> &vecX,
    vector<double> &vecY,
    bool isClosed ,
    bool yOrX
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
    //cout << step_number << " steps " << endl;

    double cur_y = 0;
    //	double cur_x = beg + i *0.5;
    //for (int i = 0; i < step_number*2; i++) {
    //	cur_y = s(cur_x);
    //	//cout << cur_x << " cur x and y " << cur_y << endl;
    //	//im.at<uchar>(cur_x, cur_y) = 255;
    //	/*	vecX.push_back(cur_x);
    //	vecY.push_back(cur_y);*/
    //	circle(im, Point(cur_y, cur_x), 1, Scalar(255, 200, 0), 1, 8);

    //}
    while (beg < en) {
        beg += step_size;
        cur_y = s(beg);
        if(yOrX == false)
        circle(im, cv::Point(beg, cur_y), 0.5, cv::Scalar(255, 200, 0), 1, 8);
        else circle(im, cv::Point( cur_y, beg), 0.5, cv::Scalar(255, 200, 0), 1, 8);

    }
}
opencv::opencv(QObject *parent) : QThread (parent)
{

}
void opencv::run(){
    startopencv();
}
void opencv::startopencv(){

    ofstream myfile;
       myfile.open("C:\\Users\\X\\Desktop\\ws\\opencv\\KUKA-face-picturing\\qt_opencv_server_kuka_app\\points.txt");

       cv::Mat frame, gray;
       cv::CascadeClassifier faceDetector("C:\\Users\\X\\Desktop\\ws\\opencv\\KUKA-face-picturing\\qt_opencv_server_kuka_app\\haarcascade_frontalface_alt2.xml");
       cv::Mat imgOriginal = cv::imread("C:\\Users\\X\\Desktop\\ws\\opencv\\KUKA-face-picturing\\qt_opencv_server_kuka_app\\lena.jpg");       // input image
       cv::Mat imgGrayscale;       // grayscale image
       cv::Mat imgBlurred;         // blured image
       cv::Mat imgCanny;           // Canny edge image
       char charCheckForEscKey = 0;
       cv::Mat mat = cv::Mat::zeros(imgOriginal.size(), CV_8UC1);
       int lowTh = 45;
       int highTh = 45;
       // Find face
       vector<cv::Rect> faces;
       cvtColor(imgOriginal, gray, cv::COLOR_BGR2GRAY);
       faceDetector.detectMultiScale(gray, faces);

       cout << imgOriginal.size() << endl;




       //////////////////////////////////

        cv::VideoCapture capWebcam(0);
        if (capWebcam.isOpened() == false)  //  To check if object was associated to webcam successfully
            {
                std::cout << "error: Webcam connect unsuccessful\n"; // if not then print error message
                return;            // and exit program
            }


        while (charCheckForEscKey != 27 && capWebcam.isOpened() && charCheckForEscKey != 13) {            // until the Esc key is pressed or webcam connection is lost
               bool blnFrameReadSuccessfully = capWebcam.read(imgOriginal);   // get next frame

                                                             // Find face
               vector<Rect> faces;
               cvtColor(imgOriginal, gray, COLOR_BGR2GRAY);
               faceDetector.detectMultiScale(gray, faces);

               if (!blnFrameReadSuccessfully || imgOriginal.empty()) {    // if frame read unsuccessfully
                   std::cout << "error: frame can't read \n";      // print error message
                   break;
               }

               cv::cvtColor(imgOriginal, imgGrayscale, COLOR_BGR2GRAY);                   // convert to grayscale

               cv::GaussianBlur(imgGrayscale, imgBlurred, cv::Size(5, 5), 1.8);           // Blur Effect
               cv::Canny(imgBlurred, imgCanny, lowTh, highTh);       // Canny Edge Image

//               for (size_t i = 0; i < faces.size(); i++) // rectangles
//               {
//                   Rect r = faces[i];
//                   Scalar color = Scalar(255, 0, 0);

//                   rectangle(imgCanny, Point(cvRound((r.x-30)*scale), cvRound((r.y-70)*scale)), Point(cvRound((r.x +
//                       (r.width + 50) - 1)*scale), cvRound((r.y + (r.width + 50) - 1)*scale)), color, 3, 8, 0);
//               }

//               cv::namedWindow("imgOriginal", WINDOW_NORMAL);
                     cv::namedWindow("imgCanny", WINDOW_NORMAL);
                     //declare trackbar
//                     cv::createTrackbar("LowTh", "imgCanny", &lowTh, 100);


//                     cv::createTrackbar("HighTh", "imgCanny", &highTh, 100);
                     // show windows
//                     cv::imshow("imgOriginal", imgOriginal);
                     cv::imshow("imgCanny", imgCanny);


                     int c;
                     c = waitKey(5);
                     // Exit loop if ESC is pressed
                     if (c == 27) {
                         break;
                     }

                     if (c == 13) {

                         //cv::Mat mat(frame.size(), CV_8UC1, cv::Scalar(255, 0, 255));
//                         Mat cropedImage = imgCanny(Rect(faces[0].x, faces[0].y, faces[0].width + 50, faces[0].height + 50));
//                         Mat cropedImage = imgCanny;
//                          mat = Mat::zeros(cropedImage.size(), CV_8UC1);

                        break;
               }
        }


       ///////////////////////////////////////////////////////////////// Cesiar algorithm
       //cout << "M = " << endl << " " << imgGrayscale << endl << endl;


       int counter1 = 0;
       for (int i = 0; i <30; i++)
           for (int j = 0; j < 30; j++)
           {
               //cout << j;
               cv::Point y2;
               vector<cv::Point> curSixX;
               //cout << curSixX.size() << " sizeC";S
               for (int y = i * 16; y < (i + 1) * 16; y++) {
                   for (int x = j * 16; x < (j + 1) *16; x++) {

                       //cout << counter << endl;
                       //cout << curSixY.size() << " size curY." << endl;
                       //cout << imgGrayscale.at<uchar>(x, y) << " size coor. " << x << " " << y << endl;

                       if (imgCanny.at<uchar>(x, y) > 0) {
                           imgCanny.at<uchar>(x, y) = 255;
                           //cout << curSixY.at(0) << " curY1";
                           y2 = cv::Point(x, y);
                       }

                       else {
                           imgCanny.at<uchar>(x, y) = 0;
                       }

                   }
                   if (y2.x == 0 && y2.y == 0) {}
                   else {
                       //cout << curSixY.at(0) << " curY" << endl;
                       curSixX.push_back(y2);
                   }
                   //cout << "i here";
               }
               //for (int i = 0; i <= curSixX.size(); i++) {
               //	//cout << curSixX.at(i);
               //}
               //cout << "i here2";
               //cout << curSixX.size();
               vector<double> curVecX;
               vector<double> curVecY;

               //cout << curSixX.size() << endl;

               if (curSixX.size() != 0 && curSixX.size() > 5  && curSixX.at(0).y != curSixX.at(curSixX.size() - 1).y) {
   // cout << curSixX.size() << endl;
                   //vector<Point> n;
                   //for (int i = 0; i < curSixX.size(); i++) {
                   /*	n.at(i).x = curSixX.at(i).x;
                       n.at(i).y = curSixX.at(i).y;


   */
                   if((double)curSixX.at(0).x/5.0 < 5.0 ||(double)curSixX.at(0).y/5.0 < 5.0 || (double)curSixX.at(curSixX.size() - 1).x/5.0 < 5.0 || (double)curSixX.at(curSixX.size() - 1).y/5.0 < 5.0){}else{

                       counter1++;
                       myfile <<counter1<< " "<< (double)curSixX.at(0).x/5.0 << " " << (double)curSixX.at(0).y/5.0 << "&" << (double)curSixX.at(curSixX.size() - 1).x/5.0 << " " << (double)curSixX.at(curSixX.size() - 1).y/5.0 << "\n";
                       curVecX.push_back(curSixX.at(0).x);
                       curVecY.push_back(curSixX.at(0).y);
                       curVecX.push_back(curSixX.at(curSixX.size() - 1).x);
                       curVecY.push_back(curSixX.at(curSixX.size() - 1).y);

                   }
   // cout << curSixX.at(0).y <<" end " <<curSixX.at(curSixX.size() - 1).y << endl;
                       //cout << curSixX.at(i).x << "   "<< curSixX.at(i).y << endl;

                   //}



               /*	std::reverse(std::begin(curVecX), std::end(curVecX));
                   std::reverse(std::begin(curVecY), std::end(curVecY));*/
                   if(!curVecX.empty())
                   drawSplines(mat, curVecY, curVecX, false,false);

                   //cout << "i here4";
               }
               else {}

           }
   cout << counter1 << "current!!!!!s"<< endl;
       //int counter = 0;
       for (int i = 0; i <30; i++)
           for (int j = 0; j < 30; j++)
           {
               //cout << j;
               cv::Point y2;
               vector<cv::Point> curSixX;
               //cout << curSixX.size() << " sizeC";S
               for (int x = i * 16-3; x < (i + 1) * 16; x++) {
                   for (int y = j * 16-3; y < (j + 1) * 16; y++) {

                       //cout << counter << endl;
                       //cout << curSixY.size() << " size curY." << endl;
                       //cout << imgGrayscale.at<uchar>(x, y) << " size coor. " << x << " " << y << endl;

                       if (imgCanny.at<uchar>(x, y) > 0) {
                           imgCanny.at<uchar>(x, y) = 255;
                           //cout << curSixY.at(0) << " curY1";
                           y2 = cv::Point(x, y);
                       }

                       else {
                           imgCanny.at<uchar>(x, y) = 0;
                       }

                   }
                   if (y2.x == 0 && y2.y == 0) {}
                   else {
                       //cout << curSixY.at(0) << " curY" << endl;
                       curSixX.push_back(y2);
                   }
                   //cout << "i here";
               }
               //for (int i = 0; i <= curSixX.size(); i++) {
               //	//cout << curSixX.at(i);
               //}
               //cout << "i here2";
               //cout << curSixX.size();
               vector<double> curVecX;
               vector<double> curVecY;

               //cout << curSixX.size() << endl;
               if (curSixX.size() != 0 && curSixX.size() > 0&& curSixX.at(0).x != curSixX.at(curSixX.size()-1).x ) {
                   //for (int i = 0; i < curSixX.size(); i++) {

                       /*curVecX.push_back(curSixX.at(i).x);
                       curVecY.push_back(curSixX.at(i).y);*/
                   if((double)curSixX.at(0).x/5.0 < 5.0 ||(double)curSixX.at(0).y/5.0 < 5.0 || (double)curSixX.at(curSixX.size() - 1).x/5.0 < 5.0 || (double)curSixX.at(curSixX.size() - 1).y/5.0 < 5.0){}else{

                       counter1++;
                       myfile <<counter1<< " "<< (double)curSixX.at(0).x/5.0 << " " << (double)curSixX.at(0).y/5.0 << "&" << (double)curSixX.at(curSixX.size() - 1).x/5.0 << " " << (double)curSixX.at(curSixX.size() - 1).y/5.0 << "\n";
                       curVecX.push_back(curSixX.at(0).x);
                       curVecY.push_back(curSixX.at(0).y);
                       curVecX.push_back(curSixX.at(curSixX.size()-1).x);
                       curVecY.push_back(curSixX.at(curSixX.size()-1).y);
                   }
                       //cout << curSixX.at(i).x << "   "<< curSixX.at(i).y << endl;

                   //}


                   //cout << " end" << endl;

                   /*	std::reverse(std::begin(curVecX), std::end(curVecX));
                   std::reverse(std::begin(curVecY), std::end(curVecY));*/
                   if(!curVecX.empty())
                   drawSplines(mat,curVecX, curVecY, false, true);

                   //cout << "i here4";
               }
               else {}

           }

       imwrite("C:\\Users\\X\\Desktop\\ws\\opencv\\KUKA-face-picturing\\qt_opencv_server_kuka_app\\saved.png", mat);
       QThread::msleep(500);
          QString s = "C:\\Users\\X\\Desktop\\ws\\opencv\\KUKA-face-picturing\\qt_opencv_server_kuka_app\\saved.png";
       emit(sendImg(s));
       capWebcam.release();
      destroyAllWindows();
      myfile.close();
       cout << counter1 << " COUNTER1!" << endl;
exec();

}







