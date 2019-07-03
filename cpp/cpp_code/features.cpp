//
// Created by X on 29.06.2019.
//
#include "iostream"
#include <ctime>
#include <assert.h>
#include <functional>
#include <vector>
#include <iomanip>
#include <fstream>
//#include <wincon.h>
#include "features.h"
#include "STL.h"
//#include "windows.h"

#define NDEBUG // turn off all assert macroses
using namespace std;

/*
strcpy_s(ar,ar2);
strcat
strncat
strcmp
strncmp
strlen


*/
// elipsis cstdarg va_list, va_start, va_arg, va_end



//void getarr(int arr[]) == void getarr(int *arr)
//r-value fun
void rvalue_test(const int &ref)
{
    cout << "r not r value!";
}
void rvalue_test(int &&ref)
{
    cout << "i am r-value!";
}

extern int g_lovely_simple_integer;
static int lovely_simple_integer;
auto returnInt() -> int{// trailing
    return 10;
}


void testField(){
    ////pruning, aggregate types, rand?, numbers
    unsigned int ui = 16;
    cout << (ui<<1) << endl; // & | ^-xor <<=
    cout << (-ui) << endl;
    signed short int si = 5;
    long int li = 6LLU; // ll ul F l
    uint16_t uint16 = 55ull;
    constexpr double d = 300000000000.344444444444444444444444444444444444444444;
     int bin = 0;
    bin = 0b10000;
    cout << setprecision(100) <<d << "\n";
    // byte masks
    const unsigned char option1 = 0x01; // шестнадцатеричный литерал для 0000 0001
    const unsigned char option2 = 0x02; // шестнадцатеричный литерал для 0000 0010
    const unsigned char option3 = 0x04; // шестнадцатеричный литерал для 0000 0100
    const unsigned char option4 = 0x08; // шестнадцатеричный литерал для 0000 1000
    const unsigned char option5 = 0x10; // шестнадцатеричный литерал для 0001 0000
    const unsigned char option6 = 0x20; // шестнадцатеричный литерал для 0010 0000
    const unsigned char option7 = 0x40; // шестнадцатеричный литерал для 0100 0000
    const unsigned char option8 = 0x80; // шестнадцатеричный литерал для 1000 0000

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

/*
    int array[] = {1,2,3,4,5};
    cout << &array[1] << "\n";
    cout << array+1 << "\n";
    cout << array[1] << "\n";
    cout << *(array+1) << "\n";

    char *ch = "hello";
    char ch2[] = "hello";
    char ch3[] = {'1', '2', 'a', 'b', 'A'}; // abracadabra
    char **ch4 = new char*[10];
    char * ch5[] = {"hello", "h"};
    //    char *ch4 = new char[20]{"hello"}; // not work in c++ 11
    char a = 'R'; // &a == abra...
    cout << ch3 << " " << "\n";

    int **array5 = new int*[20];
    int (*array6)[5] = new int[6][5];

*/

    //// const

/*    int *integer = new (std::nothrow) int; // no bad_alloc, just null
     integer = nullptr;
     delete integer;
     delete integer;
    //        assert(integer && "pointer have no value!");// always check
    const int const_x = 5;
    int const const_ptr = 5;
    const_ptr = 1111; //ok
    const int not_const_x = 5;
    //    int &ref = const_x; // cant take const int
    const int ref2 = not_const_x;
    const int ref3 = 55; // can take r-value
    void *ptr = new int(55);
    int *ptr2 = static_cast<int *>(ptr);
    cout << *ptr2 << endl;

    int ** ptr3 = &ptr2;
    cout << **ptr3 << '\n';
    */
    ////// function
    void(*func)();
    func = testField;
    (*func)(); // explicit
    func(); // implicit
    using someFunc = void(*)(int, int);
    typedef void(*someFunc2)(int, int);
    function<int(int,int)> someFunc3; // functional lib
    /////////////reference_wrapper = to not use pointer in collection for virtual f.
/*    vector<reference_wrapper<Object>> v;
    vector<reference_wrapper<Object *>> v2; // works same, but problems with dynamic memory
    ObjectChild objectChild1("Max", 70) ;
    v.emplace_back(objectChild1);
    v[0].get().doAction();
    Object* obj1 = new ObjectChild("Starship", 900000); // Child to Parent = ascending case
    obj1->doAction();
    ObjectChild *objch1 = dynamic_cast<ObjectChild*>(obj1); // Object to Child = descending cast// doesnt work with the private, protected inheritance
    obj1->doAction_uninherited();
    objch1->doAction_uninherited();

    ObjectChild objch2("Earth",5972024);
    Object &obj = objch2;
    ObjectChild &objectChild2 = dynamic_cast<ObjectChild&>(obj); // ref of the parent to the child
    objectChild2.doAction_uninherited();*/
    //// iostream

//    SetConsoleCP(1251);
//    SetConsoleOutputCP(1251);
   /* char char_arr[10];
    cin >> std::setw(8) >> char_arr; // iomanip lib
    cerr << "HEHEH! \n"; //error
    cout << char_arr;

    char ch;
    while(cin >> ch)  // read until ' ' and miss it
        cout << ch;

    while(cin.get(ch))  // read until \n takes it, doesnt take it
        cout << ch;

    cin.get(char_arr, 5);
    cout << char_arr << '\n';

    cin.getline(char_arr, 9); // read all line with \n
    cout << char_arr << '\n';

    cout << std::cin.gcount() << '\n'; // count of read symbols
    string str;
    getline(cin, str);

    putback(char) - put symbol in buffer, unget()=take and putback
    peek() - read symbol and doesnt remove it
    ignore() - ignore first symbol
    ignore(int)

    cout.setf(std::ios::showpos); //flags -no*, hex, dec,
    // oct, but firstly unsetf(dec)
    cout << 30 << '\n';  // boolalpha, noboolalpha, uppercase
    cout << std::uppercase << '\n'; // precision(5)

    stringstream stringstream1; // sstream lib
    stringstream1 << "stringstream";
    stringstream1 << 555;
    stringstream1.str("stringstream");
    cout << stringstream1.str();
    stringstream stringstream2;
    stringstream2 << 5555;
    int x;
    stringstream2 >> x;

    stringstream2.str(""); // remove the value
    stringstream2.clear(); // remove all error flags
    // goodbit, badbit - fatal er, eofbit - reach the end,
    // failbit - not fatal er; good,bad,eof,fail,clear(state),
    // setstate(state);

    // isalnum(int) - letter or digit,
    // isalpha - letter, iscntrl - comand,
    // isdigit, isprint - enter,space, ispunct - not,dig,let,space,
    // isspace, isxdigit - 0x

    int someInt;
    cin >> someInt;
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(32767, '\n');// delete all buffer
    }
    */

/*   ifstream ifstream1; // fstream
    ofstream ofstream1; // has the flush
   ifstream1.open("text.txt");
   while(ifstream1)
   {
       string str;
       ifstream1 >> str; //getline(ifstream1, str);
   }
    // with  open() use = app, in, out, trunc - delete file,
    // ate - the end of the file

    ifstream1.seekg(15, ios::cur);// go forward 15 bytes
    ifstream1.seekg(0, ios::beg);
    ifstream1.seekg(0, ios::end);
    cout << ifstream1.tellg() << '\n';*/






}