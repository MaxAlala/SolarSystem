#include <iostream>
#include <list>
#include <vector>
#include <thread>
#include <chrono>
#include <functional>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "multithreading.h"
//#include "features.h"
#include "List.h"
#include "STL.h"
#include "MyString.h"
#include "feature2.h"
#include <climits>
#include "cppSerializationProgram.h"
#include <boost/regex.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/type_index.hpp>
#include <memory>
#include <map>
//extern int globa;
// some features with class
extern int INTEGER_FROM_FEATURES;
   
class Item {
public:
    std::shared_ptr<Item> s_ptr;
    Item * ptr;
    int x;

    Item(int x) : x(x) {
        std::cout << "Item acquired \n";
    }

    ~Item() {
        std::cout << "item destroyed \n";
        if (ptr) delete ptr;
    }

};
using namespace std;

class A {
private:
    int priv = 1999;
public:
    mutable int x = 10;
    int y = 5;

    void doWork(int) {

    }

    void doWork() const {
        if (true) {
            x = 66 + 5;
        }
    }
protected:
    int prot = 5;
};

class B final : public A {
private:
    int z;

public:
    //    using A::doWork;

    void doWork() {

    }


    using A::prot; // cant do it with private

    void virtual method() final {
        cout << y;
        prot = 555;
    }

    void virtual method() const final {
        cout << y;
        //        prot = 555;
    }
};

istream & operator>>(istream& ifs, B& b) {
    ifs >> b.x >> b.y;
    return ifs;
}

ostream & operator<<(ostream& ifs, B& b) {
    ifs << b.x << " " << b.y << endl;
    return ifs;
}

void threadFunction(int &x) {
    x = 50000;
}

int main(int argc, char* argv[]) {

    /*    Object o;
        Object &o_r = o;
        int z = 10;
        cout << !z << "no Z" << endl;
        int xx = 1234;
        int &xxr = xx;

        int x = (1,024);
        if(x > 0 or x == 20 )cout << "hello! \n";

        B b;
        b.A::doWork(5);// error without using A::doWork*/
    //    int xx = 4;
    //    cout << sizeof xx; //!!!
    //    testing::InitGoogleTest(&argc, argv);
    //
    /*char *char_ar = "qweqwe";
    char *char_ar2 = "q22qweqwerqwer";
    char_ar2 = char_ar;
    cout << char_ar2 << endl;
        int * integer ;
     *integer = 5555;// stop, what?
        double dob = double (5);
        const class B b{};*/
    //    b.prot = 55;
    //    b.method();


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
    /* nsOfList::List<Object> list;
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
     cout << list3 + list2;*/
    //// unique ptr
    /*
    unique_ptr<int> ptr(new int(555));
    int *x = ptr.get();
    cout << &(*ptr) << '\n';
    cout << ptr.get()<< '\n';
    cout << x<< '\n';
     */

    //    RUN_ALL_TESTS();

    //    useSameMemorzNew();
    //    battleField();
    //    planetPopulation();
    //    fstream myfile;
    //    myfile.open ("filename.dat");
    //    myfile << "Writing this to a file.\n";
    //    myfile << "000";
    //    myfile.close();
    //    useTrueTypeRec();
    //
    ////////////////// MyString
    //String string1("Max");
    //String string2("Max2");
    //String string3("Max3");
    //String string4("Max4");
    //    cout << string4.HowMany() << "\n";
    //    string4 = string3;
    //    cout << string4 << "\n";
    //    string1.swap(string2);
    //    cout << string1;

    //    useHtmlBuilder();

    struct // no tag
    {
        int x; // 2 members
        int y;
    } position; // a structure variable

    cout << R"+*("(Who wouldn't?)", she whispered.)+*" << endl;


    cout << R"(Jim "King" Tutt uses "\n" instead of endl.)" << '\n';

    union one4all {
        int int_val;
        long long_val;
        double double_val;
    };

    one4all pail;

    pail.int_val = 15; // store an int
    cout << pail.int_val;
    pail.double_val = 1.38; // store a double, int value is lost
    cout << pail.double_val;

    int* p1, p2; // one ptr one not ptr

    int * pt;
    pt = (int *) 0xB8000000; // types now match


    short tell[10];
    auto ptr = &tell; // pas points to array of 20 shorts

    cout << (int *) "Home of the jolly bytes";
    int x = 2 * x++ * (3 - ++x); // don’t do it except as an experiment


    int cats;
    (cats = 17), 240;

    cats = (17, 240); //240

    //    int y = 0;
    //    for (x = 1; y != x; ++x) // continue while y is not equal to x
    //        for (cin >> x; x == 0; cin >> x) // continue while x is 0
    //
    //            for (char ch = 'a'; ch <= 'z'; ch++)
    //                cout << ch;
    for (int x :{3, 5, 2, 8, 6})
        cout << x << " ";

    char ch = 'q';



    cout << ch++ << " " << ch + 1 << endl;

    //    ar2[r][c] == *(*(ar2 + r) + c) // same thing

    Item * item = new Item(5);
    //    std::shared_ptr<Item> ptr1(item);
    auto ptr1 = std::make_shared<Item>(6);
    (*ptr1).x = 5;
    {

        std::shared_ptr<Item> ptr2(ptr1);
        cout << ptr2.get()->x << "\n";
        std::cout << "Killing one shared pointer\n";
    }
    ptr1->s_ptr = ptr1;

    std::map<int, std::string> spaceMap;
    spaceMap.insert(std::make_pair(3, "asteroid"));
    std::map<int, std::string>::const_iterator it;
    it = spaceMap.begin();

    while (it != spaceMap.end()) {

        std::cout << it->first << " == " << it -> second << "\n";
        it++;
    }


    std::list<int> space_list;
    for (int c = 0; c < 5; c++)
        space_list.push_back(c);

    std::list<int>::const_iterator ci;
    ci = min_element(space_list.begin(), space_list.end());
    std::cout << *ci << " min elem \n";
    ci = max_element(space_list.begin(), space_list.end());
    std::cout << *ci << " max elem \n";

    for (ci = space_list.begin(); ci != space_list.end(); ci++)
        std::cout << *ci << endl;

    std::reverse(space_list.begin(), space_list.end());

    for (ci = space_list.begin(); ci != space_list.end(); ci++)
        std::cout << *ci << endl;

    char *char_ar = new char[7];

    strcpy(char_ar, "hello!"); // plus /0
    std::cout << char_ar;
    delete[] char_ar;

    // for_each through an array
    int student_array[7] = {1, 2, 3, 4, 5, 6, 7};
    for (const auto & elem : student_array)
        std::cout << elem << " ";
    std::cout << "\n";

    INTEGER_FROM_FEATURES = 66;
    cout << "integer from feature is " << INTEGER_FROM_FEATURES << endl;
    int b1;
    int b2;
    b2 = 1 + (b1=2);
    cout << b2 << endl;
    //    string str(5); // DOESNT WORK!
    
        INTEGER_FROM_FEATURES = 66;
    cout << "integer from feature is " << INTEGER_FROM_FEATURES << endl;
    return 0;
}
