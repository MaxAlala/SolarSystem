//
// Created by X on 29.06.2019.
//

#include <iostream>
#include <algorithm>
#include "STL.h"

void ObjectChild::doAction() {
    cout << "Child does an action! \n";
}

double const Object::getWeight() { return weight;}
string const Object::getName() { return name;}
void Object::doAction(){
    for(int i = 0; i < 10; i++){
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << i << name << " " << weight <<" object does an action. \n";
    }
}

void Object::doAction_uninherited() {
    cout << "Parent \n";

}

double& Object::setWeight() {
    return weight;
}

string& Object::setName() {
    return name;
}

void ObjectChild::doAction_uninherited() {
    cout << "Child \n";
}

bool isPositive(int &x){
    return x >= 0;
};

void printCollection(std::vector<Object> &vec){
    for(auto o: vec){
        o.print();
    }
    cout << "////" << endl;
}

void countPositiveNumbers(vector<int> &vec){
    cout<< count_if(vec.begin(), vec.end(), isPositive) << " positive numbers." << endl;
}

void countHeavyObjects(std::vector<Object> &vec){
    cout << count_if(vec.begin(), vec.end(), [](Object &o){
        return o.getWeight() >= 100;
    })   << " heavy objects." << endl;
}
void sort(std::vector<Object> &vec){
    sort(vec.begin(), vec.end(), [](Object &o, Object &o2){
        return o.getWeight() >= o2.getWeight();
    });
    printCollection(vec);
}

istream & operator>>(istream& ifs, Object &o)
{
    ifs >> o.setName() >> o.setWeight();
    return ifs;
}

ostream & operator<<(ostream& os, Object &o){
    os << o.getName() << " " << o.getWeight();
    return  os;
}

void findByName(std::vector<Object> &vec, const string&& name){
   auto result = find_if(vec.begin(), vec.end(),[&](Object o){
        return name == o.getName();
    });
   if( result == vec.end()){ cout << "cant find." << endl;}
   else { cout << *result; }
}

void copyIfWeightLessThan(std::vector<Object> &vec, std::vector<Object> &result, const int weight){
    copy_if(vec.begin(), vec.end(), back_inserter(result), [&](Object o){
        return weight >= o.getWeight();
    });
    printCollection(result);
}


void removeIfWeightLessThan(std::vector<Object> &vec, const int weight){
    vec.erase(remove_if(vec.begin(), vec.end(), [&](Object o){
        return weight >= o.getWeight();
    }), vec.end());
    printCollection(vec);
}



