cmake_minimum_required(Version 2.8)

project(test_ros)
set(SOURCE_EXE main.cpp)
set(SOURCE_LIB /opt/ros/kinetic/lib)
add_library(ros STATIC ${SOURCE_LIB})
add_executable(main ${SOURCE_LIB})
target_link_libraries(main ros)

