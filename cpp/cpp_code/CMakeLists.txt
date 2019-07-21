cmake_minimum_required(VERSION 3.14)
project(cpp_code)
#set(BOOST_ROOT C:/Users/X/Desktop/ws/c++/libs/boost)
#set(Boost_LIBRARY_DIR C:/Users/X/Desktop/ws/c++/libs/boost/lib/cmake)
#set(Boost_INCLUDE_DIR ${BOOST_ROOT}/include/boost-1_70)
#set(CMAKE_CXX_STANDARD 14)
#set(Boost_USE_STATIC_LIBS ON)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME ON)
#find_package(Boost 1.70.0 COMPONENTS system)
#
#if(Boost_FOUND)
#    include_directories(${Boost_INCLUDE_DIRS})
#    target_link_libraries(cpp_code ${Boost_LIBRARY_DIR})
#endif()

SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/Users/X/Desktop/ws/c++/libs/boost/include")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/Users/X/Desktop/ws/c++/libs/boost/lib")
FIND_PACKAGE(Boost COMPONENTS)

IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
#    target_link_libraries(cpp_code ${CMAKE_LIBRARY_PATH} "C:/Users/X/Desktop/ws/c++/libs/boost/lib")
ENDIF()
#OpenCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )


add_subdirectory(lib/googletest-master)

include_directories(lib/googletest-master/googlemock/include)
include_directories(lib/googletest-master/googlemock/include)


add_executable(cpp_code main.cpp STL.cpp STL.h multithreading.cpp multithreading.h features.cpp features.h features.h List.h MyString.cpp MyString.h tests/Test.cpp tests/Test.h List.cpp patterns/Adapter.cpp patterns/Adapter.h cpp_extra/CppTopics.cpp cpp_extra/CppTopics.h feature2.cpp feature2.h Vector.cpp Vector.h Student.cpp Student.h Stack.cpp Stack.h Array.cpp Array.h Queue.cpp Queue.h cppSerializationProgram.h MoveSemantic.h OpenCV.cpp OpenCV.h)


target_link_libraries(cpp_code gtest gtest_main)
target_link_libraries(
        cpp_code
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
)
target_link_libraries( cpp_code ${OpenCV_LIBS} )


