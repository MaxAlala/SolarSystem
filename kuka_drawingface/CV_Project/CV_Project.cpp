
#include "stdafx.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
#include "spline.h"
//Mat src, src_gray;
//Mat dst, detected_edges;
//int lowThreshold = 0;
//const int max_lowThreshold = 100;
//const int ratio = 3;
//const int kernel_size = 3;
//const char* window_name = "Edge Map";
//static void CannyThreshold(int, void*)
//{
//	blur(src_gray, detected_edges, Size(3, 3));
//	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);
//	dst = Scalar::all(0);
//	src.copyTo(dst, detected_edges);
//	imshow(window_name, dst);
//}
//int main(int argc, char** argv)
//{
//	//CommandLineParser parser(argc, argv, "{@input | ../data/fruits.jpg | input image}");
//	//src = imread(parser.get<String>("@input"), IMREAD_COLOR); // Load an image
//	//if (src.empty())
//	//{
//	//	std::cout << "Could not open or find the image!\n" << std::endl;
//	//	std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
//	//	return -1;
//	//}
//	//VideoCapture cam(0);
//	//Mat frame, gray;
//	src = imread("lena.jpg");
//	dst.create(src.size(), src.type());
//	cvtColor(src, src_gray, COLOR_BGR2GRAY);
//	namedWindow(window_name, WINDOW_AUTOSIZE);
//	createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);
//	CannyThreshold(0, 0);
//	waitKey(0);
//	return 0;
//}

// include the necessary libraries

//////////////////////////////////////////////////////

#include <opencv2/face.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;
using namespace cv::face;


///////////////////////
void drawSplines
(
	Mat &im,
	vector<double> &vecX,
	vector<double> &vecY,
	bool isClosed = false
)
{
	// Gather all points between the start and end indices
	//vector <Point> points;


	tk::spline s;
	s.set_points(vecX, vecY);
	double beg = vecX.at(0);
	double en = vecX.at(vecX.size()-1);
	//cout << beg << " beg and end " << en << endl;
	double dif = en - beg;
	double step_size = 1;
	int step_number = dif / 1;
	//cout << step_number << " steps " << endl;

	double cur_y = 0;
	//for (int i = 0; i < step_number; i++) {
	//	double cur_x = beg + i * 1;
	//	cur_y = s(cur_x);
	//	//cout << cur_x << " cur x and y " << cur_y << endl;
	//	//im.at<uchar>(cur_x, cur_y) = 255;
	///*	vecX.push_back(cur_x);
	//	vecY.push_back(cur_y);*/
	//	circle(im, Point(cur_x, cur_y), 2, Scalar(255, 200, 0), 1, 8);

	//}

	while (beg < en) {
		beg += step_size;
		cur_y = s(beg);
		circle(im, Point(cur_y, beg),1, Scalar(255, 200, 0), 1, 8);

	}
}

	// Draw polylines. 
	//polylines(im, points, isClosed, COLOR, 2, 16);



////////////////////////////
int main() {
	Mat frame, gray;
	CascadeClassifier faceDetector("haarcascade_frontalface_alt2.xml");

	cv::VideoCapture capWebcam(0);   // declare a VideoCapture object to associate webcam, 0 means use 1st (default) webcam

	if (capWebcam.isOpened() == false)  //  To check if object was associated to webcam successfully
	{
		std::cout << "error: Webcam connect unsuccessful\n"; // if not then print error message
		return(0);            // and exit program
	}

	cv::Mat imgOriginal;        // input image
	cv::Mat imgGrayscale;       // grayscale image
	cv::Mat imgBlurred;         // blured image
	cv::Mat imgCanny;           // Canny edge image

	char charCheckForEscKey = 0;
	int lowTh = 45;
	int highTh = 90;

	while (charCheckForEscKey != 27 && capWebcam.isOpened()) {            // until the Esc key is pressed or webcam connection is lost
		bool blnFrameReadSuccessfully = capWebcam.read(imgOriginal);   // get next frame
		
																	   // Find face
		vector<Rect> faces;
		cvtColor(imgOriginal, gray, COLOR_BGR2GRAY);
		faceDetector.detectMultiScale(gray, faces);

		if (!blnFrameReadSuccessfully || imgOriginal.empty()) {    // if frame read unsuccessfully
			std::cout << "error: frame can't read \n";      // print error message
			break;
		}
		double scale = 1;


		cv::cvtColor(imgOriginal, imgGrayscale, COLOR_BGR2GRAY);                   // convert to grayscale

		cv::GaussianBlur(imgGrayscale, imgBlurred, cv::Size(5, 5), 1.8);           // Blur Effect             
		//cout << imgGrayscale.size();
		cv::Canny(imgBlurred, imgCanny, lowTh, highTh);       // Canny Edge Image

		for (size_t i = 0; i < faces.size(); i++) // rectangles
		{
			Rect r = faces[i];
			Scalar color = Scalar(255, 0, 0);
	
			rectangle(imgCanny, Point(cvRound((r.x-30)*scale), cvRound((r.y-70)*scale)), Point(cvRound((r.x +
				(r.width + 50) - 1)*scale), cvRound((r.y + (r.width + 50) - 1)*scale)), color, 3, 8, 0);
		}
															  //declare windows
		/////////////////////////////////////////////////////////////////// Cesiar algorithm
		////cout << "M = " << endl << " " << imgGrayscale << endl << endl;
		//int counter = 0;
		//for(int i = 0; i < 78; i ++)
		//	for (int j = 0; j < 78; j++)
		//	{
		//		//cout << j;
		//		Point y2;
		//		vector<Point> curSixX;
		//		//cout << curSixX.size() << " sizeC";
		//		for (int x = i * 6; x < (i + 1) * 6; x++) {
		//			for (int y = j * 6; y < (j + 1) * 6; y++) {
		//				counter++;
		//				//cout << counter << endl;
		//				//cout << curSixY.size() << " size curY." << endl;
		//				//cout << imgGrayscale.at<uchar>(x, y) << " size coor. " << x << " " << y << endl;

		//				if (imgCanny.at<uchar>(x, y) > 100) {
		//					imgCanny.at<uchar>(x, y) = 255;
		//					//cout << curSixY.at(0) << " curY1";
		//					y2 = Point(x, y);
		//				}

		//				else {
		//					imgCanny.at<uchar>(x, y) = 0;
		//				}

		//			}
		//			if (y2.x == 0 && y2.y == 0) {}
		//			else {
		//				//cout << curSixY.at(0) << " curY" << endl;
		//				curSixX.push_back(y2);
		//			}
		//			//cout << "i here";
		//		}
		//		//for (int i = 0; i <= curSixX.size(); i++) {
		//		//	//cout << curSixX.at(i);
		//		//}
		//		//cout << "i here2";
		//		//cout << curSixX.size();
		//				vector<double> curVecX;
		//				vector<double> curVecY;
		//				if (curSixX.size() != 0) {
		//					for (int i = 0; i < curSixX.size(); i++) {
		//						
		//						curVecX.push_back(curSixX.at(i).x);
		//						curVecY.push_back(curSixX.at(i).y);

		//					}
		//					//cout << "i here3";
		//					drawSplines(imgCanny, curVecX, curVecY, false);
		//					//cout << "i here4";
		//				} else{}

		//	}
		//////////////////////////////////////////////////////////////////////////

		cv::namedWindow("imgOriginal", WINDOW_NORMAL);
		cv::namedWindow("imgCanny", WINDOW_NORMAL);
		//declare trackbar
		cv::createTrackbar("LowTh", "imgCanny", &lowTh, 100);
		cv::createTrackbar("HighTh", "imgCanny", &highTh, 100);
		// show windows
		cv::imshow("imgOriginal", imgOriginal);
		cv::imshow("imgCanny", imgCanny);

		

		int c;
		c = waitKey(5);
		// Exit loop if ESC is pressed
		if (c == 27) {
			break;
		}

		if (c == 13) {

			//cv::Mat mat(frame.size(), CV_8UC1, cv::Scalar(255, 0, 255));
			Mat cropedImage = imgCanny(Rect(faces[0].x, faces[0].y, faces[0].width + 50, faces[0].height + 50));
			Mat mat = Mat::zeros(cropedImage.size(), CV_8UC1);
			

			///////////////////////////////////////////////////////////////// Cesiar algorithm
			//cout << "M = " << endl << " " << imgGrayscale << endl << endl;
			int counter = 0;
			for (int i = 0; i <120; i++)
				for (int j = 0; j < 120; j++)
				{ 
					//cout << j;
					Point y2;
					vector<Point> curSixX;
					//cout << curSixX.size() << " sizeC";S
					for (int x = i * 2; x < (i + 1) * 4; x++) {
						for (int y = j * 2; y < (j + 1) * 4; y++) {
							counter++;
							//cout << counter << endl;
							//cout << curSixY.size() << " size curY." << endl;
							//cout << imgGrayscale.at<uchar>(x, y) << " size coor. " << x << " " << y << endl;

							if (cropedImage.at<uchar>(x, y) > 0) {
								cropedImage.at<uchar>(x, y) = 255;
								//cout << curSixY.at(0) << " curY1";
								y2 = Point(x, y);
							}

							else {
								cropedImage.at<uchar>(x, y) = 0;
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
					if (curSixX.size() != 0) {
						for (int i = 0; i < curSixX.size(); i++) {

							curVecX.push_back(curSixX.at(i).x);
							curVecY.push_back(curSixX.at(i).y);
							//cout << curSixX.at(i).x << "   "<< curSixX.at(i).y << endl;

						}
						//cout << " end" << endl;


						drawSplines(mat, curVecX, curVecY, false);

						//cout << "i here4";
					}
					else {}
				/*	imshow("splines", imgCanny);
					imshow("origin", imgOriginal);
					imshow("origin", mat);*/
					imwrite("saved.png", mat);
				}
			//////////////////////////////////////////////////////////////////////////


		}
	}

	return(0);
}
