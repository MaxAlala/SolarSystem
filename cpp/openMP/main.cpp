#include <iostream>
#include <vector>
#include <omp.h>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <array>
#include <cmath>
//#include <wingdi.h>

class Timer
{
private:
    // Псевдонимы типов используются для удобного доступа к вложенным типам
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::chrono::time_point<clock_t> m_beg;

public:
    Timer() : m_beg(clock_t::now())
    {
    }

    void reset()
    {
        m_beg = clock_t::now();
    }

    double elapsed() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
    }
};


// open mpi
// mpi
using namespace std;
class Building{
protected:
    int x;
    int y;
    int z;

};
class Airport : Building{
    int countOfPlanes;
public:
    int getCountOfPL;
};

int someFunct(int x){

}

void taskOne(){

};

void printThreadCountAndNum(){
    int id = omp_get_thread_num ();
    int numt = omp_get_num_threads ();
    printf("Thread (%d) of (%d) threads alive. \n", id, numt);
//    printf("HelloWorld!\n");
//    cout << "Hello World!" << endl;
};

void printValue(int num){
    printf("Number is (%d). \n", num);
}


void fillArray(vector<int> &vec){
    int counter = 0;
    for( int &num: vec){
        num += counter;
        counter++;
    }
}


void assign_rnd_value(){

}
//gcc -program.c -o obj -fopenmp
int main() {
//    vector<int> vec(500);
//    int num = 555;


    //Task 1

//#pragma omp parallel
//    printf("Thread (%d) of (%d) threads alive. ", omp_get_thread_num (), omp_get_num_threads ());


    //Task 2
//
//    omp_set_num_threads(3);
//    omp_set_num_threads(3);
//#pragma omp parallel if(omp_get_max_threads() > 1)
//    {
//        printThreadCountAndNum();
//    }
//
//    omp_set_num_threads(1);
//#pragma omp parallel if(omp_get_num_threads()>1)
//    {
//        printThreadCountAndNum();
//    }


// Task 3
//auto a = 11, b = 32;
//    printValue(a);
//    printValue(b);
//    omp_set_num_threads(2);
//
//#pragma omp parallel private(a) firstprivate(b)
//    {
//        a+=omp_get_thread_num();
//        b+=omp_get_thread_num();
//    }
//    printValue(a);
//    printValue(b);
//
//    omp_set_num_threads(4);
//
//#pragma omp parallel shared(a) private(b)
//    {
//        a-=omp_get_thread_num();
//        b-=omp_get_thread_num();
//    }
//
//    printValue(a);
//    printValue(b);

    //Task 4
//    vector<int> a_vec(10);
//    auto counter = 0;
//    vector<int> b_vec(10);
//    fillArray(a_vec);
//    fillArray(b_vec);
//    for(int x:a_vec)cout<<x << endl;
//    omp_set_num_threads(2);
//
//#pragma omp parallel
//    {
//        if (omp_get_thread_num() == 1) {
//            printValue(*std::min_element(a_vec.begin(), a_vec.end()));
//        }
////        printValue(omp_get_thread_num());
//
//#pragma omp master
//            {
//                printValue(*std::max_element(a_vec.begin(), a_vec.end()));
//            }
//    }


// Task 5
//    srand(time(NULL));

//int **ar = new int*[6];
//    auto ar = new int*[6];
//    for(int i = 0; i < 6; ++i)
//        ar[i] = new int[8];
//
//    for(int i = 0; i < 6; ++i)
//        for(int j = 0; j < 8; j++)
//            ar[i][j] = rand() % 10 + 1;
//
//    Timer t;
//#pragma omp parallel sections shared(ar)
//    {
//#pragma omp section
//        {
//            int average = 0;
//            for(int i = 0; i < 6; ++i)
//                for(int j = 0; j < 8; j++)
//                    average += ar[i][j];
//            printf("ThreadNum is %d \n", omp_get_thread_num());
//            printf("average ");
//            printValue(average/(6*8));
//        }
//
//#pragma omp section
//        {
//            {
//                int min = 0;
//                int max = 0;
//                for(int i = 0; i < 6; ++i)
//                    for(int j = 0; j < 8; j++){
//                        if(ar[i][j]<min)min = ar[i][j];
//                        if(ar[i][j]>max)max = ar[i][j];
//                    }
//                printf("ThreadNum is %d \n", omp_get_thread_num());
//                printf("min ");
//                printValue(min);
//                printf("max ");
//                printValue(max);
//            }
//        }
//
//#pragma omp section
//        {
//
//            int count = 0;
//            for(int i = 0; i < 6; ++i)
//                for(int j = 0; j < 8; j++){
//                    if(ar[i][j]%3 == 0)count++;
//                }
//            printf("ThreadNum is %d \n", omp_get_thread_num());
//            printf("Number of multiples of three is %d \n", count);
//        }
//    }
//
//
//
//    cout << t.elapsed() << " timer. ";


// Task 6

//    vector<int> a_vec(10);
//    vector<int> b_vec(10);
//    fillArray(a_vec);
//    fillArray(b_vec);
//
//
//    int average_a = 0;
//    int average_b = 0;
//#pragma omp parallel for shared(average_a, average_b)
//    for (int j=0; j<a_vec.size(); j++) {
//        average_a+=a_vec.at(j);
//        average_b+=b_vec.at(j);
//    }
//    printf("average a is %d \n", average_a);
//    printf("average b is %d \n", average_b);
//
//    average_a = 0;
//    average_b = 0;
//#pragma omp parallel for reduction(+: average_a, average_b)
//    for (int j=0; j<a_vec.size(); j++) {
//        average_a+=a_vec.at(j);
//        average_b+=b_vec.at(j);
//    }
//    printf("average a is %d \n", average_a);
//    printf("average b is %d \n", average_b);

// Task 7
//
// array<int,12> a_vec;
// array<int,12> b_vec;
// array<int,12> c_vec;
//omp_set_num_threads(3);
//#pragma omp parallel for schedule(static,4)
//    for(int i = 0; i < a_vec.size(); i++)
//    {
//        a_vec.at(i) = i;
//        b_vec.at(i) = i;
//        printf("num of threads is %d, num of thread is %d, an iteration num is %d \n", omp_get_num_threads(), omp_get_thread_num(), i);
//    }
//
//    omp_set_num_threads(4);
//#pragma omp parallel for schedule(dynamic,3)
//        for (int i = 0; i < a_vec.size(); i++)
//        {
//            c_vec.at(i) = a_vec.at(i) + b_vec.at(i);
//            printf("num of threads is %d, num of thread is %d, an iteration num is %d \n", omp_get_num_threads(), omp_get_thread_num(), i);
//        }


    // task 8
//    omp_set_num_threads(8);
//    constexpr uint64_t size = 10000;
//    vector<vector<int>> matrix(size);
//    for ( int i = 0 ; i < size ; i++ )
//        matrix[i].resize(size);
//    std::for_each(matrix.begin(),matrix.end(),
//                  [](std::vector<int> &vec){
//                      vec.resize(size);
//                      std::for_each(vec.begin(), vec.end(),[](int& x){x=1+rand()%size;});
//                      std::for_each(vec.begin(),vec.end(),[](int& x){
////                          std::cout << x << " ";
//                      });
////                      cout << endl;
//                  });
//    std::vector<int > vector(size, 2);
//    std::vector<int > resultVector(size, 0);
//    int resultSum = 0;
//    Timer t;
//#pragma omp parallel
//#pragma omp for reduction(+: resultSum)
//    for(int i = 0; i < matrix.size(); i++)
//    {
//        int counter = 0;
//        for_each(matrix.at(i).begin(), matrix.at(i).end(),
//                 [vector, &resultSum, i, &counter](int x){
//                     resultSum += x*vector.at(counter);
//                     counter++;
//                 }
//        );
//        resultVector.at(i) = resultSum;
////        cout << resultVector.at(i) << "\t";
//        resultSum = 0;
//    }
//
//cout << t.elapsed() << " using openMP." <<endl;
////    for_each(resultVector.begin(), resultVector.end(),[](int x){cout << x << endl;});
//t.reset();
//
//    for(int i = 0; i < matrix.size(); i++)
//    {
//        int counter = 0;
//        for_each(matrix.at(i).begin(), matrix.at(i).end(),
//                 [vector, &resultSum, i, &counter](int x){
//                     resultSum += x*vector.at(counter);
//                     counter++;
//                 }
//        );
//        resultVector.at(i) = resultSum;
////        cout << resultVector.at(i) << "\t";
//        resultSum = 0;
//    }
//    cout << t.elapsed() << " without openMP."<< endl;
//    cout << ompt_get_mtime<< " without openMP."<< endl;



// Task 9
//
//    constexpr uint64_t sizeRaw = 6;
//    constexpr uint64_t sizeCol = 8;
//    vector<vector<int>> matrix(sizeRaw);
//    for ( int i = 0 ; i < sizeRaw ; i++ )
//        matrix[i].resize(sizeCol);
//    std::for_each(matrix.begin(),matrix.end(),
//                  [](std::vector<int> &vec){
//                      vec.resize(sizeCol);
//                      std::for_each(vec.begin(), vec.end(),[](int& x){x=1+rand()%sizeCol;});
//                      std::for_each(vec.begin(),vec.end(),[](int& x){std::cout << x << " ";
//                      });
//                      cout << endl;
//                  });
//
//
//    int minVal = matrix.at(0).at(0);
//    int maxVal = matrix.at(0).at(0);
//    Timer t;
//    omp_set_num_threads(3);
//#pragma omp parallel for
//    for(int i = 0; i < matrix.size(); i++)
//    {
//#pragma omp critical
//        for_each(matrix.at(i).begin(), matrix.at(i).end(),
//                 [&minVal, &maxVal](int x) {
//                     if (x > maxVal) maxVal = x;
//                     if (x < minVal) minVal = x;
//                 }
//        );
//    }
//
//    cout << t.elapsed() << " using parallel for." <<endl;
//    Timer t2;
//
//    cout << minVal << " min." <<endl;
//    cout << maxVal << " max." <<endl;
////
//     minVal = matrix.at(0).at(0);
//     maxVal = matrix.at(0).at(0);
//
//#pragma omp critical
//    for(int i = 0; i < matrix.size(); i++)
//    {
//        for_each(matrix.at(i).begin(), matrix.at(i).end(),
//                 [&minVal, &maxVal](int x){
//                     if(x > maxVal) maxVal = x;
//                     if(x < minVal) minVal = x;
//                 }
//        );
//    }
//    cout << minVal << " min." <<endl;
//    cout << maxVal << " max." <<endl;
//    cout << t2.elapsed() << " with critical." <<endl;


// Task 10
//    constexpr uint64_t size = 30;
//    vector<int > vec(size);
//    std::for_each(vec.begin(), vec.end(),[](int& x){x=1+rand()%size;});
//
//    int counter = 0;
//    omp_set_num_threads(10);
//#pragma  omp parallel for
//    for (int i = 0; i < vec.size(); ++i) {
//        if(vec.at(i) % 9 == 0)
//#pragma omp atomic
//            counter++;
//    }
//
//    cout << counter << " multiplies of 9" << endl;
//    counter = 0;
//
//    for (int i = 0; i < vec.size(); ++i) {
//        if(vec.at(i) % 9 == 0)
//#pragma omp atomic
//            counter++;
//    }
//    cout << counter << " multiplies of 9" << endl;


// Task 11
//    srand(time(NULL));
//    constexpr uint64_t size = 30;
//    vector<int > vec(size);
//    std::for_each(vec.begin(), vec.end(),[](int& x){x=1+rand()%size;});
//    int maxMultOfSeven = -1;
//#pragma omp parallel
//#pragma omp for
//    for (int i = 0; i < vec.size(); ++i) {
//        if (vec.at(i) % 7 == 0 && vec.at(i) > maxMultOfSeven)
//#pragma omp critical
//            maxMultOfSeven = vec.at(i);
//    }
//    cout << maxMultOfSeven << " max multiplies of 7." << endl;


    // Task 12


//    omp_set_num_threads(8);
//    #pragma omp parallel
//    {
//    int id = omp_get_thread_num();
//    int numt = omp_get_num_threads();
//    printf("Thread (%d) of (%d) threads alive. ", id, numt);
//    printf("HelloWorld!\n");
////    cout << "Hello World!" << endl;
//    }
//
//#pragma omp parallel
//    {
//        for(int i=omp_get_num_threads()-1; i>=0; i--)
//        {
//#pragma omp barrier
//            {
//                if(i==omp_get_thread_num())
//                {
//                    cout << "I am thread "<< i <<endl;
//                }
//            }
//        }
//    }
//
//#pragma omp parallel for ordered schedule(static)
//    for (int i = omp_get_num_threads(); i >=0;--i){
//
//#pragma omp ordered
//        cout << "I am thread "<< omp_get_thread_num() <<endl;
//    }


// Task 13

//vector<int> vector = {1,1,1,0,0,0}; // 56
//
//  int number = 0;
//#pragma omp parallel for shared(vector)
//    for(int i = 0; i < vector.size(); i++){
//#pragma omp critical
//        number += vector.at(i)*pow(2,vector.size()-(i+1));
////        cout << number << " number in dec." << endl;
//    }
//
//    cout << number << " number in dec." << endl;

// Task 14

//
//int number = 3;
//int square = 0;
//    #pragma omp parallel for shared(square)
//    for(int i = 0; i <= number*2; i++){
//#pragma omp critical
//        {
//            if(i % 2 == 1)
//            square += i;cout << square << endl;
//    };
////        cout << number << " number in dec." << endl;
//    }
//
//    cout << square << " number in dec." << endl;


// task 15
//    int number = 25;
//    if( number == 2) cout << 2;else
//    if(number < 2) cout << "there is not such numbers";
//#pragma omp parallel for
//    for(int i = 3; i <= number; i++){
//#pragma omp critical
//        {
//            if(i % 2 == 1)
//                cout << i << endl;
//        };
//    }

////////////////////////


//#pragma omp parallel shared(num) //В этот момент создается 4 нити, переменная num у них будет общей
////    omp_set_num_threads(4); //Установить количество нитей
//    {
//        num= num + 1;
////#pragma omp single
//#pragma omp criticald
//        cout << num<<endl; //Вывести номер нити
//        someFunc(num); //Функцию кинутся выполнять все нити параллельно
//        cout << omp_get_th?read_num() << endl; //Вывести номер нити
//
//#pragma omp parallel
//        {
//            cout << num<< endl;
//        }
//    }
//
//#pragma omp for
////в этот момент каждая из нитей возьмет себе по индексу и начнет исполнение цикла
//    for(int i = 0; i < 8; i++) {
//        //блок
//        cout << i<<endl;
//    }

//#pragma omp parallel for private(x) // переменная x объявлена ранее
//    for (int i = 0; i < 500; ++i)
//    {
//      vec.at(i) = i;
//    }
//    cout << "Hello, World!" << std::endl;




    return 0;
}