#include <utility>

#include <utility>

//
// Created by X on 29.06.2019.
//

#ifndef CPP_CODE_STL_H
#define CPP_CODE_STL_H
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <iostream>
using namespace std;


/*
random_shuffle
unique_copy
for_each
unique
sort(b,e)
equal(b,e,b,e) == bool

auto res = mismatch(b,e,b,e);
if(res.first == end(arr) && res.second == end(arr2))
    cout << "yes";
= returns pair of iterators with bad mismatched values
accumulate(next(b), e, startVal, lambda);

*/
// can define class in .h file = not violation of rule about one definition
// same story about it's methods, they are inside!
class Object{
private:
    string name = "";
    double weight{};

public:
    double const getWeight();
    string const getName();
    string& setName();
    double& setWeight();
    explicit Object(string name, double weight):name(std::move(name)), weight(weight){}
    Object()= default;
    friend bool operator==(Object &o, Object &o1);
    friend bool operator!=(Object &o, Object &o1);
    virtual ~Object()= default;
    void print(){cout << name << " " << weight << endl; };
    void doAction_uninherited();
    virtual void doAction();
};

class ObjectChild: public Object{
private:
public:
    explicit ObjectChild(string name, double weight):Object(std::move(name), weight){}
    void doAction() override;
    void doAction_uninherited();
};

ostream & operator<<(ostream& os, Object &o);
bool isPositive(int &x);
void printCollection(vector<Object>&);
void countPositiveNumbers(std::vector<int> &vec);
void countHeavyObjects(std::vector<Object> &vec);
void sort(std::vector<Object> &vec);
void findByName(std::vector<Object> &vec, const string && name);
void copyIfWeightLessThan(std::vector<Object> &vec, std::vector<Object> &result, const int weight);
void removeIfWeightLessThan(std::vector<Object> &vec, const int weight);

//void sayhello(){// multiple definition error
//    cout << "hello!";
//}
#endif //CPP_CODE_STL_H
