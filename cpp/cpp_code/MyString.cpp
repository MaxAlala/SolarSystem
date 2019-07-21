// string1.cpp -- String class methods
#include <cstring> // string.h for some
#include "MyString.h" // includes <iostream>
#include <algorithm>
using std::cin;
using std::cout;


struct String::Impl{
    Impl(const char * s){
        len = std::strlen(s); // set size
        str = new char[len + 1]; // allot storage
        std::strcpy(str, s); // initialize pointer
        num_strings++; // set object count
    }; // constructor
    Impl() // default constructor
    {
        len = 4;
        str = new char[1];
        str[0] = '\0'; // default string
        num_strings++;
    }
    Impl(const String & st)
    {
        num_strings++; // handle static member update
        len = st.pimpl->len; // same length
        str = new char [len + 1]; // allot space
        std::strcpy(str, st.pimpl->str); // copy string to new location
    }
    ~Impl(){
        --num_strings; // required
        delete [] str; // required
    }
    char * str; // pointer to string
    int len; // length of string
    static int num_strings; // number of objects
    static const int CINLIM = 80; // cin input limit
};
// initializing static class member
int String::Impl::num_strings = 0;
// static method
int String::HowMany() const
{
    return pimpl->num_strings;
}

// class methods
String::String(const char * s) : pimpl(std::make_unique<Impl>(s)) // construct String from C string
{
//    len = std::strlen(s); // set size
//    str = new char[len + 1]; // allot storage
//    std::strcpy(str, s); // initialize pointer
//    num_strings++; // set object count
}
String::String(): pimpl(std::make_unique<Impl>()) // default constructor
{
//    len = 4;
//    str = new char[1];
//    str[0] = '\0'; // default string
//    num_strings++;
}

String::String(const String & st):pimpl(std::make_unique<Impl>(st))
{
//    num_strings++; // handle static member update
//    len = st.len; // same length
//    str = new char [len + 1]; // allot space
//    std::strcpy(str, st.str); // copy string to new location
}
String::~String() // necessary destructor
{
//    --num_strings; // required
//    delete [] str; // required
}
// overloaded operator methods
// assign a String to a String


String & String::operator=(const String & st)
{
    if (this == &st)
        return *this;
    delete [] pimpl->str;
    pimpl->len = st.pimpl->len;
    pimpl->str = new char[pimpl->len + 1];
    std::strcpy(pimpl->str, st.pimpl->str);

    return *this;
}
String & String::swap(String & st)
{
    std::swap(pimpl, st.pimpl);
    return *this;
}

// assign a C string to a String
String & String::operator=(const char * s)
{
    delete [] pimpl->str;
    pimpl->len = std::strlen(s);
    pimpl->str = new char[pimpl->len + 1];
    std::strcpy(pimpl->str, s);
    return *this;
}
// read-write char access for non-const String
char & String::operator[](int i)
{
    return pimpl->str[i];
}
// read-only char access for const String
const char & String::operator[](int i) const
{
    return pimpl->str[i];
}

// overloaded operator friends
bool operator<(const String &st1, const String &st2)
{
    return (std::strcmp(st1.pimpl->str, st2.pimpl->str) < 0);
}
bool operator>(const String &st1, const String &st2)
{
    return st2 < st1;
}
bool operator==(const String &st1, const String &st2)
{
    return (std::strcmp(st1.pimpl->str, st2.pimpl->str) == 0);
}
// simple String output
ostream & operator<<(ostream & os, const String & st)
{
    os << st.pimpl->str;
    return os;
}
// quick and dirty String input
istream & operator>>(istream & is, String & st)
{
    char temp[String::Impl::CINLIM];
    is.get(temp, String::Impl::CINLIM);
    if (is)
        st = temp;
    while (is && is.get() != '\n')
        continue;
    return is;
}