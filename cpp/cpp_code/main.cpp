#include <iostream>
#include <list>
#include <vector>
#include <thread>
#include <chrono>
#include <functional>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "multithreading.h"
#include "features.h"
#include "List.h"
#include "STL.h"
#include "MyString.h"
//extern int globa;
using namespace std;
class A{
private:
    int priv = 1999;
public:
    int x = 10;
    int y = 5;
protected:
    int prot = 5;
};

class B final: public A{
private:
    int z;

public:
    using A::prot; // cant do it with private
    void  virtual method() final{
        cout << y;
        prot = 555;
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

int main( int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
//
//    B b;
//    b.prot = 55;
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
//    testField();
    ////List
/*    nsOfList::List<Object> list;
    Object o("max", 65);
    Object o1("max1", 65);
    Object o2("max2", 65);
    list.push_back(o);
    list.push_back(o1);
    list.push_back(o2);
    std::cout << list.getSize() << '\n';
    std::cout << list[0] << '\n';
    std::cout << list[1] << '\n';
    std::cout << list[2] << '\n';
    list.removeAt(0);
    std::cout << list.getSize() << '\n';
    std::cout << list[0] << '\n';
    list.insert(o, 1);
    std::cout << list.getSize() << '\n';
    std::cout << list[0] << '\n';
    std::cout << list[1] << '\n';
//    std::cout << list[3] << '\n';
    std::cout << "here " << '\n';
    cout << list.back() << '\n';
//    list.clear();
    cout << list.getSize() << '\n';
    cout << list << '\n';

    nsOfList::List<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    cout << list1 << '\n';
    list1 = list1 + 4;
    cout << list1 << '\n';
    nsOfList::List<int> list2;
    list2.push_back(22);
    cout << (list1 + list2);
    cout << " list 3_1 \n";
    nsOfList::List<int> list3(list1);
    cout << list3;
    list3 = list3 + list1;
    cout << "list3: \n" <<list3;
//    cout << list3 + list2;*/
//// unique ptr
/*
unique_ptr<int> ptr(new int(555));
int *x = ptr.get();
cout << &(*ptr) << '\n';
cout << ptr.get()<< '\n';
cout << x<< '\n';
*/
    RUN_ALL_TESTS();
    return 0;
}