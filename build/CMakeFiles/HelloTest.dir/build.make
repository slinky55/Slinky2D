# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/209/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/209/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/slinky/Slinky2D

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/slinky/Slinky2D/build

# Include any dependencies generated for this target.
include CMakeFiles/HelloTest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/HelloTest.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/HelloTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HelloTest.dir/flags.make

CMakeFiles/HelloTest.dir/tests/AABBTest.cpp.o: CMakeFiles/HelloTest.dir/flags.make
CMakeFiles/HelloTest.dir/tests/AABBTest.cpp.o: ../tests/AABBTest.cpp
CMakeFiles/HelloTest.dir/tests/AABBTest.cpp.o: CMakeFiles/HelloTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/slinky/Slinky2D/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HelloTest.dir/tests/AABBTest.cpp.o"
	/bin/x86_64-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HelloTest.dir/tests/AABBTest.cpp.o -MF CMakeFiles/HelloTest.dir/tests/AABBTest.cpp.o.d -o CMakeFiles/HelloTest.dir/tests/AABBTest.cpp.o -c /home/slinky/Slinky2D/tests/AABBTest.cpp

CMakeFiles/HelloTest.dir/tests/AABBTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HelloTest.dir/tests/AABBTest.cpp.i"
	/bin/x86_64-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/slinky/Slinky2D/tests/AABBTest.cpp > CMakeFiles/HelloTest.dir/tests/AABBTest.cpp.i

CMakeFiles/HelloTest.dir/tests/AABBTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HelloTest.dir/tests/AABBTest.cpp.s"
	/bin/x86_64-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/slinky/Slinky2D/tests/AABBTest.cpp -o CMakeFiles/HelloTest.dir/tests/AABBTest.cpp.s

# Object files for target HelloTest
HelloTest_OBJECTS = \
"CMakeFiles/HelloTest.dir/tests/AABBTest.cpp.o"

# External object files for target HelloTest
HelloTest_EXTERNAL_OBJECTS =

HelloTest: CMakeFiles/HelloTest.dir/tests/AABBTest.cpp.o
HelloTest: CMakeFiles/HelloTest.dir/build.make
HelloTest: lib/libgtest_main.so.1.12.1
HelloTest: libSlinky2D.a
HelloTest: lib/libgtest.so.1.12.1
HelloTest: CMakeFiles/HelloTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/slinky/Slinky2D/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable HelloTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HelloTest.dir/link.txt --verbose=$(VERBOSE)
	/snap/clion/209/bin/cmake/linux/bin/cmake -D TEST_TARGET=HelloTest -D TEST_EXECUTABLE=/home/slinky/Slinky2D/build/HelloTest -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/slinky/Slinky2D/build -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_FILTER= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=HelloTest_TESTS -D CTEST_FILE=/home/slinky/Slinky2D/build/HelloTest[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -D TEST_XML_OUTPUT_DIR= -P /snap/clion/209/bin/cmake/linux/share/cmake-3.23/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
CMakeFiles/HelloTest.dir/build: HelloTest
.PHONY : CMakeFiles/HelloTest.dir/build

CMakeFiles/HelloTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HelloTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HelloTest.dir/clean

CMakeFiles/HelloTest.dir/depend:
	cd /home/slinky/Slinky2D/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/slinky/Slinky2D /home/slinky/Slinky2D /home/slinky/Slinky2D/build /home/slinky/Slinky2D/build /home/slinky/Slinky2D/build/CMakeFiles/HelloTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HelloTest.dir/depend

