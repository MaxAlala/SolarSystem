#include <iostream>

class A{
private:
public:
    int x = 10;
    int y = 5;
};

class B: public A{
private:
    int z;

    void method(){
        cout << y;
    }
};

istream & operator>>(istream& ifs, B& b)
{
    ifs >> b.x >> b.y;
    return ifs;
}
ostream & operator<<(ostream& ifs, B& b)
{
    ifs << b.x << " " << b.y << endl;
    return ifs;
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}