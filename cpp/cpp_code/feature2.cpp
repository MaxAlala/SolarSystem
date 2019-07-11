//
// Created by X on 07.07.2019.
//

#include <iostream>
#include "feature2.h"
#include "Vector.h"
#include <iostream>
#include <cstdlib> // rand(), srand() prototypes
#include <ctime> // time() prototype


void randomWalkingTask(){
    using namespace std;
    using VECTOR::Vector;
    srand(time(0)); // seed random-number generator
    double direction;
    Vector step;
    Vector result(0.0, 0.0);
    unsigned long steps = 0;
    double target;
    double dstep;
    cout << "Enter target distance (q to quit): ";
    while (cin >> target)
    {
        cout << "Enter step length: ";
        if (!(cin >> dstep))
            break;
        while (result.magval() < target)
        {
            direction = rand() % 360;
            step.reset(dstep, direction, Vector::POL);
            result = result + step;
            steps++;
        }
        cout << "After " << steps << " steps, the subject "
                                     "has the following location:\n";
        cout << result << endl;
        result.polar_mode();
        cout << " or\n" << result << endl;
        cout << "Average outward distance per step = "
             << result.magval()/steps << endl;
        steps = 0;
        result.reset(0.0, 0.0);

        cout << "Enter target distance (q to quit): ";
    }
    cout << "Bye!\n";
    cin.clear();
    while (cin.get() != '\n')
        continue;
}



class SomeFeatureClass{
    enum{ GoodEnumLikeConstant = 555};// no pointer, no ref = great
    constexpr static const double FudgeFactor = 5;

};
template<unsigned n> // general case: the value of ///TMP.
struct Factorial { // Factorial<n> is n times the value
// of Factorial<n-1>
    enum { value = n * Factorial<n-1>::value };
};
template<> // special case: the value of
struct Factorial<0> { // Factorial<0> is 1
    enum { value = 1 };
};

template<typename T> // implicit interface// compile-time
void doProcessing(T& w)
{
    if (w.size() > 10 && w != "Hector") {
        T temp(w);
        temp.normalize();
        temp.swap(w);
    }
}


namespace // unnamed namespace
{
    int ice; // static storage, internal linkage
    int bandycoot;
}

namespace elements
{
    namespace fire
    {
        int flame;
    }
    float water;
}
namespace someNs = elements::fire;
using someNs::flame;

const int BUF = 512;
const int N = 5;
char buffer[BUF];

void useSameMemorzNew(){
    using namespace std;
    double *pd1, *pd2;
    int i;
    cout << "Calling new and placement new:\n";
    pd1 = new double[N]; // use heap
    pd2 = new (buffer) double[N]; // use buffer array
    for (i = 0; i < N; i++)
        pd2[i] = pd1[i] = 1000 + 20.0 * i;
    cout << "Memory addresses:\n" << " heap: " << pd1
         << " static: " << (void *) buffer <<endl;
    cout << "Memory contents:\n";
    for (i = 0; i < N; i++)
    {
        cout << pd1[i] << " at " << &pd1[i] << "; ";
        cout << pd2[i] << " at " << &pd2[i] << endl;
    }
    cout << "\nCalling new and placement new a second time:\n";
    double *pd3, *pd4;
    pd3= new double[N]; // find new address
    pd4 = new (buffer) double[N]; // overwrite old data
    for (i = 0; i < N; i++)
        pd4[i] = pd3[i] = 1000 + 40.0 * i;
    cout << "Memory contents:\n";
    for (i = 0; i < N; i++)
    {
        cout << pd3[i] << " at " << &pd3[i] << "; ";
        cout << pd4[i] << " at " << &pd4[i] << endl;
    }
    cout << "\nCalling new and placement new a third time:\n";
    delete [] pd1;
    pd1= new double[N];
    pd2 = new (buffer + N * sizeof(double)) double[N];
    for (i = 0; i < N; i++)
        pd2[i] = pd1[i] = 1000 + 60.0 * i;
    cout << "Memory contents:\n";
    for (i = 0; i < N; i++)
    {
        cout << pd1[i] << " at " << &pd1[i] << "; ";
        cout << pd2[i] << " at " << &pd2[i] << endl;
    }
    delete [] pd1;
    delete [] pd3;
}

void battleField(){
    std::cout << Factorial<10>::value << " is facrotial of 10. TMP";
}