// mpi2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "mpi.h"
#include <stdio.h>
#pragma comment(lib, "msmpi.lib")
#include "vector" 
#include "algorithm" 
#include <ctime>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <numeric>  
//using namespace std;
#include <random>
#include <ctime>
#include <chrono>
#include "math.h"
#include <array>

using namespace std;
typedef double(*pointFunc)(double);
double f(double x) {
	return (10 - x);
}
double simpson_integral(pointFunc f, double a, double b, int n) {
	const double h = (b - a) / n;
	double k1 = 0, k2 = 0;
	for (int i = 1; i < n; i += 2) {
		k1 += f(a + i * h);
		k2 += f(a + (i + 1)*h);
	}
	return h / 3 * (f(a) + 4 * k1 + 2 * k2);
}





int main(int argc, char **argv)
{
	using namespace std;
	int rank = 0;
		int size = 3;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	// 1 & 2 tasks -n 4

		//printf("Process %d size %d \n", rank, size); // 1 and 2
		//std::cout << "Hello World! MPI";

	// 3 task  -n 2
	//
	//if (rank == 0) {
	//	srand(time(NULL));
	//	int number =10;
	//	vector<int> vec(number, 2);
	//	int ar[10] = { 1,2,3,4,5,6,7,8,9,10 };
	//	for_each(vec.begin(), vec.end(), [](int &x) {
	//		x = 1 + rand() % 12;
	//	});

	//	MPI_Send(static_cast<void*>(vec.data()), number, MPI_INT, 1, 5, MPI_COMM_WORLD);

	//}
	//else if (rank == 1) {
	//	MPI_Status status;
	//	vector<int> receiver(10,0);
	//	int number = 10;


	//	MPI_Recv(static_cast<void*>(receiver.data()), number, MPI_FLOAT, 0, 5, MPI_COMM_WORLD, &status);


	//	for (int i = 0; i < number; i++)
	//	{
	//		cout << receiver.at(i) << " received \n";
	//	}
	//}

	// 4 task -n 3 or any number


	//int number_amount;
	//if (rank == 0) {
	//	const int MAX_NUMBERS = 10;
	//	int numbers[MAX_NUMBERS] = {1,2,3,4,5,6,7,8,9};
	//	// Pick a random amount of integers to send to process one
	//	srand(time(NULL));
	//	number_amount = (rand() / (float)RAND_MAX) * MAX_NUMBERS;

	//	cout << "num of processes is " << size << "\n";
	//	// Send the random amount of integers to process one
	//	while (size-1 > 0) {
	//		MPI_Send(numbers, number_amount, MPI_INT, size-1, 0, MPI_COMM_WORLD);
	//		printf("0 sent %d numbers to %d\n", number_amount, size-1);
	//		size--;
	//	}
	//	//MPI_Send(numbers, number_amount, MPI_INT, 1, 0, MPI_COMM_WORLD);
	//}

	//else {
	//	MPI_Status status;
	//	// Probe for an incoming message from process zero
	//	MPI_Probe(0, 0, MPI_COMM_WORLD, &status);

	//	// When probe returns, the status object has the size and other
	//	// attributes of the incoming message. Get the message size
	//	MPI_Get_count(&status, MPI_INT, &number_amount);

	//	// Allocate a buffer to hold the incoming numbers
	//	int* number_buf = new int[sizeof(int) * number_amount];

	//	// Now receive the message with the allocated buffer
	//	MPI_Recv(number_buf, number_amount, MPI_INT, 0, 0,
	//		MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	//	printf("%d dynamically received %d numbers from 0.\n",
	//		rank, number_amount);
	//	for (int i = 0; i < number_amount; i++)
	//	{
	//		cout << number_buf[i] << "\n";
	//	}

	//	delete[] number_buf;
	//}


	// 5 task -n 10 or 9
	//vector<int> proccessesnames = { 2,3,4,6,8 };
	//int number_amount;
	//if (rank == 0) {
	//	const int max_numbers = 12;
	//	vector<int> numbers = {1,2,3,4,5,6,7,8,9,10,11,12};
	//	// pick a random amount of integers to send to process one
	//	srand(time(NULL));
	//	number_amount = (rand() / (float)RAND_MAX) * max_numbers;

	//	cout << "num of processes is " << size << "\n";
	//	// send the random amount of integers to process one
	//	for(int i = 0; i < proccessesnames.size(); i++){
	//		MPI_Send(numbers.data(), 12/proccessesnames.at(i)+1, MPI_INT, proccessesnames.at(i), 0, MPI_COMM_WORLD);
	//		printf("0 sent %d numbers to %d\n", 12/proccessesnames.at(i)+1, proccessesnames.at(i));
	//		size--;
	//	}
	//	//mpi_send(numbers, number_amount, mpi_int, 1, 0, mpi_comm_world);
	//}
	//	else if(find(proccessesnames.begin(), proccessesnames.end(), rank) != proccessesnames.end()) {
	//	MPI_Status status;
	//	// probe for an incoming message from process zero
	//	MPI_Probe(0, 0, MPI_COMM_WORLD, &status);

	//	// when probe returns, the status object has the size and other
	//	// attributes of the incoming message. get the message size
	//	MPI_Get_count(&status, MPI_INT, &number_amount);

	//	// allocate a buffer to hold the incoming numbers
	//	int* number_buf = new int[sizeof(int) * number_amount];

	//	// now receive the message with the allocated buffer
	//	MPI_Recv(number_buf, number_amount, MPI_INT, 0, 0,
	//		MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	//	printf("%d dynamically received %d numbers from 0.\n",
	//		rank, number_amount);
	//	for (int i = 0; i < number_amount; i++)
	//	{
	//		cout << number_buf[i] << "\n";
	//	}

	//	delete[] number_buf;
	//}

//task 6 -n 4
//
//vector<int> proccessesNames = {1,2,3};
//int number_amount;
//if (rank == 0) {
//	const int MAX_NUMBERS = 12;
//	vector<int> numbers = { 1,2,3,4,5,6}; // xy pairs
//	vector<int> zVector;
//	//vector<vector<int>> threeVectors = { {1,1,1},{2,2,2},{0,0,0} };
//
//	// Pick a random amount of integers to send to process one
//	srand(time(NULL));
//	number_amount = (rand() / (float)RAND_MAX) * MAX_NUMBERS;
//
//	cout << "num of processes is " << size << "\n";
//	// Send the random amount of integers to process one
//	 int vectorSize = numbers.size();
//	for (int i = 0; i < proccessesNames.size(); i++) {
//		MPI_Send(numbers.data(), vectorSize /proccessesNames.size(), MPI_INT, proccessesNames.at(i), 0, MPI_COMM_WORLD);
//		printf("0 sent %d numbers to %d\n", vectorSize / proccessesNames.size(), proccessesNames.at(i));
//		size--;
//		numbers.erase(numbers.begin(), (numbers.begin() + 2));
//	}
//	while (zVector.size() != 3) {
//		MPI_Status status;
//		static int counter = 0;
//		cout << "attemp " << counter << "\n";
//		// Probe for an incoming message from process zero
//		//MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
//
//		// When probe returns, the status object has the size and other
//		// attributes of the incoming message. Get the message size
//		//MPI_Get_count(&status, MPI_INT, &number_amount);
//
//	
//
//		for (int k = 1; k <= 3; k++) {
//			// Allocate a buffer to hold the incoming numbers
//			int* number_buf_z = new int[sizeof(int) * vectorSize / proccessesNames.size()];
//			MPI_Recv(number_buf_z, vectorSize / proccessesNames.size()/2, MPI_INT, k, 0,
//				MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//		
//			for (int i = 0; i < vectorSize / proccessesNames.size()/2; i++)
//			{
//				cout << number_buf_z[i] << " in buf z" << endl;
//
//				zVector.push_back(number_buf_z[i]);
//
//			}
//			//if (zVector.size() == vectorSize / 2) break;
//			delete[] number_buf_z;
//		}
//		cout << "z vec size is " << zVector.size() << endl;
//	}
//	cout << "vector Z equals to: \n";
//	for_each(zVector.begin(), zVector.end(), [](int x){
//		cout << x << "\n"; });
//
//	//MPI_Send(numbers, number_amount, MPI_INT, 1, 0, MPI_COMM_WORLD);
//}
//else if (find(proccessesNames.begin(), proccessesNames.end(), rank) != proccessesNames.end()) {
//	MPI_Status status;
//	// Probe for an incoming message from process zero
//	MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
//
//	// When probe returns, the status object has the size and other
//	// attributes of the incoming message. Get the message size
//	MPI_Get_count(&status, MPI_INT, &number_amount);
//
//	// Allocate a buffer to hold the incoming numbers
//	int* number_buf = new int[sizeof(int) * number_amount];
//
//	// Now receive the message with the allocated buffer
//	MPI_Recv(number_buf, number_amount, MPI_INT, 0, 0,
//		MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//	printf("%d dynamically received %d numbers from 0.\n",
//		rank, number_amount);
//	vector<int > resultZvector(number_amount/2);
//	for (int i = 0; i < number_amount; i++)
//	{
//		cout << number_buf[i] << "\n";
//
//	}
//	for (int i = 0; i < number_amount/2; i++)
//	{
//		resultZvector.at(i) = number_buf[i] + number_buf[i + 1];
//		cout << resultZvector.at(i) << " is Z coordinate." << "\n";
//	}
//	MPI_Send(resultZvector.data(), resultZvector.size(), MPI_INT, 0, 0, MPI_COMM_WORLD);
//
//
//	delete[] number_buf;
//}



// task 7 -n 4
//const int a = 2;
//const int b = 2;
//vector<int> proccessesNames = { 1,2,3 };
//int number_amount;
//if (rank == 0) {
//	const int MAX_NUMBERS = 12;
//	vector<int> numbers = { 1,2,3,4,5,6 }; // xy pairs
//	vector<int> zVector;
//	//vector<vector<int>> threeVectors = { {1,1,1},{2,2,2},{0,0,0} };
//
//	// Pick a random amount of integers to send to process one
//	srand(time(NULL));
//	number_amount = (rand() / (float)RAND_MAX) * MAX_NUMBERS;
//
//	cout << "num of processes is " << size << "\n";
//	// Send the random amount of integers to process one
//	int vectorSize = numbers.size();
//	for (int i = 0; i < proccessesNames.size(); i++) {
//		MPI_Send(numbers.data(), vectorSize / proccessesNames.size(), MPI_INT, proccessesNames.at(i), 0, MPI_COMM_WORLD);
//		printf("0 sent %d numbers to %d\n", vectorSize / proccessesNames.size(), proccessesNames.at(i));
//		size--;
//		numbers.erase(numbers.begin(), (numbers.begin() + 2));
//	}
//	/*while (zVector.size() != 12) {*/
//		MPI_Status status;
//		static int counter = 0;
//		cout << "attemp " << counter << "\n";
//		// Probe for an incoming message from process zero
//		//MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
//
//		// When probe returns, the status object has the size and other
//		// attributes of the incoming message. Get the message size
//		//MPI_Get_count(&status, MPI_INT, &number_amount);
//
//
//
//		for (int k = 1; k <= 3; k++) {
//			// Allocate a buffer to hold the incoming numbers
//			int* number_buf_z = new int[sizeof(int) * vectorSize / proccessesNames.size() * 2 + 1];
//			MPI_Recv(number_buf_z, vectorSize / proccessesNames.size() * 2 + 1, MPI_INT, k, 0,
//				MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//
//			for (int i = 0; i < vectorSize / proccessesNames.size() * 2 + 1; i++)
//			{
//				cout << number_buf_z[i] << " in buf z" << endl;
//
//				zVector.push_back(number_buf_z[i]);
//
//			}
//			//if (zVector.size() == vectorSize / 2) break;
//			delete[] number_buf_z;
//		}
//		cout << "z vec size is " << zVector.size() << endl;
//	//}
//	cout << "vector Z equals to: \n";
//	for_each(zVector.begin(), zVector.end(), [](int x) {
//		cout << x << "\n"; });
//
//	//MPI_Send(numbers, number_amount, MPI_INT, 1, 0, MPI_COMM_WORLD);
//}
//else if (find(proccessesNames.begin(), proccessesNames.end(), rank) != proccessesNames.end()) {
//	MPI_Status status;
//	// Probe for an incoming message from process zero
//	MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
//
//	// When probe returns, the status object has the size and other
//	// attributes of the incoming message. Get the message size
//	MPI_Get_count(&status, MPI_INT, &number_amount);
//
//	// Allocate a buffer to hold the incoming numbers
//	int* number_buf = new int[sizeof(int) * number_amount];
//
//	// Now receive the message with the allocated buffer
//	MPI_Recv(number_buf, number_amount, MPI_INT, 0, 0,
//		MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//	printf("%d dynamically received %d numbers from 0.\n",
//		rank, number_amount);
//	vector<int > resultZvector;
//	for (int i = 0; i < number_amount; i++)
//	{
//		cout << number_buf[i] << "\n";
//
//	}
//	for (int i = 0; i < number_amount / 2; i++)
//	{
//		int buf_num = 0;
//		buf_num = number_buf[i] * a + number_buf[i + 1] * b;
//		resultZvector.push_back(buf_num);
//		cout << buf_num << " is Z coordinate." << "\n";
//
//		buf_num = number_buf[i] * a + number_buf[i + 1] * b;
//		resultZvector.push_back(buf_num);
//		cout << buf_num << " is new Y coordinate." << "\n";
//
//		buf_num = number_buf[i] * number_buf[i + 1];
//		resultZvector.push_back(buf_num);
//		cout << buf_num << " is again Z coordinate." << "\n";
//		resultZvector.push_back(number_buf[i+1]);
//		resultZvector.push_back(number_buf[i]);
//
//	
//	}
//	MPI_Send(resultZvector.data(), resultZvector.size(), MPI_INT, 0, 0, MPI_COMM_WORLD);
//
//
//	delete[] number_buf;
//}


// task 8 -n 3

//const int a = 2;
//const int b = 2;
//vector<int> proccessesNames = { 1,2 };
//int number_amount;
//if (rank == 0) {
//	const int MAX_NUMBERS = 12;
//	vector<int> numbers = { 1,2,3,4,5,6 }; // xy pairs
//	vector<int> zVector;
//	vector<int> matrixA = {1,1,1,1}; // 2x2 matrix
//	vector<int> matrixB = {2,2,2,2}; // 2x2 matrix
//
//
//	// Pick a random amount of integers to send to process one
//	srand(time(NULL));
//	//number_amount = (rand() / (float)RAND_MAX) * MAX_NUMBERS;
//
//	cout << "num of processes is " << size << "\n";
//	// Send the random amount of integers to process one
//	
//	
//	for (int i = 0; i < proccessesNames.size(); i++) {
//		vector<int> bufferVector;
//		vector<int> bufferBMatrix(matrixB);
//		vector<int> bufferAMatrix(matrixA);
//		bufferVector.push_back(2);
//		for (int j = 0; j < matrixA.size()/2; j++)
//		{
//			
//			bufferVector.push_back(bufferAMatrix.back());
//			bufferAMatrix.pop_back();
//		}
//			
//		for (int k = 0; k < matrixB.size(); k++)
//		{
//			bufferVector.push_back(bufferBMatrix.back());
//			bufferBMatrix.pop_back();
//		}
//
//		MPI_Send(bufferVector.data(), bufferVector.size(), MPI_INT, proccessesNames.at(i), 0, MPI_COMM_WORLD);
//		printf("0 sent %d numbers to %d\n", bufferVector.size(), proccessesNames.at(i));
//
//	}
//	while (zVector.size() != 4) {
//		MPI_Status status;
//		static int counter = 0;
//		cout << "attemp " << counter << "\n";
//
//		for (int k = 1; k <= 2; k++) {
//			// Allocate a buffer to hold the incoming numbers
//			int* number_buf_z = new int[sizeof(int) * matrixB.size()];
//			MPI_Recv(number_buf_z, matrixB.size()/2, MPI_INT, k, 0,
//				MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//
//			for (int i = 0; i < matrixB.size() / 2; i++)
//			{
//				cout << number_buf_z[i] << " in buf z" << endl;
//
//				zVector.push_back(number_buf_z[i]);
//
//			}
//			//if (zVector.size() == vectorSize / 2) break;
//			delete[] number_buf_z;
//		}
//		cout << "z vec size is " << zVector.size() << endl;
//	}
//	cout << "vector Z equals to: \n";
//	for_each(zVector.begin(), zVector.end(), [](int x) {
//		cout << x << "\n"; });
//
//	//MPI_Send(numbers, number_amount, MPI_INT, 1, 0, MPI_COMM_WORLD);
//}
//else if (find(proccessesNames.begin(), proccessesNames.end(), rank) != proccessesNames.end()) {
//	MPI_Status status;
//	// Probe for an incoming message from process zero
//	MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
//
//	// When probe returns, the status object has the size and other
//	// attributes of the incoming message. Get the message size
//	MPI_Get_count(&status, MPI_INT, &number_amount);
//
//	// Allocate a buffer to hold the incoming numbers
//	int* number_buf = new int[sizeof(int) * number_amount];
//	cout << number_amount << "count \n";
//	// Now receive the message with the allocated buffer
//	MPI_Recv(number_buf, number_amount, MPI_INT, 0, 0,
//		MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//	printf("%d dynamically received %d numbers from 0.\n",
//		rank, number_amount);
//	vector<int > resultZvector;
//	for (int i = 0; i < number_amount; i++)
//	{
//		cout << number_buf[i] << "\n";
//
//	}
//	
//		int buf_num = 0;
//		int i = 0;
//		resultZvector.push_back(number_buf[i+1] * number_buf[i + 1 + number_buf[0]] + number_buf[i+2]* number_buf[i + 2 + number_buf[0]]);
//		resultZvector.push_back(number_buf[i + 1] * number_buf[i + 3 + number_buf[0]] + number_buf[i + 2] * number_buf[i + 4 + number_buf[0]]);
//	
//	
//
//	MPI_Send(resultZvector.data(), resultZvector.size(), MPI_INT, 0, 0, MPI_COMM_WORLD);
//
//
//	delete[] number_buf;
//}

// task 9 -n 3
//const int a = 2;
//const int b = 2;
//vector<int> proccessesNames = { 1,2 };
//int number_amount;
//if (rank == 0) {
//	const int MAX_NUMBERS = 12;
//	vector<int> numbers = { 1,2,3,4,5,6 }; // xy pairs
//	vector<int> zVector;
//	vector<int> vectorX = {1,2};
//	vector<int> matrixA = { 1,1,1,1 }; // 2x2 matrix
//
//	//vector<int> matrixB = { 2,2,2,2 }; // 2x2 matrix
//
//
//	// Pick a random amount of integers to send to process one
//	srand(time(NULL));
//	//number_amount = (rand() / (float)RAND_MAX) * MAX_NUMBERS;
//
//	cout << "num of processes is " << size << "\n";
//	// Send the random amount of integers to process one
//
//
//	for (int i = 0; i < proccessesNames.size(); i++) {
//		vector<int> bufferVector;
//		//vector<int> bufferBMatrix(matrixB);
//		vector<int> bufferAMatrix(matrixA);
//		for (int j = 0; j < matrixA.size() / proccessesNames.size(); j++)
//		{
//
//			bufferVector.push_back(bufferAMatrix.back());
//			bufferAMatrix.pop_back();
//		}
//
//		for (int k = 0; k < vectorX.size(); k++)
//		{
//			bufferVector.push_back(vectorX.at(k));
//		}
//
//		MPI_Send(bufferVector.data(), bufferVector.size(), MPI_INT, proccessesNames.at(i), 0, MPI_COMM_WORLD);
//		printf("0 sent %d numbers to %d\n", bufferVector.size(), proccessesNames.at(i));
//
//	}
//	while (zVector.size() != 4) {
//		MPI_Status status;
//		static int counter = 0;
//		cout << "attemp " << counter << "\n";
//
//		for (int k = 1; k <= 2; k++) {
//			// Allocate a buffer to hold the incoming numbers
//			int* number_buf_z = new int[sizeof(int) * matrixA.size()];
//			MPI_Recv(number_buf_z, matrixA.size() / 2, MPI_INT, k, 0,
//				MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//
//			for (int i = 0; i < matrixA.size() / 2; i++)
//			{
//				cout << number_buf_z[i] << " in buf z" << endl;
//
//				zVector.push_back(number_buf_z[i]);
//
//			}
//			//if (zVector.size() == vectorSize / 2) break;
//			delete[] number_buf_z;
//		}
//		cout << "z vec size is " << zVector.size() << endl;
//	}
//	cout << "vector Z equals to: \n";
//	for_each(zVector.begin(), zVector.end(), [](int x) {
//		cout << x << "\n"; });
//
//	//MPI_Send(numbers, number_amount, MPI_INT, 1, 0, MPI_COMM_WORLD);
//}
//else if (find(proccessesNames.begin(), proccessesNames.end(), rank) != proccessesNames.end()) {
//	MPI_Status status;
//	// Probe for an incoming message from process zero
//	MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
//
//	// When probe returns, the status object has the size and other
//	// attributes of the incoming message. Get the message size
//	MPI_Get_count(&status, MPI_INT, &number_amount);
//
//	// Allocate a buffer to hold the incoming numbers
//	int* number_buf = new int[sizeof(int) * number_amount];
//	cout << number_amount << "count \n";
//	// Now receive the message with the allocated buffer
//	MPI_Recv(number_buf, number_amount, MPI_INT, 0, 0,
//		MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//	printf("%d dynamically received %d numbers from 0.\n",
//		rank, number_amount);
//	vector<int > resultZvector;
//	for (int i = 0; i < number_amount; i++)
//	{
//		cout << number_buf[i] << "\n";
//
//	}
//
//	int buf_num = 0;
//	int i = 0;
//	if(rank == 1)
//	resultZvector.push_back(number_buf[1]);
//	else {
//		resultZvector.push_back(number_buf[2]);
//	}
//	resultZvector.push_back(number_buf[0] * number_buf[2] + number_buf[1] * number_buf[3]);
//
//
//
//	MPI_Send(resultZvector.data(), resultZvector.size(), MPI_INT, 0, 0, MPI_COMM_WORLD);
//
//
//	delete[] number_buf;
//}

// task 10 -n 2
//class Timer
//{
//private:
//    // Псевдонимы типов используются для удобного доступа к вложенным типам
//    using clock_t = std::chrono::high_resolution_clock;
//    using second_t = std::chrono::duration<double, std::ratio<1> >;
//
//    std::chrono::time_point<clock_t> m_beg;
//
//public:
//    Timer() : m_beg(clock_t::now())
//    {
//    }
//
//    void reset()
//    {
//        m_beg = clock_t::now();
//    }
//
//    double elapsed() const
//    {
//        return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
//    }
//};
//
//const int a = 2;
//const int b = 2;
//vector<int> proccessesNames = { 1};
//vector<double> sendflag(1, 1);
//vector<double> getflag(1, 0);
//int number_amount;
//bool typeIsAorB = true; // false == a ping pong
//bool firstHasReceived = false;
//bool secondHasReceived = false;
//int n = 10000; // for pingping more than 100000 is impossible because of some mysterious reason
//Timer pingPingTimer;
//cout << "hy";
//if (rank == 0) {
//	const int MAX_NUMBERS = 12;
//	vector<int> numbers = { 1,2,3,4,5,6 }; // xy pairs
//	vector<int> zVector;
//	vector<int> vectorX = {1,2};
//	vector<double> matrixA(n,1); // 2x2 matrix
//
//
//	srand(time(NULL));
//
//	cout << "num of processes is " << size << "\n";
//
//	Timer t0;
//		MPI_Send(matrixA.data(), matrixA.size(), MPI_DOUBLE, proccessesNames.at(0), 0, MPI_COMM_WORLD);
//		printf("0 sent %d numbers to %d\n", matrixA.size(), proccessesNames.at(0));
//		//cout << t0.elapsed() << ": 0 process has sent a message. Ping \n";
//	//}
//		Timer t1;
//	//while (zVector.size() != n) {
//	
//		MPI_Status status;
//	/*	static int counter = 0;
//		cout << "attemp " << counter << "\n";*/
//
//		//for (int k = 1; k <= n; k++) {
//			// Allocate a buffer to hold the incoming numbers
//			double* number_buf_z = new double[sizeof(int) * matrixA.size()];
//			MPI_Recv(number_buf_z, matrixA.size(), MPI_DOUBLE, 1, 0,
//				MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//
//			for (int i = 0; i < matrixA.size(); i++)
//			{
//				//cout << number_buf_z[i] << " in buf z" << endl;
//
//				zVector.push_back(number_buf_z[i]);
//
//			}
//			//if (zVector.size() == vectorSize / 2) break;
//			delete[] number_buf_z;
//		//}
//		cout << "z vec size is " << zVector.size() << endl;
//	//}
//	//MPI_Send(sendflag.data(), sendflag.size(), MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
//	MPI_Recv(getflag.data(), getflag.size(), MPI_DOUBLE, 1, 0,
//		MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//
//	cout << getflag.at(0) << ": flag \n";
//
//	firstHasReceived = true;
//	if (getflag.at(0) == 1)
//		secondHasReceived = true;
//	cout << "2 change common val \n";
//	if (typeIsAorB == false) {
//	cout <<t0.elapsed() << ": process 0 has received the message. Ping Pong \n";
//	}
//	
//	//cout << "vector Z size equals to: "<<zVector.size()  << "\n";
//	//for_each(zVector.begin(), zVector.end(), [](int x) {
//	//	cout << x << "\n"; });
//
//	//MPI_Send(numbers, number_amount, MPI_INT, 1, 0, MPI_COMM_WORLD);
//}
//else if (find(proccessesNames.begin(), proccessesNames.end(), rank) != proccessesNames.end()) {
//	if (typeIsAorB == true) { // if PING PING
//		
//		MPI_Status status;
//		vector<double> sendvector(n, 1);
//		vector<double> sendflag(1, 1);
//		vector<double> getflag(1, 1);
//		MPI_Send(sendvector.data(), sendvector.size(), MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
//
//		// Probe for an incoming message from process zero
//		MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
//
//		// When probe returns, the status object has the size and other
//		// attributes of the incoming message. Get the message size
//		MPI_Get_count(&status, MPI_DOUBLE, &number_amount);
//
//		// Allocate a buffer to hold the incoming numbers
//		double* number_buf = new double[sizeof(int) * number_amount];
//		cout << number_amount << "count \n";
//		// Now receive the message with the allocated buffer
//		MPI_Recv(number_buf, number_amount, MPI_DOUBLE, 0, 0,
//			MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//		printf("%d dynamically received %d numbers from 0. Ping Ping.\n",
//			rank, number_amount);
//		MPI_Send(sendflag.data(), sendflag.size(), MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
//		/*MPI_Recv(getflag.data(), getflag.size(), MPI_DOUBLE, 0, 0,
//			MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//		secondHasReceived = true;*/
//		//cout << rank << " has changed the common val \n";
//		delete[] number_buf;
//
//	}
//	else
//	{
//		Timer t;
//		MPI_Status status;
//		// Probe for an incoming message from process zero
//		MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
//
//		// When probe returns, the status object has the size and other
//		// attributes of the incoming message. Get the message size
//		MPI_Get_count(&status, MPI_DOUBLE, &number_amount);
//
//		// Allocate a buffer to hold the incoming numbers
//		int* number_buf = new int[sizeof(int) * number_amount];
//		cout << number_amount << "count \n";
//		// Now receive the message with the allocated buffer
//		MPI_Recv(number_buf, number_amount, MPI_DOUBLE, 0, 0,
//			MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//		printf("%d dynamically received %d numbers from 0.\n",
//			rank, number_amount);
//
//		MPI_Send(number_buf, number_amount, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
//
//		delete[] number_buf;
//	}
//
//}
//if (typeIsAorB == true && rank == 0)
//{
//	while (firstHasReceived != true )
//	{
//		while (secondHasReceived != true) {}
//	}
//	cout << pingPingTimer.elapsed() << ": pingping time \n";
//}


// task 11 -n 2 
//vector<float > rand_nums(4,2);
//if (rank == 0) {
//	
//}
//
//vector<float > receiver(4,0);
//vector<float > localReceiver(4,0);
//float getdata;
//// Scatter the random numbers to all processes
//MPI_Scatter(rand_nums.data(), 2, MPI_FLOAT, receiver.data(),
//	2, MPI_FLOAT, 0, MPI_COMM_WORLD);
//
//// Compute the average of your subset
//cout << receiver.size();
//
//float localSumOfSquare = 0;
//for (int x : receiver) {
//	localSumOfSquare += x * x;
//
//cout << x << " is val of " << rank << "\n";
//}
//MPI_Reduce(&localSumOfSquare, &getdata, 1, MPI_FLOAT, MPI_SUM, 0,
//	MPI_COMM_WORLD);
//
//// Print the result
//if (rank == 0) {
//	printf("Total length i s = %f\n", sqrt(getdata));
//}
//

//task 12 -n 2
//	vector<float> twoVectors = {1,2,1,2}; // NB! chess distribution here
//if (rank == 0) {
//
//}
//
//vector<float > receiver(4, 1);
//float getdata;
//// Scatter the random numbers to all processes
//MPI_Scatter(twoVectors.data(), 2, MPI_FLOAT, receiver.data(),
//	2, MPI_FLOAT, 0, MPI_COMM_WORLD);
//
//
//cout << receiver.size();
//
//float localmult = 1;
//for (float x : receiver) {
//	localmult *= x;
//
//	cout << x << " is a val of rank " << rank << "\n";
//}
//MPI_Reduce(&localmult, &getdata, 1, MPI_FLOAT, MPI_SUM, 0,
//	MPI_COMM_WORLD);
//
//// Print the result
//if (rank == 0) {
//	printf(" scalar is = %f\n", getdata);
//}

// task13 -n 1
//#define  LEN   4 
//
//	float val[LEN] = {5,1,3,4};        /* local array of values */
//int count = 4;             /* local number of values */
//int myrank, minrank, minindex;
//float minval;
//
//struct {
//	float value;
//	int   index;
//} in, out;
//
///* local minloc */
//in.value = val[0];
//in.index = 0;
//for (int i = 1; i < count; i++)
//	if (in.value > val[i]) {
//		in.value = val[i];
//		in.index = i;
//	}
//
///* global minloc */
//MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
//in.index = myrank * LEN + in.index;
//MPI_Reduce(&in, &out, 1, MPI_FLOAT_INT, MPI_MINLOC, 0, MPI_COMM_WORLD);
///* At this point, the answer resides on process root
// */
//if (myrank == 0) {
//	/* read answer out
//	 */
//	minval = out.value;
//	minrank = out.index / LEN;
//	minindex = out.index % LEN;
//	cout << minval << " " << minindex << "\n";
//}
// task14 -n 2
//#define  LEN   4 
//
//	float val[LEN] = {5,1,3,4};        /* local array of values */
//int count = 4;             /* local number of values */
//int myrank, minrank, minindex;
//float minval;
//vector<float> receiver(2);
//struct {
//	float value;
//	int   index;
//} in, out;
//float max = 0;
//MPI_Scatter(&val, 2, MPI_FLOAT, receiver.data(),
//	2, MPI_FLOAT, 0, MPI_COMM_WORLD);
///* local minloc */
//in.value = val[0];
//in.index = 0;
//float sum = 0;
//for_each(receiver.begin(), receiver.end(), [&sum](float x) { sum += x; });
//
///* global minloc */
//MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
//in.index = myrank * LEN + in.index;
//MPI_Reduce(&sum, &max, 1, MPI_FLOAT, MPI_MAX, 0, MPI_COMM_WORLD);
///* At this point, the answer resides on process root
// */
//if (myrank == 0) {
//	cout << max << " is max. Norm";
//}
//task15 -n 2

//#define  LEN   8 
//
//float val[LEN] = {1,1,2,2,1,1,2,2};        /* local array of values */
//vector<float> result(LEN/2, 0);      /* local array of values */
//int count = 8;             /* local number of values */
//int myrank, minrank, minindex;
//float minval;
//vector<float> receiver(4);
//struct {
//	float value;
//	int   index;
//} in, out;
//
//float max = 0;
//MPI_Scatter(&val, 4, MPI_FLOAT, receiver.data(),
//	4, MPI_FLOAT, 0, MPI_COMM_WORLD);
///* local minloc */
//for (int i = 0; i < 2; i++)
//	receiver.at(i) = receiver[i] * receiver[i + 2];
//MPI_Gather(receiver.data(), 2, MPI_INT, result.data(), 2, MPI_INT, 0, MPI_COMM_WORLD);
//
//if (rank == 0) {
//	for_each(result.cbegin(), result.cend(), [](const int x) {cout << x << " val \n"; });
//}


// task 16 -n 2
//
//#define  LEN   8 
//
//float val[LEN] = { 1,1,1,1 };        /* local array of values */
//vector<float> vec(2,2);
//vector<float> result(vec.size());      /* local array of values */
//int count = 8;             /* local number of values */
//int myrank, minrank, minindex;
//float minval;
//vector<float> receiver(4);
//struct {
//	float value;
//	int   index;
//} in, out;
//
//float max = 0;
//MPI_Scatter(&val, 2, MPI_FLOAT, receiver.data(),
//	2, MPI_FLOAT, 0, MPI_COMM_WORLD);
//MPI_Bcast(vec.data(), 2, MPI_FLOAT, 0, MPI_COMM_WORLD);
///* local minloc */
//for (int i = 0; i < vec.size()/2; i++)
//	vec.at(i) = receiver[i]* vec[i] + receiver[i+1]*vec[i+1];
//		
//
//MPI_Gather(vec.data(), 1, MPI_FLOAT, result.data(), 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
//
//if (rank == 0) {
//	for_each(result.cbegin(), result.cend(), [](const int x) {cout << x << " val \n"; });
//}


// task 17 -n 2

//#define  LEN   8 
//
//float val[LEN] = { 1,1,1,1 };        /* local array of values */
//vector<float> vec(2, 2);
//vector<float> result;      /* local array of values */
//int count = 8;             /* local number of values */
//int myrank, minrank, minindex;
//float minval;
//vector<float> receiver(4);
//struct {
//	float value;
//	int   index;
//} in, out;
//
//float max = 0;
//MPI_Scatter(&val, 2, MPI_FLOAT, receiver.data(),
//	2, MPI_FLOAT, 0, MPI_COMM_WORLD);
//MPI_Bcast(vec.data(), 2, MPI_FLOAT, 0, MPI_COMM_WORLD);
///* local minloc */
////for (int i = 0; i < vec.size() / 2; i++)
////	vec.at(i) = receiver[i] * vec[i] + receiver[i + 1] * vec[i + 1];
//
//if (rank == 0)result.push_back(vec[0]);
////MPI_Gather(vec.data(), 1, MPI_FLOAT, result.data(), 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
//if( rank != 0 )
//MPI_Send(vec.data(), 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
//if (rank == 0) {
//
//	while (result.size() != 2) {
//		vector<float> buf(1);
//		cout << result.size() << "current size! \n";
//		for (int k = 1; k < 2; k++) {
//
//			MPI_Recv(buf.data(), 1, MPI_FLOAT, k, 0,
//				MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//			result.push_back(buf.at(0));
//		}
//	}
//	for_each(result.cbegin(), result.cend(), [](const int x) {cout << x << " val \n"; });
//}
//

//task 18
//#define  LEN   4 // -n 4
//
//constexpr uint64_t sizeRaw = 5;
//constexpr uint64_t sizeCol = 5;
//static int counter = 0;
//vector<int> vecOfMatrix;
//vector<vector<int>> matrix(sizeRaw);
//for (int i = 0; i < sizeRaw; i++)
//	matrix[i].resize(sizeCol);
//std::for_each(matrix.begin(), matrix.end(),
//	[&vecOfMatrix, sizeRaw, sizeCol](std::vector<int> &vec) {
//	vec.resize(sizeCol);
//	std::for_each(vec.begin(), vec.end(), [&vecOfMatrix, sizeRaw, sizeCol](int& x) {
//		//x = 1+rand()%sizeCol;
//
//		x = counter;
//		counter++;
//		//vecOfMatrix.push_back(x);
//	});
//});
//
//if (rank == 0)
////for_each(vecOfMatrix.cbegin(), vecOfMatrix.cend(), [](const int x) {cout << x << " val " << "\n"; });
//
//cout << "hello \n";
//vector<int> buffer;
//int n = 0;
//int n_halfDivider = 0;
//int m = 0;
//int m_halfDivider = 0;
//int isEvenRaw = 0; // 0 = not even
//int isEvenCol = 0;
//if (sizeCol % 2 == 0) {
//	isEvenCol = 1;
//	m_halfDivider = sizeCol / 2;
//}
//else
//{
//	m_halfDivider = sizeCol / 2 + 1;
//}
//
//if (sizeRaw % 2 == 0) {
//	isEvenRaw = 1;
//	n_halfDivider = sizeRaw / 2;
//}
//else
//{
//	n_halfDivider = sizeRaw / 2 + 1;
//}
//
//cout << "hello \n";
//vector<int > vectorOfSize;
//for (int i = 0; i < 4; i++)
//	switch (i)
//	{
//	case 0:
//		n = 0;
//		m = 0;
//		for (int i = n; i < n_halfDivider; i++)
//{
//	for (int j = m; j < m_halfDivider; j++)
//	{
//		
//		vecOfMatrix.push_back(matrix.at(i).at(j));
//	}
//}
////cout << vecOfMatrix.size() << " size 0 \n";
//		vectorOfSize.push_back(n_halfDivider*m_halfDivider);
//		break;
//	case 1:
//		n = 0;
//		m = m_halfDivider;
//		for (int i = n; i < n_halfDivider; i++)
//	{
//		for (int j = m; j < sizeCol; j++)
//		{
//			vecOfMatrix.push_back(matrix.at(i).at(j));
//		}
//	}
//		vectorOfSize.push_back(n_halfDivider*(sizeCol - m_halfDivider));
//		break;
//	case 2:
//		n = n_halfDivider;
//		m = 0;
//		for (int i = n; i < sizeRaw; i++)
//	{
//		for (int j = m; j < m_halfDivider; j++)
//		{
//			vecOfMatrix.push_back(matrix.at(i).at(j));
//		}
//	}
//		vectorOfSize.push_back((sizeRaw - n_halfDivider)*m_halfDivider);
//		break;
//	case 3:
//		n = n_halfDivider;
//		m = m_halfDivider;
//
//		for (int i = n; i < sizeRaw; i++)
//		{
//			for (int j = m; j < sizeCol; j++)
//			{
//				vecOfMatrix.push_back(matrix.at(i).at(j));
//			}
//		}
//		vectorOfSize.push_back((sizeRaw - n_halfDivider)*(sizeCol - m_halfDivider));
//		break;
//	default:
//		break;
//	}
//
//int isEvenMatrix = 0;
//
////vector<float> receiver(1);
//if (rank == 0) {
//	if (std::adjacent_find(vectorOfSize.begin(), vectorOfSize.end(), std::not_equal_to<>()) == vectorOfSize.end())
//	{
//		isEvenMatrix = 1;
//		std::cout << "All elements are equal each other" << std::endl;
//	}
//	cout << vecOfMatrix.size() << "vec of matrix size \n";
//	cout << "is even mat: " << isEvenMatrix << " \n";
//	cout << "vecOfsize has size: " << vectorOfSize.size() << "\n";
//	for_each(vectorOfSize.cbegin(), vectorOfSize.cend(), [rank](int x) {cout << x << " size " << "\n"; });
//	for_each(vecOfMatrix.cbegin(), vecOfMatrix.cend(), [rank](int x) {cout << x << " value " << "\n"; });
//
//
//
//}
//
//vector<int> vectorOfProcesses(sizeRaw*sizeCol / 2, -1);
//vector<int> disp;
//disp.push_back(0);
//for (int i = 1; i < vectorOfSize.size(); i++)
//{
//	int to_display = 0;
//	for (int j = 0; j < i; j++)
//	{
//		to_display += vectorOfSize.at(j);
//	}
//	disp.push_back(to_display);
//}
//if (rank == 0)
//for_each(disp.cbegin(), disp.cend(), [rank](int x) {cout << x << " disp " << "\n"; });
//
//
////if (sizeRaw % 2 == 0 && sizeCol % 2 == 0)
//MPI_Scatterv(vecOfMatrix.data(), vectorOfSize.data(), disp.data(), MPI_INT, vectorOfProcesses.data(),
//	sizeRaw*sizeCol / 2, MPI_INT, 0, MPI_COMM_WORLD);
//
//for_each(vectorOfProcesses.cbegin(), vectorOfProcesses.cend(), [rank](int x) {cout << x << " val of rank " << rank << "\n"; });
//


//task 19-- -n any num

//int someNum = rank;
//int sum;
//MPI_Reduce(&someNum, &sum, 1, MPI_FLOAT, MPI_SUM, 0,
//	MPI_COMM_WORLD);
//
//MPI_Bcast(&sum, 1, MPI_INT, 0, MPI_COMM_WORLD);
//
//
//	cout << "rank " << rank << " has received a sum: " <<  sum << '\n' ;
//

//
//task 20-- -n 3
//MPI_Datatype matrix;
//MPI_Datatype matrix2;
////mpi_datatype matrix2;
//MPI_Status status;
//
//
//
//MPI_Type_vector(4, 8, 16, MPI_DOUBLE, &matrix);
//MPI_Type_vector(1, 32, 1, MPI_DOUBLE, &matrix2);
//MPI_Type_commit(&matrix);
//MPI_Type_commit(&matrix2);
//
////vector<vector<double>> u;
////u.push_back(vector<double>());
////u.push_back(vector<double>());
////u.push_back(vector<double>());
////u.push_back(vector<double>());
////u.push_back(vector<double>());
////u.push_back(vector<double>());
////u.push_back(vector<double>());
////u.push_back(vector<double>());
////std::array<double, 64> u2;
//if (rank == 0) {
//	double u2[64];
//	vector<double> odd;
//	// int counter = 0;
//	//std::for_each(u.begin(), u.end(),
//	//	[&u2, &counter](std::vector<double> &vec) {
//	//	for_each(vec.begin(), vec.end(),
//	//		[&vec, &u2, &counter] {
//	//		vec.push_back(counter);
//	//		u2.push_back(counter);
//	//		counter++;
//	//	});
//	//});
//	cout << rank << "cur rank \n";
//	//if (rank == 0)
//	//if (rank == 0) {
//
//	for (int i = 0; i < 64; i++)
//	{
//		u2[i] = i;
//	}
//
//	int counter = 0;
//	for (int i = 0; i < 8; i++)
//	{
//		for (int u = counter * 8; u < (counter + 1) * 8; u++)
//		{
//			if (counter % 2 == 1)
//				odd.push_back(u);
//		}
//		counter++;
//	}
//
//
//	MPI_Send(u2, 1, matrix, 1, 0, MPI_COMM_WORLD);
//
//
//	MPI_Send(odd.data(), 1, matrix2, 2, 0, MPI_COMM_WORLD);
//
//
//
//
//
//}
//
// if (rank == 1) {
//
//
//	 double* recv_buff2 = new double[250];
//	 for (int i = 0; i < 250; i++)
//	 {
//		 recv_buff2[i] = 0;
//	 }
//
//		MPI_Recv(recv_buff2, 1, matrix, 0, 0, MPI_COMM_WORLD, &status);
//			//recv_buff = new double*[2];
//		for (int i = 0; i < 170; i++)
//		{
//			cout << recv_buff2[i];
//		}
//
//		cout << "first've finished \n";
//			
//}
// if (rank == 2) {
//	 double* recv_buff1 = new double[250];
//	 for (int i = 0; i < 250; i++)
//	 {
//		 recv_buff1[i] = 0;
//	 }
//
//	 MPI_Recv(recv_buff1, 1, matrix, 0, 0, MPI_COMM_WORLD, &status);
//	 //recv_buff = new double*[2];
//	 for (int i = 0; i < 170; i++)
//	 {
//		 cout << recv_buff1[i];
//	 }
//
//	 cout << "secon've finished \n";
//
// }
	
//task 21--  du mus alle Felhen ignorieren -n 4
//
//vector<double> u2;
//	for (int i = 0; i < 64; i++)
//	{
//
//		u2.push_back(i);
//
//	}
//
//struct MyType {
//	double * star = new double[64];
//
//};
//
//
//
//struct MyType my;
//if(rank == 0 )
//for (int i = 0; i < 64; i++)
//{
//
//	my.star[i] = i;
//
//}
//else
//for (int i = 0; i < 64; i++)
//{
//
//	my.star[i] = 0;
//
//}
//int blocklengths[2] = { 8, 8};
//
//
//MPI_Datatype types[2] = { MPI_DOUBLE, MPI_DOUBLE };
//MPI_Aint address[2];
//MPI_Aint disp[3];
//MPI_Datatype newtype;
//
//
//MPI_Get_address(&my, &address[0]);
//MPI_Get_address(&(my.star[8]), &address[1]);
//MPI_Get_address(&(my.star[40]), &address[2]);
//disp[0] = address[1] - address[0];
//disp[1] = address[2] - address[0];
//MPI_Type_create_struct(2, blocklengths, disp, types, &newtype);
//MPI_Type_commit(&newtype);
//
//if (rank == 0) {
//
//
//	for (int i = 1; i <= 3; i++) {
//		MPI_Get_address(&my, &address[0]);
//		MPI_Get_address(&(my.star[i*8]), &address[1]);
//		MPI_Get_address(&(my.star[40 + (i-1) * 8]), &address[2]);
//		disp[0] = address[1] - address[0];
//		disp[1] = address[2] - address[0];
//		MPI_Type_create_struct(2, blocklengths, disp, types, &newtype);
//		MPI_Type_commit(&newtype);
//		MPI_Send(&my, 1, newtype,i, 0, MPI_COMM_WORLD);
//
//
//	}
//}
//else if (rank == 1 || rank == 2 || rank == 3) {
//	MPI_Status status;
//	MPI_Recv(&my, 1, newtype, 0, 0, MPI_COMM_WORLD, &status);
//	//printf("recv rank=1 c=%c f=%f\n", my.c[0], my.f);
//	cout << rank << " rank begins receiving \n";
//	for (int i = 0; i < 64; i++)
//	{
//
//		cout << my.star[i];
//
//	}
//}
//
//
//MPI_Type_free(&newtype);



//task 22-- -n any num

//
//
//int blocklengths[2] = { 2, 1 };
//
//
//MPI_Datatype types[2] = { MPI_DOUBLE, MPI_DOUBLE };
//MPI_Aint address[2];
//
//MPI_Datatype newtype;
//int stride[2] = { 0, 3 };
//
//MPI_Type_indexed(2, blocklengths, stride, MPI_DOUBLE, &newtype);
//MPI_Type_commit(&newtype);
//
//vector<double> uptriangularmatrix;
//if (rank == 0) {
//	
//	uptriangularmatrix.push_back(1);
//	uptriangularmatrix.push_back(2);
//	uptriangularmatrix.push_back(3);
//	uptriangularmatrix.push_back(4);
//}
//else
//{
//	uptriangularmatrix.push_back(0);
//	uptriangularmatrix.push_back(0);
//	uptriangularmatrix.push_back(0);
//	uptriangularmatrix.push_back(0);
//}
//MPI_Bcast(uptriangularmatrix.data(), 1, newtype, 0, MPI_COMM_WORLD);
//
//
//
//
//cout << "rank " << rank << " has received some mat: ";
//for (double d : uptriangularmatrix) {
//	cout << d;
//}
//
//
//
//
//MPI_Type_free(&newtype);


//task 23-- -n 2
//int inteGER[10] = { 0,0 };
//double dobby[8] = { 0,0 };
//int inteGERB[50] = { 0,0 };
//double dobbyB[16] = { 0,0 };
//char buf[1000];
//if (rank == 0) {
//	for (int i = 0; i < 10; i++)
//	{
//
//		inteGER[i] = i;
//
//	}for (int i = 0; i < 8; i++)
//	{
//
//		dobby[i] = i;
//
//	}
//}
//
//int position = 0;
//if (rank == 0) {
//	MPI_Pack(dobby, 8, MPI_DOUBLE, buf, 1000, &position, MPI_COMM_WORLD);
//	MPI_Pack(inteGER, 10, MPI_INT, buf, 1000, &position, MPI_COMM_WORLD);
//	MPI_Bcast(buf, 1000, MPI_PACKED, 0, MPI_COMM_WORLD);
	//MPI_Send(buffer, position, MPI_PACKED, 1, 100, MPI_COMM_WORLD);
//}
//
//else {
//	MPI_Bcast(buf, 1000, MPI_PACKED, 0, MPI_COMM_WORLD);
//	cout << rank << "rank\n";
//	//MPI_Bcast(&buf, 100, MPI_PACKED, 0, MPI_COMM_WORLD);
//	position = 0;
//	MPI_Unpack(buf, 1000, &position, dobby, 8, MPI_DOUBLE, MPI_COMM_WORLD);
//	MPI_Unpack(buf, 1000, &position, inteGER, 10, MPI_INT, MPI_COMM_WORLD);
//	cout << rank << " rank\n";
//	cout << "dobby \n";
//	for (double d : dobby) {
//		cout << d;
//	}
//	cout << "\n ints \n";
//	for (double d : inteGER) {
//		cout << d;
//	}
//
//	//cout << "\n" << &MPI_Comm_group << endl;
//}



//task 24-- -n 15
//int errs = 0, toterr;
//MPI_Group basegroup;
//MPI_Group g1, g2, g3, g4, g5, g6, g7, g8, g9, g10;
//MPI_Group g3a, g3b;
//MPI_Comm comm, newcomm, splitcomm, dupcomm;
//int i, grp_rank, grp_size, result;
//int nranks, *ranks, *ranks_out;
//int range[1][3];
//int worldrank;
//
//MPI_Comm_rank(MPI_COMM_WORLD, &worldrank);
//comm = MPI_COMM_WORLD;
//MPI_Comm_group(comm, &basegroup); // world group
////MPI_Comm_rank(comm, &rank);
////MPI_Comm_size(comm, &size);
//
//ranks = new int[size];
//for (int i = 0; i < size; i++)
//{
//	ranks[i] = i;
//}
////cout << size << " " << rank << " world\n";
//ranks[0] = 9;
//ranks[1] = 8;
//ranks[2] = 6;
//ranks[3] = 3;
//ranks[4] = 1;
//
//MPI_Group_incl(basegroup, 5, ranks, &g1);
////ranks[1] = (rank + size - 1) % size;
//MPI_Comm worldcom, newcom;
//MPI_Group world_group;
////MPI_Group_size(g1, &size);
////MPI_Group_rank(g1, &rank);
//
////MPI_Comm_dup(MPI_COMM_WORLD, &worldcom);
////int rank1 = -1;
////cout << size << " " << rank << " newcom\n";
//MPI_Comm_group(MPI_COMM_WORLD, &world_group);
//
//MPI_Comm_create(MPI_COMM_WORLD, g1, &newcom);
////MPI_Group_size(MPI_COMM_WORLD, &size);
////MPI_Group_rank(MPI_COMM_WORLD, &rank);
//
////MPI_Comm comm1, comm2, icomm, local;
////cout << "here";
//MPI_Comm local;
//int rleader;
//if (newcom != MPI_COMM_NULL) { local = newcom; rleader = 0; }
//if (MPI_COMM_WORLD != MPI_COMM_NULL) { local = MPI_COMM_WORLD;  rleader = 1;
//}
//
//MPI_Comm icomm;
/////////////////////////////// intercomm part!!!!!!!!!!!!!!!!!!!!!!!!!!!not working ahahahah
//if (newcom != MPI_COMM_NULL) {
//	//MPI_Intercomm_create(newcom, 0, MPI_COMM_WORLD, 0, 0, &icomm);
//
//	cout << "here in new comm";
//	vector<float> vec(8,0);
//	if (rank == 9) {
//		for (int i = 0; i < 8; i++)
//		{
//			vec.at(i) = i;
//		}
//	}
//	MPI_Bcast(vec.data(), 8, MPI_FLOAT, 0, newcom);
//	cout << "rank is " << rank << endl;
//	for (int i = 0; i < 8; i++)
//	{
//		cout << vec.at(i) << " ";
//	}
//	if (rank == 1)
//	{
//		MPI_Send(vec.data(), 8, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
//
//		//MPI_Send(vec.data(), 8, MPI_FLOAT, 0, 0, icomm);
//	}
//
//	//MPI_Comm_rank(newcom, &rank1);
//}
//vector<float> somevec(8, 0);
//if (rank == 0) {
//	MPI_Recv(somevec.data(), 8, MPI_FLOAT, 9, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
//	cout << "rank is " << rank << endl;
//	for (int i = 0; i < 8; i++)
//	{
//		cout << somevec.at(i) << " ";
//	}
//}
//if (MPI_COMM_WORLD != MPI_COMM_NULL) {
//	MPI_Intercomm_create(MPI_COMM_WORLD, 0, MPI_COMM_WORLD, 1, 0, &icomm);
//
//	cout << "here in world comm" << rank;
//	vector<float> somevec(8, 0);
//	MPI_Status status;
	//if (rank == 0) {
	//	MPI_Recv(somevec.data(), 8, MPI_FLOAT, MPI_ANY_SOURCE, MPI_ANY_TAG, icomm, MPI_STATUSES_IGNORE);
	//	cout << "rank is " << rank << endl;
	//	for (int i = 0; i < 8; i++)
	//	{
	//		cout << somevec.at(i) << " ";
	//	}
	//}
//}




//task 25--  -n 12


	//int ranks1[3] = { 0,1,2 };
	//int ranks2[3] = { 3,4,5 };
	//int ranks3[3] = { 6,7,8 };
	//int ranks4[3] = { 9,10, 11};

	//MPI_Group wgroup, group1, group2;
	//MPI_Group group3, group4;
	//MPI_Comm_group(MPI_COMM_WORLD, &wgroup);
	//MPI_Group_incl(wgroup, 3, ranks1, &group1);
	//MPI_Group_incl(wgroup, 3, ranks2, &group2);
	//MPI_Group_incl(wgroup, 3, ranks3, &group3);
	//MPI_Group_incl(wgroup, 3, ranks4, &group4);

	//MPI_Comm comm1, comm2, comm3, comm4, icomm, local;
	//MPI_Comm_create(MPI_COMM_WORLD, group1, &comm1);
	//MPI_Comm_create(MPI_COMM_WORLD, group2, &comm2);
	//MPI_Comm_create(MPI_COMM_WORLD, group3, &comm3);
	//MPI_Comm_create(MPI_COMM_WORLD, group4, &comm4);

	//int rank1 = -1;
	//int rank2 = -1;
	//int rank3 = -1;
	//int rank4 = -1;
	//if (comm1 != MPI_COMM_NULL) MPI_Comm_rank(comm1, &rank1);
	//if (comm2 != MPI_COMM_NULL) MPI_Comm_rank(comm2, &rank2);
	//if (comm3 != MPI_COMM_NULL) MPI_Comm_rank(comm3, &rank3);
	//if (comm4 != MPI_COMM_NULL) MPI_Comm_rank(comm4, &rank4);
	//printf("rank1=%d, rank2=%d,rank3=%d,rank4=%d, rank=%d\n", rank1, rank2, rank3, rank4, rank);


	//int rlead;
	//if (comm1 != MPI_COMM_NULL) { local = comm1; rlead = 3; }
	//if (comm2 != MPI_COMM_NULL) { local = comm2; rlead = 0; }
	//if (comm3 != MPI_COMM_NULL) { local = comm3; rlead = 9; }
	//if (comm4 != MPI_COMM_NULL) { local = comm4; rlead = 6; }
	//int tag = 777;
	//MPI_Intercomm_create(local, 0, MPI_COMM_WORLD, rlead, tag, &icomm);

	//vector<int> a(3,0);
	//if (comm1 != MPI_COMM_NULL) {
	//	vector<int> vec(1, 1);
	//	vector<int> result(3);

	//	MPI_Gather(vec.data(), 1, MPI_INT, result.data(), 1, MPI_INT, 0, comm1);

	//	if (rank == 0) {
	//		for_each(result.cbegin(), result.cend(), [](const int x) {cout << x << " val \n"; });
	//	}

	//	if (rank1 == 0) {
	//		 MPI_Send(result.data(), 3, MPI_INT, 0, 12, icomm);
	//	}

	//}
	//if (comm2 != MPI_COMM_NULL) {
	//	vector<int> vec(1, 2);
	//	vector<int> result(3);

	//	MPI_Gather(vec.data(), 1, MPI_INT, result.data(), 1, MPI_INT, 0, comm2);

	//	if (rank2 == 0) {
	//		for_each(result.cbegin(), result.cend(), [](const int x) {cout << x << " val \n"; });
	//		MPI_Recv(a.data(), 3, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, icomm, MPI_STATUSES_IGNORE); printf("a=%d\n", a);
	//		for_each(a.cbegin(), a.cend(), [](const int x) {cout << x << " received. \n";
	//	});
	//		
	//	}
	//}
	//if (comm3 != MPI_COMM_NULL) {
	//	vector<int> vec(1, 3);
	//	vector<int> result(3);

	//	MPI_Gather(vec.data(), 1, MPI_INT, result.data(), 1, MPI_INT, 0, comm3);


	//	if (rank3 == 0) {
	//		for_each(result.cbegin(), result.cend(), [](const int x) {cout << x << " val \n"; });
	//		 MPI_Send(result.data(), 3, MPI_INT, 0, 12, icomm);
	//	}
	//}

	//if (comm4 != MPI_COMM_NULL) {
	//	vector<int> vec(1, 4);
	//	vector<int> result(3);

	//	MPI_Gather(vec.data(), 1, MPI_INT, result.data(), 1, MPI_INT, 0, comm4);


	//	if (rank4 == 0) {
	//		for_each(result.cbegin(), result.cend(), [](const int x) {cout << x << " val \n"; });
	//		MPI_Recv(a.data(), 3, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, icomm, MPI_STATUSES_IGNORE); printf("a=%d\n", a);
	//		for_each(a.cbegin(), a.cend(), [](const int x) {cout << x << " received. \n"; });

	//	}
	//}

	//
	//

	//if (comm1 != MPI_COMM_NULL)cout << rank1 << "rank1";
	//if (comm2 != MPI_COMM_NULL) cout << rank2 << "rank2";
	//if (comm3 != MPI_COMM_NULL) cout << rank3 << "rank3";
	//if (comm4 != MPI_COMM_NULL) cout << rank4 << "rank4";


	//if (comm1 != MPI_COMM_NULL) MPI_Comm_free(&comm1);
	//if (comm2 != MPI_COMM_NULL) MPI_Comm_free(&comm2);





//task 26


//#define  LEN   4
//
//float val[LEN] = { 1,1,1,1 };        /* local array of values */
//vector<float> vec(2,2);
//vector<float> result(vec.size());      /* local array of values */
//int count = 8;             /* local number of values */
//int myrank, minrank, minindex;
//float minval;
//vector<float> receiver(2);
//struct {
//	float value;
//	int   index;
//} in, out;
//
//float avr = 0;
//MPI_Scatter(&val, 2, MPI_FLOAT, receiver.data(),
//	2, MPI_FLOAT, 0, MPI_COMM_WORLD);
////MPI_Bcast(vec.data(), 2, MPI_FLOAT, 0, MPI_COMM_WORLD);
///* local minloc */
//for (int i = 0; i < vec.size()/2; i++)
//	vec.at(0) = receiver[i]+ receiver[i+1];
//
//MPI_Gather(vec.data(), 1, MPI_FLOAT, result.data(), 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
//
//if (rank == 0) {
//	int avg = 0;
//	for_each(result.begin(), result.end(), [&avg](const int x) {
//		avg += x;
//		cout << x << " val \n"; });
//
//	cout << "avg is " << avg /LEN;
//}
//

//task 27

//#define  LEN   4
//
//float val[LEN] = { 1,1,1,1 };        /* local array of values */
//vector<float> vec(2, 2);
//vector<float> result(vec.size());      /* local array of values */
//int count = 8;             /* local number of values */
//int myrank, minrank, minindex;
//float minval;
//vector<float> receiver(2);
//struct {
//	float value;
//	int   index;
//} in, out;
//
//float avr = 0;
//MPI_Scatter(&val, 2, MPI_FLOAT, receiver.data(),
//	2, MPI_FLOAT, 0, MPI_COMM_WORLD);
////MPI_Bcast(vec.data(), 2, MPI_FLOAT, 0, MPI_COMM_WORLD);
///* local minloc */
//for (int i = 0; i < vec.size() / 2; i++)
//	vec.at(0) = receiver[i] + receiver[i + 1];
//
//MPI_Gather(vec.data(), 1, MPI_FLOAT, result.data(), 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
//
//if (rank == 0) {
//	int avg = 0;
//	for_each(result.begin(), result.end(), [&avg](const int x) {
//		avg += x;
//		cout << x << " val \n"; });
//			
//	cout << "sum is " << avg;
//}
//task 28

//
//std::default_random_engine generator;
//std::uniform_int_distribution<int> distribution(1, 30000);
//
//vector<double> result(2);
//	int Npoints = (int)1E3;
//	int Nincircle = 0;
//	srand(time(0));
//	MPI_Bcast(&Npoints, 1, MPI_INT, 0, MPI_COMM_WORLD);
//
//	for (int i = 0; i < Npoints; i++)
//	{
//		double R = 1.0,
//			x = (distribution(generator) % (4 * Npoints) - 2 * Npoints) / (2.0*Npoints),
//			y = (distribution(generator) % (4 * Npoints) - 2 * Npoints) / (2.0*Npoints);
//		if
//			((x*x + y * y) < R*R)
//			Nincircle++;
//	}
//
//	double pi = Nincircle * 4.0 / Npoints;
//	cout << pi << " val pi of rank " << rank << "\n";
//	MPI_Gather(&pi, 1, MPI_DOUBLE, result.data(), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
//
//	if (rank == 0)
//	{
//		for_each(result.begin(), result.end(), [rank](const double x) {
//		cout << x << " val pi of rank " << rank <<"\n"; });
//		cout << accumulate(result.begin(), result.end(), 0.0) / result.size() << " final pi ";
//	}


//task 29
//
	
//vector<int > forSort = {1,2,3,4,9,8,7,6,54,1};
//vector<int> receiver(forSort.size() / 2);
//vector<int> result(forSort.size());
//vector<int> resultOfResult;
//MPI_Scatter(forSort.data(), 5, MPI_INT, receiver.data(),
//	5, MPI_INT, 0, MPI_COMM_WORLD);
//
//		for (int i = 0; i < receiver.size(); i++) {
//			// (i % 2) ? 0 : 1 возвращает 1, если i четное, 0, если i не четное
//			for (int j = (i % 2) ? 0 : 1; j < receiver.size() - 1; j += 2) {
//				if (receiver[j] > receiver[j + 1]) {
//					std::swap(receiver[j], receiver[j + 1]);
//				}
//			}
//		}
//		MPI_Gather(receiver.data(), 5, MPI_INT, result.data(), 5, MPI_INT, 0, MPI_COMM_WORLD);
//		if (rank == 0) {
//			for_each(result.begin(), result.end(), [rank](const double x) {
//				cout << x << " val of rank " << rank << "\n"; });
//		
//			cout <<"here \n";
//	
//		int k = 0;
//		int z = result.size() / 2;
//		for (int i = 0; i < result.size(); i++)
//		{
//			if (result[k] < result[z])
//			{
//				resultOfResult.push_back(result[k]);
//				k++;
//			}
//			else {
//				resultOfResult.push_back(result[z]);
//				z++;
//			}
//		}
//		for_each(resultOfResult.begin(), resultOfResult.end(), [rank](const double x) {
//			cout << x << " val of rank " << rank << "\n"; });
//		}

//task 30 -n 2

//vector<int > rand_nums;
//rand_nums.push_back(4);
//rand_nums.push_back(6);
//rand_nums.push_back(6);
//rand_nums.push_back(12);
//
//vector<int > receiver(2,0);
//// Scatter the random numbers to all processes
//MPI_Scatter(rand_nums.data(), 2, MPI_INT, receiver.data(),
//	2, MPI_INT, 0, MPI_COMM_WORLD);
//	double a, b, eps;
//	double s1, s;
//	int n = 1; //начальное число шагов
//	//cout << "Введите левую границу интегрирования a = ";
//	//cin >> a;
//	a = receiver.at(0);
//	//cout << "\nВведите правую границу интегрирования b = ";
//	//cin >> b;
//	b = receiver.at(1);
//	//cout << "\nВведите требуемую точность eps = ";
//	//cin >> eps;
//	eps = 0.0001;
//
//	cout <<a << " " << b << '\n' << rank << "rank \n";
//		s1 = simpson_integral(f, a, b, n); //первое приближение для интеграла
//		do {
//			s = s1;     //второе приближение
//			n = 2 * n;  //увеличение числа шагов в два раза,
//						//т.е. уменьшение значения шага в два раза
//			s1 = simpson_integral(f, a, b, n);
//		} while (fabs(s1 - s) > eps);  //сравнение приближений с заданной точностью
//		cout << "\nintegral = " << s1 << " of rank " << rank << endl;
//
//	
//
//	double getdata;
//	MPI_Reduce(&s1, &getdata, 1, MPI_DOUBLE, MPI_SUM, 0,
//		MPI_COMM_WORLD);
//
//	if (rank == 0) {
//		cout << getdata << " sum result \n";
//	}
//



	MPI_Finalize();
}
		//                  [](std::vector<int> &vec){
   /* std::cout << "Hello World!\n"; */















// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
