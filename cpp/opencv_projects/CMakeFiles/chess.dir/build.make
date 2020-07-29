# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/northlight/SolarSystem/cpp/opencv_projects

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/northlight/SolarSystem/cpp/opencv_projects

# Include any dependencies generated for this target.
include CMakeFiles/chess.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/chess.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/chess.dir/flags.make

CMakeFiles/chess.dir/apps/chess.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/apps/chess.cpp.o: apps/chess.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/northlight/SolarSystem/cpp/opencv_projects/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/chess.dir/apps/chess.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chess.dir/apps/chess.cpp.o -c /home/northlight/SolarSystem/cpp/opencv_projects/apps/chess.cpp

CMakeFiles/chess.dir/apps/chess.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chess.dir/apps/chess.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/northlight/SolarSystem/cpp/opencv_projects/apps/chess.cpp > CMakeFiles/chess.dir/apps/chess.cpp.i

CMakeFiles/chess.dir/apps/chess.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chess.dir/apps/chess.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/northlight/SolarSystem/cpp/opencv_projects/apps/chess.cpp -o CMakeFiles/chess.dir/apps/chess.cpp.s

CMakeFiles/chess.dir/apps/chess.cpp.o.requires:

.PHONY : CMakeFiles/chess.dir/apps/chess.cpp.o.requires

CMakeFiles/chess.dir/apps/chess.cpp.o.provides: CMakeFiles/chess.dir/apps/chess.cpp.o.requires
	$(MAKE) -f CMakeFiles/chess.dir/build.make CMakeFiles/chess.dir/apps/chess.cpp.o.provides.build
.PHONY : CMakeFiles/chess.dir/apps/chess.cpp.o.provides

CMakeFiles/chess.dir/apps/chess.cpp.o.provides.build: CMakeFiles/chess.dir/apps/chess.cpp.o


# Object files for target chess
chess_OBJECTS = \
"CMakeFiles/chess.dir/apps/chess.cpp.o"

# External object files for target chess
chess_EXTERNAL_OBJECTS =

bin/chess: CMakeFiles/chess.dir/apps/chess.cpp.o
bin/chess: CMakeFiles/chess.dir/build.make
bin/chess: lib/libopencv_projects.so
bin/chess: /usr/local/lib/libopencv_stitching.so.3.4.0
bin/chess: /usr/local/lib/libopencv_superres.so.3.4.0
bin/chess: /usr/local/lib/libopencv_videostab.so.3.4.0
bin/chess: /usr/local/lib/libopencv_aruco.so.3.4.0
bin/chess: /usr/local/lib/libopencv_bgsegm.so.3.4.0
bin/chess: /usr/local/lib/libopencv_bioinspired.so.3.4.0
bin/chess: /usr/local/lib/libopencv_ccalib.so.3.4.0
bin/chess: /usr/local/lib/libopencv_dpm.so.3.4.0
bin/chess: /usr/local/lib/libopencv_face.so.3.4.0
bin/chess: /usr/local/lib/libopencv_photo.so.3.4.0
bin/chess: /usr/local/lib/libopencv_freetype.so.3.4.0
bin/chess: /usr/local/lib/libopencv_fuzzy.so.3.4.0
bin/chess: /usr/local/lib/libopencv_img_hash.so.3.4.0
bin/chess: /usr/local/lib/libopencv_line_descriptor.so.3.4.0
bin/chess: /usr/local/lib/libopencv_optflow.so.3.4.0
bin/chess: /usr/local/lib/libopencv_reg.so.3.4.0
bin/chess: /usr/local/lib/libopencv_rgbd.so.3.4.0
bin/chess: /usr/local/lib/libopencv_saliency.so.3.4.0
bin/chess: /usr/local/lib/libopencv_stereo.so.3.4.0
bin/chess: /usr/local/lib/libopencv_structured_light.so.3.4.0
bin/chess: /usr/local/lib/libopencv_phase_unwrapping.so.3.4.0
bin/chess: /usr/local/lib/libopencv_surface_matching.so.3.4.0
bin/chess: /usr/local/lib/libopencv_tracking.so.3.4.0
bin/chess: /usr/local/lib/libopencv_datasets.so.3.4.0
bin/chess: /usr/local/lib/libopencv_plot.so.3.4.0
bin/chess: /usr/local/lib/libopencv_text.so.3.4.0
bin/chess: /usr/local/lib/libopencv_dnn.so.3.4.0
bin/chess: /usr/local/lib/libopencv_xfeatures2d.so.3.4.0
bin/chess: /usr/local/lib/libopencv_ml.so.3.4.0
bin/chess: /usr/local/lib/libopencv_shape.so.3.4.0
bin/chess: /usr/local/lib/libopencv_video.so.3.4.0
bin/chess: /usr/local/lib/libopencv_ximgproc.so.3.4.0
bin/chess: /usr/local/lib/libopencv_calib3d.so.3.4.0
bin/chess: /usr/local/lib/libopencv_features2d.so.3.4.0
bin/chess: /usr/local/lib/libopencv_flann.so.3.4.0
bin/chess: /usr/local/lib/libopencv_highgui.so.3.4.0
bin/chess: /usr/local/lib/libopencv_videoio.so.3.4.0
bin/chess: /usr/local/lib/libopencv_xobjdetect.so.3.4.0
bin/chess: /usr/local/lib/libopencv_imgcodecs.so.3.4.0
bin/chess: /usr/local/lib/libopencv_objdetect.so.3.4.0
bin/chess: /usr/local/lib/libopencv_xphoto.so.3.4.0
bin/chess: /usr/local/lib/libopencv_imgproc.so.3.4.0
bin/chess: /usr/local/lib/libopencv_core.so.3.4.0
bin/chess: CMakeFiles/chess.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/northlight/SolarSystem/cpp/opencv_projects/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/chess"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/chess.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/chess.dir/build: bin/chess

.PHONY : CMakeFiles/chess.dir/build

CMakeFiles/chess.dir/requires: CMakeFiles/chess.dir/apps/chess.cpp.o.requires

.PHONY : CMakeFiles/chess.dir/requires

CMakeFiles/chess.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/chess.dir/cmake_clean.cmake
.PHONY : CMakeFiles/chess.dir/clean

CMakeFiles/chess.dir/depend:
	cd /home/northlight/SolarSystem/cpp/opencv_projects && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/northlight/SolarSystem/cpp/opencv_projects /home/northlight/SolarSystem/cpp/opencv_projects /home/northlight/SolarSystem/cpp/opencv_projects /home/northlight/SolarSystem/cpp/opencv_projects /home/northlight/SolarSystem/cpp/opencv_projects/CMakeFiles/chess.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/chess.dir/depend
