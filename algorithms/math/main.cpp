#include <iostream>

#include <iostream>
#include <chrono>
#include <vector>
using namespace std;
class SimpleTimer
{
public:
    SimpleTimer()
    {
        start = std::chrono::high_resolution_clock::now();
    }

    ~SimpleTimer()
    {
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = end - start;
        cout << "Duration " << duration.count() << " s" << endl;
    }
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
};

int getNaiveFibo(int n){
    if(n <= 1) return n;
    return getNaiveFibo(n - 1) + getNaiveFibo(n - 2);
}

int getArrayFibo(int n){

    int ar[n];
    ar[0] = 0;
    ar[1] = 1;
//    vector<int> vector(n);
//    vector[0] = 0;
//    vector[1] = 1;
    for(int i = 2; i <= n; i++ )
    {
        ar[i] = ar[i-1] + ar[i-2];
    }
    return ar[n];

}

#include <cassert>
#include <iostream>
#include <unordered_set>

template <class Int>
Int gcd(Int a, Int b) {
    if (a == 0) {
        return b;
    } else if (b == 0) {
        return a;
    }
    assert(a > 0 && b > 0);
    // optimize this function


    if(a >= b){
        return gcd(a % b, b);
    } else if(a <= b) {
        return gcd(a,b % a);
    }
}


int binarySearch(vector<int> &vec, int n)
{
    int l = 0;
    int r = vec.size()-1;
    int m = 0;
    while(l <= r)
    {
        m = (l+r)/2;
        if(vec[m] == n) return vec[m];
        else if(vec[m] > n) r = m - 1;
        else if(vec[m] < n) l = m + 1;
    }
    return -1;
}


void insertionSort(vector<int> &vec){
    for(int i = 1; i < vec.size(); i++){
        int j = i;
        while(vec[j] < vec[j - 1]) {
//            int temp = vec[j - 1];
//            vec[j - 1] = vec[j];
//            vec[j] = temp;
            std::swap(vec[j-1], vec[j]);
            j--;
        }
    }
}
#include <cstdio>
#include <fstream>

void maxIncreasingSequenceType(){

}

template <typename T>
void invert_string(T &str){
    int length = str.size();
    for(int i = 0; i < (length/2); i++)
    {
        std::swap( str[i], str[length - i - 1]);
    }
}


int main() {
    std::cout << "Hello, World!" << std::endl;

    return 0;
}
