//
// Created by X on 29.06.2019.
//

#ifndef CPP_CODE_MULTITHREADING_H
#define CPP_CODE_MULTITHREADING_H
#include "STL.h"
#include <thread>
#include <chrono>
#include <iostream>

/*
unique_lock<mutex> m(ntx, defer_lock);
lock
unlock
*/

// int globa = 5;


void createThreadWillClassMethod();
void useMutex();
void justPrinting(char ch);
void callDeadLock();
void recursive_mutex_f(int a);

#endif //CPP_CODE_MULTITHREADING_H
