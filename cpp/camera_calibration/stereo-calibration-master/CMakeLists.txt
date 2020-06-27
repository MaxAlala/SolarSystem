cmake_minimum_required(VERSION 2.8.11)
project(CALIB_CAM)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(OpenCV REQUIRED PATHS /usr/local/share/OpenCV NO_DEFAULT_PATH)
find_package( Boost COMPONENTS program_options filesystem system REQUIRED )

include_directories(
  ${Boost_INCLUDE_DIRS}
                     ./include
                      /usr/include
                      /usr/local/include
		      /usr/local/include/opencv2
$(OpenCV_INCLUDE_DIRS))

add_executable(renamefileapp RenameFilesApp.cpp)
target_link_libraries(renamefileapp  ${Boost_LIBRARIES})


add_executable(calib2 calib2.cpp)
target_link_libraries(calib2 ${OpenCV_LIBS})


add_executable(calibrate calib_intrinsic.cpp popt_pp.h)
target_link_libraries(calibrate ${OpenCV_LIBS} "-lpopt")

add_executable(read read_images.cpp)
target_link_libraries(read ${OpenCV_LIBS} "-lpopt")

add_executable(calibrate_stereo calib_stereo.cpp)
target_link_libraries(calibrate_stereo ${OpenCV_LIBS} "-lpopt")

add_executable(undistort_rectify undistort_rectify.cpp)
target_link_libraries(undistort_rectify ${OpenCV_LIBS} "-lpopt")