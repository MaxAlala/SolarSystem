//
// Created by X on 29.06.2019.
//
#include "iostream"
#include <ctime>
#include <assert.h>
#include "features.h"
using namespace std;

/*
strcpy_s(ar,ar2);
strcat
strncat
strcmp
strncmp
strlen


*/



void testField(){
    using std::cout;
    short s = 30000;
    short c = 30000;
    cout << s+c << endl; // int 60000
    using someInt = int;
    someInt x = 5;
    srand(time(0));
    std::cout << rand() << "\t" << "\n";
        int nu = NULL;

    ////cin fun
/*    double d{};
    cin>>d;
    string str{};
    cin.ignore(32767, '\n');
    getline(cin, str);
    cout << d << " " << str << "\n";*/
    ////arrays

    int array[] = {1,2,3,4,5};
    cout << &array[1] << "\n";
    cout << array+1 << "\n";
    cout << array[1] << "\n";
    cout << *(array+1) << "\n";

    char *ch = "hello";
    char ch2[] = "hello";
    char ch3[] = {'1', '2', 'a', 'b', 'A'}; // abracadabra
    //    char *ch4 = new char[20]{"hello"}; // not work in c++ 11
    char a = 'R'; // &a == abra...
    cout << ch3 << " " << "\n";
    ////

    int *integer = new (std::nothrow) int; // no bad_alloc, just null
     integer = nullptr;
     delete integer;
     delete integer;
    //        assert(integer && "pointer have no value!");// always check
    const int const_x = 5;
    const int not_const_x = 5;
    //    int &ref = const_x; // cant take const int
    const int ref2 = not_const_x;
    const int ref3 = 55; // can take r-value
    void *ptr = new int(55);
    int *ptr2 = static_cast<int *>(ptr);
    cout << *ptr2 << endl;

    int ** ptr3 = &ptr2;
    cout << **ptr3 << '\n';


    int **array5 = new int*[20];
    int (*array6)[5] = new int[6][5];

}