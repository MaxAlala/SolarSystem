// string1.h -- fixed and augmented string class definition
#ifndef STRING1_H_
#define STRING1_H_
#include <iostream>
#include <memory>
using std::ostream;

using std::istream;

class String
{
private:
    struct Impl;
    std::unique_ptr<Impl> pimpl; // pipmpl pattern to separate impl from interface

public:
// constructors and other methods
    String(const char * s); // constructor
    String(); // default constructor
    String(const String &); // copy constructor
    ~String(); // destructor
    int length () const;
// overloaded operator methods
    String & operator=(const String &);
    String & swap(String & st);
    String & operator=(const char *);
    char & operator[](int i);
    const char & operator[](int i) const;
// overloaded operator friends
    friend bool operator<(const String &st, const String &st2);
    friend bool operator>(const String &st1, const String &st2);
    friend bool operator==(const String &st, const String &st2);
    friend ostream & operator<<(ostream & os, const String & st);
    friend istream & operator>>(istream & is, String & st);
// static function
   int HowMany() const;
};
#endif