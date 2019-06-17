// Client.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

void main()
{
	string ipAddress = "127.0.0.1";			// IP Address of the server
	int port = 1234;						// Listening port # on the server

	// Initialize WinSock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		cerr << "Can't start Winsock, Err #" << wsResult << endl;
		return;
	}

	// Create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	// Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}

	// Do-while loop to send and receive data
	char buf[4096];
	string userInput = "";
	int counter = 0;
	
	do
	{
		// Prompt the user for some text
		while (counter < 2) {
			int bytesReceived = recv(sock, buf, 4096, 0);



			userInput = string(buf, 0, bytesReceived);
			cout << userInput << endl;
			
			//cout << "i am here " << endl;
			ZeroMemory(buf, 4096);
			//int bytesReceived = recv(sock, buf, 4096, 0);
			//if (bytesReceived > 0)
			//{
			//	// Echo response to console
			//	cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;
			//}
			
			// Send the text
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			//cout << "i am here3 " << endl;
			Sleep(2000);
			if (sendResult != SOCKET_ERROR)
			{
				// Wait for response

			}
			counter++;
		}
		Sleep(1000);
		userInput = "<Server><Cmd>100</Cmd></Server>";
		counter = 0;
		cout << "send flag" << endl;
		int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
		userInput = "";
			
	} while (1);

	// Gracefully close down everything
	closesocket(sock);
	WSACleanup();
}