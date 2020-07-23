project( opencv_projects )

cmake_minimum_required(VERSION 3.0)

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Build type automatically set to 'Release'")
    set(CMAKE_BUILD_TYPE "Release" )
else(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Build type: '${CMAKE_BUILD_TYPE}'") 
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(STATUS "WARNING: you will get poor performance!")
    endif(CMAKE_BUILD_TYPE STREQUAL "Debug")
endif(NOT CMAKE_BUILD_TYPE)

set (CMAKE_CXX_STANDARD 14)
option(USE_SSE "Build with SSE3+ support" ON)
option(USE_AVX "Build with AVX/AVX2 support" OFF)
option(USE_NEON "Build with NEON support" OFF)
option(USE_CAFFE_TRIPLET "Build with Caffe Triplet CNN support" OFF)
### ZED
option(LINK_SHARED_ZED "Link with the ZED SDK shared executable" ON)

if (NOT LINK_SHARED_ZED AND MSVC)
    message(FATAL_ERROR "LINK_SHARED_ZED OFF : ZED SDK static libraries not available on Windows")
endif()

if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 OLD)
	cmake_policy(SET CMP0015 OLD)
endif(COMMAND cmake_policy)

if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
SET(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()


#################################


set(CMAKE_CURRENT_SOURCE_DIR /home/northlight/SolarSystem/cpp/opencv_projects)
# This is to be complinat with OpenCV >= 3.3.1
set(EXTRA_CXX_FLAGS "${EXTRA_CXX_FLAGS} -DOPENCV_TRAITS_ENABLE_DEPRECATED")
  
  set(EXTRA_CXX_FLAGS "${EXTRA_CXX_FLAGS} -Wall -Wpedantic -Wno-narrowing -Wno-deprecated -std=c++14 -march=nocona")
  
find_package(OpenCV REQUIRED PATHS /usr/local/share/OpenCV NO_DEFAULT_PATH)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

if(NOT DEFINED EIGEN3_INCLUDE_DIR)
  find_path(EIGEN3_INCLUDE_DIR eigen3)
endif(NOT DEFINED EIGEN3_INCLUDE_DIR)
include_directories( ./include
                      /usr/include
                      /usr/local/include
		      /usr/local/include/opencv2
                      ${OpenCV_INCLUDE_DIRS}
                      ${Boost_INCLUDE_DIRS}
                      ${EIGEN3_INCLUDE_DIR}
	              ${PATH_INCLUDE_OPENCV}
/opt/ros/kinetic/include
)

if(USE_CAFFE_TRIPLET)
  find_library(Caffe_LIBS NAMES caffe HINTS /opt/caffe_triplet/lib)
  include_directories(/opt/caffe_triplet/include)
endif(USE_CAFFE_TRIPLET)                      

aux_source_directory( src OPENCV_PROJECTS_SRC )
message(STATUS "OpenCV_INCLUDE_DIRS = ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV_LIBS = ${OpenCV_LIBS}")
message(STATUS "OPENCV_PROJECTS_SRC = ${OPENCV_PROJECTS_SRC}")
link_directories(/opt/ros/kinetic/lib)

##############################ZED
target_link_libraries( opencv_projects PUBLIC
                       ${Boost_LIBRARIES}
                       ${OpenCV_LIBS}
### ROS for NODE
                       -I/opt/ros/kinetic/include -L/opt/ros/kinetic/lib
-lroscpp -lrostime -lrosconsole -lroscpp_serialization -lxmlrpcpp -lcpp_common -lrosconsole_log4cxx -lrosconsole_backend_interface
-linteractive_markers
)

###create d2co library

set_target_properties(opencv_projects PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set_target_properties(opencv_projects PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

add_executable(track_object apps/track_object.cpp)
target_link_libraries( detect_object
                       opencv_projects
### ROS for NODE
#                       -I/opt/ros/kinetic/include -L/opt/ros/kinetic/lib
#-lroscpp -lrostime -lrosconsole -lroscpp_serialization -lxmlrpcpp -lcpp_common -lrosconsole_log4cxx -lrosconsole_backend_interface
#-linteractive_markers
)

set_target_properties( track_object PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
 
