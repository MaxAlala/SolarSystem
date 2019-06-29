#include <iostream>
#include <list>
#include <vector>
#include <thread>
#include <chrono>
#include <functional>
#include "STL.h"
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

    vector<int> vec = {1,2,3,4,-5,-7};
    countPositiveNumbers(vec);
    vector<Object> vec_obj = {
            Object("Greta", 60),
            Object("Ingvar", 110),
            Object("Inga", 65),
            Object("Anton", 111),
    };

    countHeavyObjects(vec_obj);

    ////////////////lambda and function<int(int,int)>
//    auto f2 = [&](int x, int y){ return x+y;};
//    cout << f2(4,6);

//    list<int> l = {2,3,4,5,7,1};
//    auto iter = l.begin();
//    advance(iter,3);
//    l.insert(iter, 999);
//    for(int i: l){
//        cout << i << " ";
//    }
//    thr.join();
//    cout << x;

    return 0;
}