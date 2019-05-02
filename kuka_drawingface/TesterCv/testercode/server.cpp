// TCPServer.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <opencv2/opencv.hpp>
#pragma comment (lib, "ws2_32.lib")

using namespace cv;
using namespace std;

// must send it \/  
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
