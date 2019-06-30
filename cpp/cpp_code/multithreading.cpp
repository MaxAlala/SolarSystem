//
// Created by X on 29.06.2019.
//

#include "multithreading.h"
#include <mutex>
#include "STL.h"
    mutex m1;
    mutex m2;
    void print1(){
        m1.lock();
        this_thread::sleep_for(chrono::milliseconds(1));
        m2.lock();
        for(int i = 0; i < 5; i++){
            this_thread::sleep_for(chrono::milliseconds(500));
            cout << 'A' << "\n";
        }
        m1.unlock();
        m2.unlock();
    }
    void print2(){
        m2.lock();
        this_thread::sleep_for(chrono::milliseconds(1));
        m1.lock();
        for(int i = 0; i < 5; i++){
            this_thread::sleep_for(chrono::milliseconds(500));
            cout << 'A' << "\n";
        }
        m1.unlock();
        m2.unlock();
    }

void callDeadLock(){
    thread th1(print1);
    thread th2(print2);

    th1.join();
    th2.join();
}
void recursive_mutex_f(int a){
        recursive_mutex m1;
        m1.lock();
        cout << a << " ";

        this_thread::sleep_for(chrono::milliseconds(300));
        if(a <= 1){
            cout << endl;
            m1.unlock();
            return;
        }

        a--;
    recursive_mutex_f(a);
        m1.unlock();
    }


void createThreadWillClassMethod(){
    Object o("Daria", 60);
    thread th(&Object::doAction, o);
    for(int i = 0; i < 10; i++){
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << i << "MAIN" << " " << "THREAD" << endl;
    }
    th.join();
}

void justPrinting(char ch){
    mutex mtx;
    mtx.lock();
//    lock_guard<mutex> guard(mtx);
    for(int i = 0; i < 5; i++){
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << ch << "\n";
    }
    mtx.unlock();
}

void useMutex(){
    thread th(justPrinting, '*');
    thread th2(justPrinting, '#');
    th.join();
    th2.join();
}

