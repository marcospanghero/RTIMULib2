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
include WASPDriver/CMakeFiles/WASPDriver.dir/depend.make

# Include the progress variables for this target.
include WASPDriver/CMakeFiles/WASPDriver.dir/progress.make

# Include the compile flags for this target's objects.
include WASPDriver/CMakeFiles/WASPDriver.dir/flags.make

WASPDriver/CMakeFiles/WASPDriver.dir/WASPDriver.cpp.o: WASPDriver/CMakeFiles/WASPDriver.dir/flags.make
WASPDriver/CMakeFiles/WASPDriver.dir/WASPDriver.cpp.o: ../WASPDriver/WASPDriver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/wasp-p16/platform/RTIMULib2/Linux/builds/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object WASPDriver/CMakeFiles/WASPDriver.dir/WASPDriver.cpp.o"
	cd /home/pi/wasp-p16/platform/RTIMULib2/Linux/builds/WASPDriver && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WASPDriver.dir/WASPDriver.cpp.o -c /home/pi/wasp-p16/platform/RTIMULib2/Linux/WASPDriver/WASPDriver.cpp

WASPDriver/CMakeFiles/WASPDriver.dir/WASPDriver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WASPDriver.dir/WASPDriver.cpp.i"
	cd /home/pi/wasp-p16/platform/RTIMULib2/Linux/builds/WASPDriver && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/wasp-p16/platform/RTIMULib2/Linux/WASPDriver/WASPDriver.cpp > CMakeFiles/WASPDriver.dir/WASPDriver.cpp.i

WASPDriver/CMakeFiles/WASPDriver.dir/WASPDriver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WASPDriver.dir/WASPDriver.cpp.s"
	cd /home/pi/wasp-p16/platform/RTIMULib2/Linux/builds/WASPDriver && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/wasp-p16/platform/RTIMULib2/Linux/WASPDriver/WASPDriver.cpp -o CMakeFiles/WASPDriver.dir/WASPDriver.cpp.s

# Object files for target WASPDriver
WASPDriver_OBJECTS = \
"CMakeFiles/WASPDriver.dir/WASPDriver.cpp.o"

# External object files for target WASPDriver
WASPDriver_EXTERNAL_OBJECTS =

WASPDriver/WASPDriver: WASPDriver/CMakeFiles/WASPDriver.dir/WASPDriver.cpp.o
WASPDriver/WASPDriver: WASPDriver/CMakeFiles/WASPDriver.dir/build.make
WASPDriver/WASPDriver: RTIMULib/libRTIMULib.so.8.1.0
WASPDriver/WASPDriver: WASPDriver/CMakeFiles/WASPDriver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/wasp-p16/platform/RTIMULib2/Linux/builds/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable WASPDriver"
	cd /home/pi/wasp-p16/platform/RTIMULib2/Linux/builds/WASPDriver && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/WASPDriver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
WASPDriver/CMakeFiles/WASPDriver.dir/build: WASPDriver/WASPDriver

.PHONY : WASPDriver/CMakeFiles/WASPDriver.dir/build

WASPDriver/CMakeFiles/WASPDriver.dir/clean:
	cd /home/pi/wasp-p16/platform/RTIMULib2/Linux/builds/WASPDriver && $(CMAKE_COMMAND) -P CMakeFiles/WASPDriver.dir/cmake_clean.cmake
.PHONY : WASPDriver/CMakeFiles/WASPDriver.dir/clean

WASPDriver/CMakeFiles/WASPDriver.dir/depend:
	cd /home/pi/wasp-p16/platform/RTIMULib2/Linux/builds && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/wasp-p16/platform/RTIMULib2/Linux /home/pi/wasp-p16/platform/RTIMULib2/Linux/WASPDriver /home/pi/wasp-p16/platform/RTIMULib2/Linux/builds /home/pi/wasp-p16/platform/RTIMULib2/Linux/builds/WASPDriver /home/pi/wasp-p16/platform/RTIMULib2/Linux/builds/WASPDriver/CMakeFiles/WASPDriver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : WASPDriver/CMakeFiles/WASPDriver.dir/depend
