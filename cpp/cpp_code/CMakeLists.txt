cmake_minimum_required(VERSION 3.14)
project(cpp_code)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(cpp_code main.cpp STL.cpp STL.h multithreading.cpp multithreading.h features.cpp features.h features.h List.h MyString.cpp MyString.h tests/Test.cpp tests/Test.h List.cpp patterns/Adapter.cpp patterns/Adapter.h cpp_extra/CppTopics.cpp cpp_extra/CppTopics.h feature2.cpp feature2.h Vector.cpp Vector.h Student.cpp Student.h Stack.cpp Stack.h Array.cpp Array.h Queue.cpp Queue.h cppSerializationProgram.h)

target_link_libraries(cpp_code gtest gtest_main)
