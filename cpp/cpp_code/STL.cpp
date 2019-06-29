//
// Created by X on 29.06.2019.
//

#include <iostream>
#include <algorithm>
#include "STL.h"

double const Object::getWeight() { return weight;}

bool isPositive(int &x){
    return x >= 0;
};

void countPositiveNumbers(vector<int> &vec){
    cout<< count_if(vec.begin(), vec.end(), isPositive) << " positive numbers." << endl;
}

void countHeavyObjects(std::vector<Object> &vec){
    cout << count_if(vec.begin(), vec.end(), [](Object &o){
        return o.getWeight() >= 100;
    })   << " heavy objects." << endl;
}

