//
// Created by X on 30.06.2019.
//

#include "MyString.h"
#include<iostream>
#include <cstring>

using namespace std;






MyString::MyString(const char *str)
    {

        length = strlen(str);// функция strlen получает количество символов в строке которую мы передаём в объект

        // выделяем память для динамического массива где будет храниться наша строка
        // +1 символ так как нужно место в массиве под терминирующий 0
        this->str = new char[length + 1];

        // копируем символы строки в массив нашего класса
        for (int i = 0; i < length; i++)
        {
            this->str[i] = str[i];
        }

        //закрываем строку терминирующим нулём
        this->str[length] = '\0';

    }
    // деструктор, отвечает за освобождение ресурвов занятых объектом, вызывается при уничтожении объекта класса
    MyString::~MyString()
    {
        delete[] this->str;
    }

    // конструктор копировании, необходим для создании точной копи объекта класса но в другой области памяти
    MyString::MyString(const MyString &other)
    {
        length = strlen(other.str);
        this->str = new char[length + 1];

        for (int i = 0; i < length; i++)
        {
            this->str[i] = other.str[i];
        }

        this->str[length] = '\0';
    }

    // перегруженый оператор присваивания, вызывается когда необходимо присвоить значение одного объекта другому
    MyString &MyString::operator =(const MyString& other)
    {
        // здесь логика похожа на ту которая реализована в конструкторе, за исключением того, что нам нужно позаботиться
        // об освобождении ресурсов объекта если до копирования в него новой строки он уже содержал код
        //+ страндартный синтаксис перегрузки оператора =
        if (this->str != nullptr)
        {
            delete[] str;
        }

        length = strlen(other.str);
        this->str = new char[length + 1];

        for (int i = 0; i < length; i++)
        {
            this->str[i] = other.str[i];
        }

        this->str[length] = '\0';

        return *this;

    }
    MyString &MyString::operator =(const char* other)
    {
        // здесь логика похожа на ту которая реализована в конструкторе, за исключением того, что нам нужно позаботиться
        // об освобождении ресурсов объекта если до копирования в него новой строки он уже содержал код
        //+ страндартный синтаксис перегрузки оператора =
        if (this->str != nullptr)
        {
            delete[] str;
        }

        length = strlen(other);
        this->str = new char[length + 1];

        for (int i = 0; i < length; i++)
        {
            this->str[i] = other[i];
        }

        this->str[length] = '\0';

        return *this;

    }
    //перегруженный оператор сложения, в текущей реализации класса String необходим для конкатенации строк
    MyString MyString::operator+(const MyString &other)
    {
        //создаём новый пустой объект где будим хранить результат конкатенации строк и который будет результатом работы
        // перегруженного оператора +
        MyString newStr;
        // получаем количество символов в обеих строках для конкатенации

        int thisLength = strlen(this->str);
        int otherLength = strlen(other.str);

        newStr.length = thisLength + otherLength;

        // выделяем место в динамической памяти под новую строку
        newStr.str = new char[thisLength + otherLength + 1];

        //копируем данные из 2х конкатенируемых строк в новую строку
        int i = 0;
        for (; i < thisLength; i++)
        {
            newStr.str[i] = this->str[i];
        }

        for (int j = 0; j < otherLength; j++, i++)
        {
            newStr.str[i] = other.str[j];
        }

        newStr.str[thisLength + otherLength] = '\0';

        // возвращаем результа
        // возвращаем результат конкатенации
        return newStr;
    }

    // выводит строку в консоль, в идеале для этого необходима перегрузка оператора «
    void MyString::Print()
    {
        cout << str;
    }

    int MyString::Length()
    {
        return length;
    }

    bool MyString::operator ==(const MyString & other)
    {
        if (this->length != other.length)
        {
            return false;
        }

        for (int i = 0; i < this->length; i++)
        {
            if (this->str[i] != other.str[i])
            {
                return false;
            }
        }
        return true;
    }

    bool MyString::operator !=(const MyString & other)
    {
        return !(this->operator==(other));
    }


