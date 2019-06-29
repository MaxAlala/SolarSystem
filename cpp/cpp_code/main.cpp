#include <iostream>
#include <list>
#include <vector>
#include <thread>
#include <chrono>
#include <functional>
#include "STL.h"
#include "multithreading.h"
#include "features.h"
//extern int globa;
using namespace std;
class A{
private:
public:
    int x = 10;
    int y = 5;
};

class B: public A{
private:
    int z;

    void method(){
        cout << y;
    }
};

istream & operator>>(istream& ifs, B& b)
{
    ifs >> b.x >> b.y;
    return ifs;
}
ostream & operator<<(ostream& ifs, B& b)
{
    ifs << b.x << " " << b.y << endl;
    return ifs;
}

void threadFunction(int &x){
    x = 50000;
}

int main() {
    ////STL
//    vector<int> vec = {1,2,3,4,-5,-7};
//    countPositiveNumbers(vec);
//    vector<Object> vec_obj = {
//            Object("Greta", 60),
//            Object("Ingvar", 110),
//            Object("Inga", 65),
//            Object("Anton", 111),
//    };
//    countHeavyObjects(vec_obj);
//    sort(vec_obj);
//    findByName(vec_obj, "Ingaa");
//    vector<Object> result;
//    copyIfWeightLessThan(vec_obj, result, 80);
//    removeIfWeightLessThan(vec_obj, 80);
    ////multithreading
//    createThreadWillClassMethod();
//    useMutex();
//    callDeadLock();
//    recursive_mutex_f(5);
    ////lambda and function<int(int,int)>


    ////feature place
    testField();
    return 0;
}