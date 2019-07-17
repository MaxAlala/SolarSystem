//
// Created by X on 16.07.2019.
//

#ifndef CPP_CODE_MOVESEMANTIC_H
#define CPP_CODE_MOVESEMANTIC_H


// useless.cpp -- an otherwise useless class with move semantics
#include <iostream>
#include <utility>
using namespace std;
// interface
class MoveSemantic
{
private:
    int n; // number of elements
    char * pc; // pointer to data
    static int ct; // number of objects
    void ShowObject() const;
public:
    MoveSemantic();
    explicit MoveSemantic(int k);
    MoveSemantic(int k, char ch);
    MoveSemantic(const MoveSemantic & f); // regular copy constructor
    MoveSemantic(MoveSemantic && f); // move constructor
    ~MoveSemantic();
    MoveSemantic operator+(const MoveSemantic & f)const;
// need operator=() in copy and move versions
    MoveSemantic & operator=(MoveSemantic && f);
    MoveSemantic & operator=(const MoveSemantic & f);
    void ShowData() const;
};
// implementation
int MoveSemantic::ct = 0;
MoveSemantic::MoveSemantic()
{
    ++ct;
    n = 0;
    pc = nullptr;
    cout << "default constructor called; number of objects: " << ct << endl;
    ShowObject();
}
MoveSemantic::MoveSemantic(int k) : n(k)
{
    ++ct;
    cout << "int constructor called; number of objects: " << ct << endl;
    pc = new char[n];
    ShowObject();
}
MoveSemantic::MoveSemantic(int k, char ch) : n(k)
{
    ++ct;
    cout << "int, char constructor called; number of objects: " << ct
         << endl;
    pc = new char[n];
    for (int i = 0; i < n; i++)
        pc[i] = ch;
    ShowObject();
}
MoveSemantic::MoveSemantic(const MoveSemantic & f): n(f.n)
{
    ++ct;
    cout << "copy const called; number of objects: " << ct << endl;
    pc = new char[n];
    for (int i = 0; i < n; i++)
        pc[i] = f.pc[i];
    ShowObject();
}
MoveSemantic::MoveSemantic(MoveSemantic && f): n(f.n)
{
    ++ct;
    cout << "move constructor called; number of objects: " << ct << endl;
    pc = f.pc; // steal address
    f.pc = nullptr; // give old object nothing in return
    f.n = 0;
    ShowObject();
}
MoveSemantic::~MoveSemantic()
{
    cout << "destructor called; objects left: " << --ct << endl;
    cout << "deleted object:\n";
    ShowObject();
    delete [] pc;
}
MoveSemantic MoveSemantic::operator+(const MoveSemantic & f)const
{
    cout << "Entering operator+()\n";
    MoveSemantic temp = MoveSemantic(n + f.n);
    for (int i = 0; i < n; i++)
        temp.pc[i] = pc[i];
    for (int i = n; i < temp.n; i++)
        temp.pc[i] = f.pc[i - n];
    cout << "temp object:\n";
    cout << "Leaving operator+()\n";
    return temp;
}

void MoveSemantic::ShowObject() const
{
    cout << "Number of elements: " << n;
    cout << " Data address: " << (void *) pc << endl;
}


void MoveSemantic::ShowData() const
{
    if (n == 0)
        cout << "(object empty)";
    else
        for (int i = 0; i < n; i++)
            cout << pc[i];
    cout << endl;
}
// application

MoveSemantic & MoveSemantic::operator=(const MoveSemantic & f) // copy assignment
{
    if (this == &f)
        return *this;
    delete [] pc;
    n = f.n;
    pc = new char[n];
    for (int i = 0; i < n; i++)
        pc[i] = f.pc[i];
    return *this;
}
MoveSemantic & MoveSemantic::operator=(MoveSemantic && f) // move assignment
{
    if (this == &f)
        return *this;
    delete [] pc;
    n = f.n;
    pc = f.pc;
    f.n = 0;
    f.pc = nullptr;
    return *this;
}

int useMoveSemantic()
{


    {
        MoveSemantic one(10, 'x');
        MoveSemantic two = one; // calls copy constructor
        MoveSemantic three(20, 'o');
        MoveSemantic four (one + three); // calls operator+(), move constructor
        cout << "object one: ";
        one.ShowData();
        cout << "object two: ";
        two.ShowData();
        cout << "object three: ";
        three.ShowData();
        cout << "object four: ";
        four.ShowData();
    }
    cout << "////////////////////////// \n\n\n";

    {
        using std::cout;
        {
            MoveSemantic one(10, 'x');
            MoveSemantic two = one +one; // calls move constructor
            cout << "object one: ";
            one.ShowData();
            cout << "object two: ";
            two.ShowData();
            MoveSemantic three, four;
            cout << "three = one\n";
            three = one; // automatic copy assignment
            cout << "now object three = ";
            three.ShowData();
            cout << "and object one = ";
            one.ShowData();
            cout << "four = one + two\n";
            four = one + two; // automatic move assignment
            cout << "now object four = ";
            four.ShowData();
            cout << "four = move(one)\n";
            four = std::move(one); // forced move assignment
            cout << "now object four = ";
            four.ShowData();
            cout << "and object one = ";
            one.ShowData();
        }
    }
}


#endif //CPP_CODE_MOVESEMANTIC_H
