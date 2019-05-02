// TesterCv.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
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


VOID startup(LPCTSTR lpApplicationName)
{
	// additional information
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	// set the size of the structures
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// start the program up

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

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

void createServer(int id);
int main(int argc, char *argv[] )
{
//std:thread th1(createServer, 1);

	ofstream myfile;
	myfile.open("points.txt");

	cv::Mat frame, gray;
	cv::CascadeClassifier faceDetector("haarcascade_frontalface_alt2.xml");
	cv::Mat imgOriginal = cv::imread("lena.jpg");;        // input image
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

	cv::GaussianBlur(imgGrayscale, imgBlurred, cv::Size(5, 5), 1.8);           // Blur Effect             
																			   //cout << imgGrayscale.size();
	cv::Canny(imgBlurred, imgCanny, lowTh, highTh);       // Canny Edge Image


	//cv::Mat img = cv::imread("lena.jpg", 0);
	//cv::Mat img2 = cv::imread("lena.jpg");
	//cout << "hello";
	//imshow("sys",img);
	int c;

	/*for (int i = 0; i<img.rows; i++)
		for (int j = 0; j<img.cols; j++)
			std::cout << (int)img.at<uchar>(i, j) << std::endl;*/

	//uchar ch = 'A';
	//int ker = ch;
	//cout << 000000ker;
	//int counter = 0;
	//double d = ch;
	///////////////////////////////////////////////////////////////// Cesiar algorithm
	//cout << "M = " << endl << " " << imgGrayscale << endl << endl;

	vector<vector<cv::Point>> allSplines;
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
		
			if (curSixX.size() != 0 && curSixX.size() > 5) {
				
				//vector<Point> n;
				counter1++;
				//for (int i = 0; i < curSixX.size(); i++) {
				/*	n.at(i).x = curSixX.at(i).x;
					n.at(i).y = curSixX.at(i).y;
*/	myfile <<counter1<< " "<< (double)curSixX.at(0).x/5.0 << " " << (double)curSixX.at(0).y/5.0 << "&" << (double)curSixX.at(curSixX.size() - 1).x/5.0 << " " << (double)curSixX.at(curSixX.size() - 1).y/5.0 << "\n";

					curVecX.push_back(curSixX.at(0).x);
					curVecY.push_back(curSixX.at(0).y);
					curVecX.push_back(curSixX.at(curSixX.size() - 1).x);
					curVecY.push_back(curSixX.at(curSixX.size() - 1).y);
					//cout << curSixX.at(i).x << "   "<< curSixX.at(i).y << endl;
					
				//}
				allSplines.push_back(curSixX);
				//cout << " end" << endl;
			
			/*	std::reverse(std::begin(curVecX), std::end(curVecX));
				std::reverse(std::begin(curVecY), std::end(curVecY));*/
				drawSplines(mat, curVecY, curVecX, false);
				
				//cout << "i here4";
			}
			else {}
	
		}

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
			if (curSixX.size() != 0 && curSixX.size() > 0) {
				counter1++;
				//for (int i = 0; i < curSixX.size(); i++) {
				
					/*curVecX.push_back(curSixX.at(i).x);
					curVecY.push_back(curSixX.at(i).y);*/
				myfile << counter1<< " " << curSixX.at(0).x/5 << " " << curSixX.at(0).y/5 << "&"<< curSixX.at(curSixX.size() - 1).x/5 << " " << curSixX.at(curSixX.size() - 1).y/5 << "\n";
		
					curVecX.push_back(curSixX.at(0).x);
					curVecY.push_back(curSixX.at(0).y);
					curVecX.push_back(curSixX.at(curSixX.size()-1).x);
					curVecY.push_back(curSixX.at(curSixX.size()-1).y);
					//cout << curSixX.at(i).x << "   "<< curSixX.at(i).y << endl;

				//}

				allSplines.push_back(curSixX);
				//cout << " end" << endl;

				/*	std::reverse(std::begin(curVecX), std::end(curVecX));
				std::reverse(std::begin(curVecY), std::end(curVecY));*/
				drawSplines(mat,curVecX, curVecY, false, true);

				//cout << "i here4";
			}
			else {}

		}
	//<Server>
	//<Pos>
	//  <X>
	//	< / X>
	//    
	//	<Y>
	//	< / Y>
	//	<Z>
	// </Z>
	//	<A>
	// </A>
	//	<B>
	// </B>
	//	<C>
	// </C>
	//	< / Pos>
	//	< / Server>
	cout << counter1 << " COUNTER1!" << endl;
	//cout << counter << " COUNTER!";
	//cout << allSplines.size() << "size! ";
	
	vector<vector<string>> xmlMessages;
	for (int i = 0; i < allSplines.size(); i++) {
		vector<string> xmlMessage;
		for (int j = 0; j < allSplines.at(i).size(); j++){
			//cout << allSplines.at(i).at(j).x << " <-X; Y-> " << allSplines.at(i).at(j).y << endl;
			
				xmlMessage.push_back("<Server><Pos><X>" + to_string(allSplines.at(i).at(j).x) + "</X><Y>"+ to_string(allSplines.at(i).at(j).y) +"</Y><Z>10</Z><A>0</A><B>0</B><C>0</C><T>0</T><S>0</S></Pos></Server>");
				//cout << "<Server><Pos><X>" + to_string(allSplines.at(i).at(j).x) + "</X><Y>" + to_string(allSplines.at(i).at(j).y) + "</Y><Z>10</Z><A>0</A><B>0</B><C>0</C><T>0</T><S>0</S></Pos></Server>";
		}
		xmlMessages.push_back(xmlMessage);
	}

	
	//Sleep(5000);
	cout << xmlMessages.size() << "size!xml ";
	imshow("splines", imgCanny);
	imshow("origin", imgOriginal);
	imshow("origin", mat);

	
	//////////////////////////////////////////////////////////////////////////
	//LPCWSTR a = L"TCPServer2";
	//CreateProcess(a, NULL,NULL,           // Process handle not inheritable
	//	NULL,           // Thread handle not inheritable
	//	FALSE,          // Set handle inheritance to FALSE
	//	0,              // No creation flags
	//	NULL,           // Use parent environment block
	//	NULL,           // Use parent starting directory 
	//	NULL,            // Pointer to STARTUPINFO structure
	//	NULL);
	//startup(a);
	//system("start TCPServer2");
	//system("pause");
	ShellExecute(NULL, (LPCWSTR)"open", (LPCWSTR)"cmd", NULL, NULL, SW_SHOWDEFAULT);
	Sleep(1000);
	cv::waitKey(0);
	/*fopen("TCPServer2", "r");*/
	//system("start TCPServer2");
	LPCWSTR a = L"TCPServer2";
	LPCWSTR o = L"open";

    return 0;
}



void createServer(int id)
{
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		cerr << "Can't Initialize winsock! Quitting" << endl;
		return;
	}

	// Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cerr << "Can't create a socket! Quitting" << endl;
		return;
	}

	// Bind the ip address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(59152);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; // Could also use inet_pton .... 

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	// Tell Winsock the socket is for listening 
	listen(listening, SOMAXCONN);
	char host[NI_MAXHOST];
	SOCKET clientSocket;
	//while (host != "DESKTOP-T9DMDI9") {
		// Wait for a connection
		sockaddr_in client;
		int clientSize = sizeof(client);

		 clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

		// Client's remote name
		char service[NI_MAXSERV];	// Service (i.e. port) the client is connect on

		ZeroMemory(host, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
		ZeroMemory(service, NI_MAXSERV);

		if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
		{
			cout << host << " connected on port " << service << endl;
		}
		else
		{
			inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
			cout << host << " connected on port " <<
				ntohs(client.sin_port) << endl;
		}
	//}
	// Close listening socket
	closesocket(listening);

	// While loop: accept and echo message back to client
	string s = "<Server><Pos><X>" + to_string(150) + "</X><Y>" + to_string(300) + "</Y><Z>100</Z><A>0</A><B>0</B><C>0</C><T>0</T><S>0</S></Pos></Server>";
	const int const n = s.length();
	char * char_array = new char[(n + 1)];
	strcpy_s(char_array, (n + 1), s.c_str());


	//while (true)
	//{
	//ZeroMemory(buf, 4096);

	//// Wait for client to send data
	//int bytesReceived = recv(clientSocket, buf, 4096, 0);
	//if (bytesReceived == SOCKET_ERROR)
	//{
	//	cerr << "Error in recv(). Quitting" << endl;
	//	break;
	//}

	//if (bytesReceived == 0)
	//{
	//	cout << "Client disconnected " << endl;
	//	break;
	//}

	//cout << string(buf, 0, bytesReceived) << endl;

	// Echo message back to client

	send(clientSocket, char_array, n + 1, 0);

	//}

	// Close the socket
	closesocket(clientSocket);

	// Cleanup winsock
	WSACleanup();

	system("pause");
		////WSAStartup
		//WSAData wsaData;
		//WORD DLLVersion = MAKEWORD(2, 1);
		//if (WSAStartup(DLLVersion, &wsaData) != 0) {
		//	std::cout << "Error" << std::endl;
		//	exit(1);
		//}

		//SOCKADDR_IN addr;
		//int sizeofaddr = sizeof(addr);
		//addr.sin_addr.s_addr = inet_addr("127.0.0.2");
		//addr.sin_port = htons(56000);
		//addr.sin_family = AF_INET;

		//SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
		//bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
		//listen(sListen, SOMAXCONN);

		//SOCKET newConnection;
		//newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

		//if (newConnection == 0) {
		//	std::cout << "Error #2\n";
		//}
		//else {
		//	std::cout << "Client Connected!\n";
		//	char msg[256] = "Hello. It`s my first network program!";
		//	send(newConnection, msg, sizeof(msg), NULL);
		//}


		//system("pause");
	}


/*for (int i = 0; i < xmlMessages.size(); i++)
for (int j = 0; j < xmlMessages.at(i).size(); j++) {
const int const n = xmlMessages.at(i).at(j).length();
char * char_array = new char[(n + 1)];
strcpy_s(char_array, (n + 1), xmlMessages.at(i).at(j).c_str());
send(clientSocket, char_array, n + 1, 0);

}*/

//const int const n = xmlMessages.at(0).at(0).length();
//char * char_array = new char[(n + 1)];
//strcpy_s(char_array, (n + 1), xmlMessages.at(0).at(0).c_str());
//send(clientSocket, char_array, n + 1, 0);
