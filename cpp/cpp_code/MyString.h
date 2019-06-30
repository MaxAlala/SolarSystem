//
// Created by X on 30.06.2019.
//

#ifndef CPP_CODE_MYSTRING_H
#define CPP_CODE_MYSTRING_H
using namespace std;

class MyString
{
public:
    MyString()
    {
        str = nullptr;
        length = 0;
    }
    MyString(const char *str);
    ~MyString();
    MyString(const MyString &other);
    MyString &operator =(const MyString& other);
    MyString &operator =(const char* other);
    MyString operator+(const MyString &other);
    void Print();
    int Length();
    bool operator ==(const MyString & other);
    bool operator !=(const MyString & other);
    char& operator [](int index)
    {
        return this->str[index];
    }
private:
    char*str;
    int length;
};


#endif //CPP_CODE_MYSTRING_H
