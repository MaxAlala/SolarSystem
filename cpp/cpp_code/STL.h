#include <utility>

#include <utility>

//
// Created by X on 29.06.2019.
//

#ifndef CPP_CODE_STL_H
#define CPP_CODE_STL_H
#include <vector>
#include <string>
using namespace std;

class Object{
private:
    string name;
    double weight;

public:
    double const getWeight();
    explicit Object(string name, int weight):name(std::move(name)), weight(weight){}
};

bool isPositive(int &x);
void countPositiveNumbers(std::vector<int> &vec);
void countHeavyObjects(std::vector<Object> &vec);
#endif //CPP_CODE_STL_H
