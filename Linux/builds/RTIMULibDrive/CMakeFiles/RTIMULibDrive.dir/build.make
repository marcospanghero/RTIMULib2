# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/pi/wasp-p16/platform/RTIMULib2/Linux

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/wasp-p16/platform/RTIMULib2/Linux/builds

# Include any dependencies generated for this target.
include RTIMULibDrive/CMakeFiles/RTIMULibDrive.dir/depend.make

# Include the progress variables for this target.
include RTIMULibDrive/CMakeFiles/RTIMULibDrive.dir/progress.make

# Include the compile flags for this target's objects.
include RTIMULibDrive/CMakeFiles/RTIMULibDrive.dir/flags.make

RTIMULibDrive/CMakeFiles/RTIMULibDrive.dir/RTIMULibDrive.cpp.o: RTIMULibDrive/CMakeFiles/RTIMULibDrive.dir/flags.make
RTIMULibDrive/CMakeFiles/RTIMULibDrive.dir/RTIMULibDrive.cpp.o: ../RTIMULibDrive/RTIMULibDrive.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/wasp-p16/platform/RTIMULib2/Linux/builds/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object RTIMULibDrive/CMakeFiles/RTIMULibDrive.dir/RTIMULibDrive.cpp.o"
	cd /home/pi/wasp-p16/platform/RTIMULib2/Linux/builds/RTIMULibDrive && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RTIMULibDrive.dir/RTIMULibDrive.cpp.o -c /home/pi/wasp-p16/platform/RTIMULib2/Linux/RTIMULibDrive/RTIMULibDrive.cpp

RTIMULibDrive/CMakeFiles/RTIMULibDrive.dir/RTIMULibDrive.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RTIMULibDrive.dir/RTIMULibDrive.cpp.i"
	cd /home/pi/wasp-p16/platform/RTIMULib2/Linux/builds/RTIMULibDrive && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/wasp-p16/platform/RTIMULib2/Linux/RTIMULibDrive/RTIMULibDrive.cpp > CMakeFiles/RTIMULibDrive.dir/RTIMULibDrive.cpp.i

RTIMULibDrive/CMakeFiles/RTIMULibDrive.dir/RTIMULibDrive.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RTIMULibDrive.dir/RTIMULibDrive.cpp.s"
	cd /home/pi/wasp-p16/platform/RTIMULib2/Linux/builds/RTIMULibDrive && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/wasp-p16/platform/RTIMULib2/Linux/RTIMULibDrive/RTIMULibDrive.cpp -o CMakeFiles/RTIMULibDrive.dir/RTIMULibDrive.cpp.s

# Object files for target RTIMULibDrive
RTIMULibDrive_OBJECTS = \
"CMakeFiles/RTIMULibDrive.dir/RTIMULibDrive.cpp.o"

# External object files for target RTIMULibDrive
RTIMULibDrive_EXTERNAL_OBJECTS =

RTIMULibDrive/RTIMULibDrive: RTIMULibDrive/CMakeFiles/RTIMULibDrive.dir/RTIMULibDrive.cpp.o
RTIMULibDrive/RTIMULibDrive: RTIMULibDrive/CMakeFiles/RTIMULibDrive.dir/build.make
RTIMULibDrive/RTIMULibDrive: RTIMULib/libRTIMULib.so.8.1.0
RTIMULibDrive/RTIMULibDrive: RTIMULibDrive/CMakeFiles/RTIMULibDrive.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/wasp-p16/platform/RTIMULib2/Linux/builds/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable RTIMULibDrive"
	cd /home/pi/wasp-p16/platform/RTIMULib2/Linux/builds/RTIMULibDrive && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RTIMULibDrive.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
RTIMULibDrive/CMakeFiles/RTIMULibDrive.dir/build: RTIMULibDrive/RTIMULibDrive

.PHONY : RTIMULibDrive/CMakeFiles/RTIMULibDrive.dir/build

RTIMULibDrive/CMakeFiles/RTIMULibDrive.dir/clean:
	cd /home/pi/wasp-p16/platform/RTIMULib2/Linux/builds/RTIMULibDrive && $(CMAKE_COMMAND) -P CMakeFiles/RTIMULibDrive.dir/cmake_clean.cmake
.PHONY : RTIMULibDrive/CMakeFiles/RTIMULibDrive.dir/clean

RTIMULibDrive/CMakeFiles/RTIMULibDrive.dir/depend:
	cd /home/pi/wasp-p16/platform/RTIMULib2/Linux/builds && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/wasp-p16/platform/RTIMULib2/Linux /home/pi/wasp-p16/platform/RTIMULib2/Linux/RTIMULibDrive /home/pi/wasp-p16/platform/RTIMULib2/Linux/builds /home/pi/wasp-p16/platform/RTIMULib2/Linux/builds/RTIMULibDrive /home/pi/wasp-p16/platform/RTIMULib2/Linux/builds/RTIMULibDrive/CMakeFiles/RTIMULibDrive.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : RTIMULibDrive/CMakeFiles/RTIMULibDrive.dir/depend

