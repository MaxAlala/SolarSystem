//
// Created by X on 07.07.2019.
//

#include <iostream>
#include "feature2.h"
#include "Vector.h"
#include <iostream>
#include <cstdlib> // rand(), srand() prototypes
#include <ctime> // time() prototype
#include <functional>



#include <boost/type_index.hpp>
#include <memory>
#include <sstream>
#include "vector"
template<typename T>
std::string to_string_impl(const T& t)
{
    std::stringstream ss;
    ss << t;
    return  ss.str();
}

std::vector<std::string> to_string()
{
    return {};
}
template<typename P1, typename ...Param>
std::vector<std::string> to_string(const P1 &p1, const Param& ... param)
{
    std::vector<std::string> s;
    s.push_back(to_string_impl(p1));

    const auto remainder = to_string(param...);
    s.insert(s.end(), remainder.begin(), remainder.end());
    return s;
}
template<typename P1, typename ...Param>
std::vector<std::string> to_string2(const P1 &p1, const Param& ... param)
{
    return {to_string_impl(param)...};//init vector with init list, for each param call string impl.
}

template<typename P1, typename ...Param>
std::vector<std::string> to_string3(const P1 &p1, const Param& ... param)
{
    const auto to_string_impl = [](const auto &p){
        std::stringstream ss;
        ss << p;
        return ss.str();
    };
    return {to_string_impl(param)...};//init vector with init list, for each param call string impl.
}


void useToString(){
    const auto vec = to_string("hello!",9.3, 1,'h',1.3L);
    for(const auto &o: vec)
    {
        std::cout << o << '\n';
    }
}

class Investment {
public:
    virtual ~Investment(); // design
    void putLog() noexcept {
        using namespace std;
        cout << "log. \n";
    }
};
template<typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts&&... params)
{
    return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}

void makeLogEntry(Investment* i){
    (*i).putLog();
}
void assignDefaultDeleter(){
    using namespace std;
    auto delInvmt = [](Investment* pInvestment) // this is now
    { // inside
        makeLogEntry(pInvestment); // makedelete
        pInvestment; // Investment
    };
    std::unique_ptr<Investment, decltype(delInvmt)> // as
            pInv(nullptr, delInvmt);
}

constexpr int pow(int base, int exp) noexcept
{
    return (exp == 0 ? 1 : base * pow(base, exp - 1));
}
constexpr int pow2(int base, int exp) noexcept // C++14
{
    auto result = 1;
    for (int i = 0; i < exp; ++i) result *= base;
    return result;
}

template<typename T>
void f(const T& param) noexcept
{
    using std::cout;
    using boost::typeindex::type_id_with_cvr;
// show T
    cout << "T = "
         << type_id_with_cvr<T>().pretty_name()
         << '\n';
// show param's type
    cout << "param = "
         << type_id_with_cvr<decltype(param)>().pretty_name()
         << '\n';
}

void useTrueTypeRec(){

    const int& x = 555;
    f(x);
}
///////////
class Widget{

};
template<typename Container, typename Index> // final
auto // C++11
authAndAccess(Container&& c, Index i) // version
-> decltype(std::forward<Container>(c)[i])
{
//    authenticateUser();
    return std::forward<Container>(c)[i];
}

template<typename Container, typename Index> // final
decltype(auto) // C++14
authAndAccess(Container&& c, Index i) // version
{
//    authenticateUser();
    return std::forward<Container>(c)[i];
}


template<typename Container, typename Index> // works, but
auto authAndAccess(Container& c, Index i) // requires
-> decltype(c[i]) // refinement
{
//    authenticateUser();
    return c[i];
}

template<typename Container, typename Index> // C++14;
auto authAndAccess(Container& c, Index i) // not quite
{ // correct
//    authenticateUser();
    return c[i]; // return type deduced from c[i]
}
void useReturnRvalueFromContainer(){
//    std::deque<std::string> makeStringDeque(); // factory function
//// make copy of 5th element of deque returned
//// from makeStringDeque
//    auto s = authAndAccess(makeStringDeque(), 5);
    Widget w;
    const Widget& cw = w;
    auto myWidget1 = cw; // auto type deduction
    // myWidget1's type is Widget
    decltype(auto) myWidget2 = cw; // decltype type deduction:
// myWidget2's type is
// const Widget&
}
//////////////////elipsis template

// definition for 0 parameters
void show_list() {}
// definition for 1 parameter
template<typename T>
void show_list(const T& value)
{
    std::cout << value << '\n';
}


// definition for 2 or more parameters
template<typename T, typename... Args>
void show_list(const T& value, const Args&... args)
{
    std::cout << value << ", ";
    show_list(args...);
}
void use_elipsis_template()
{
    int n = 14;
    double x = 2.71828;
    std::string mr = "Mr. String objects!";
    show_list(n, x);
    show_list(x*x, '!', 7, mr);
}






template <typename T, typename F> // want only one instantiations!
T use_f(T v, F f)
{
    static int count = 0;
    count++;
    std::cout << " use_f count = " << count
              << ", &count = " << &count << std::endl;
    return f(v);
}
class Fp
{
private:
    double z_;
public:
    Fp(double z = 1.0) : z_(z) {}
    double operator()(double p) { return z_*p; }
};
class Fq
{
private:
    double z_;
public:
    Fq(double z = 1.0) : z_(z) {}
    double operator()(double q) { return z_+ q; }
};

template <typename T>
T use_f(T v, std::function<T(T)> f) // f call signature is T(T)
{
    static int count = 0;
    count++;
    std::cout << " use_f count = " << count
              << ", &count = " << &count << std::endl;
    return f(v);
}

double dub(double x) {return 2.0*x;}
double square(double x) {return x*x;}
void use_different_instantiations_for_same_sig(){
    {
        using std::cout;
        using std::endl;
        double y = 1.21;
        cout << "Function pointer dub:\n";
        cout << " " << use_f(y, dub) << endl;
        cout << "Function pointer square:\n";
        cout << " " << use_f(y, square) << endl;
        cout << "Function object Fp:\n";
        cout << " " << use_f(y, Fp(5.0)) << endl;
        cout << "Function object Fq:\n";
        cout << " " << use_f(y, Fq(5.0)) << endl;
        cout << "Lambda expression 1:\n";
        cout << " " << use_f(y, [](double u) {return u*u;}) << endl;
        cout << "Lambda expression 2:\n";
        cout << " " << use_f(y, [](double u) {return u+u/2.0;}) << endl;

        cout << "//////////////////////////////one inst.. \n";

        using std::function;
        function<double(double)> ef1 = dub;
        function<double(double)> ef2 = square;
        function<double(double)> ef3 = Fq(10.0);
        function<double(double)> ef4 = Fp(10.0);
        function<double(double)> ef5 = [](double u) {return u*u;};
        function<double(double)> ef6 = [](double u) {return u+u/2.0;};
        cout << "Function pointer dub:\n";
        cout << " " << use_f(y, ef1) << endl;
        cout << "Function pointer square:\n";
        cout << " " << use_f(y, ef2) << endl;
        cout << "Function object Fp:\n";
        cout << " " << use_f(y, ef3) << endl;
        cout << "Function object Fq:\n";
        cout << " " << use_f(y, ef4) << endl;
        cout << "Lambda expression 1:\n";
        cout << " " << use_f(y, ef5) << endl;
        cout << "Lambda expression 2:\n";
        cout << " " << use_f(y,ef6) << endl;
    }
}





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