# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.24.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.24.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/shaft/Slinky2D

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/shaft/Slinky2D

# Include any dependencies generated for this target.
include CMakeFiles/AABBTest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/AABBTest.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/AABBTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AABBTest.dir/flags.make

CMakeFiles/AABBTest.dir/tests/AABBTest.cpp.o: CMakeFiles/AABBTest.dir/flags.make
CMakeFiles/AABBTest.dir/tests/AABBTest.cpp.o: tests/AABBTest.cpp
CMakeFiles/AABBTest.dir/tests/AABBTest.cpp.o: CMakeFiles/AABBTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/shaft/Slinky2D/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AABBTest.dir/tests/AABBTest.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/AABBTest.dir/tests/AABBTest.cpp.o -MF CMakeFiles/AABBTest.dir/tests/AABBTest.cpp.o.d -o CMakeFiles/AABBTest.dir/tests/AABBTest.cpp.o -c /Users/shaft/Slinky2D/tests/AABBTest.cpp

CMakeFiles/AABBTest.dir/tests/AABBTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AABBTest.dir/tests/AABBTest.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shaft/Slinky2D/tests/AABBTest.cpp > CMakeFiles/AABBTest.dir/tests/AABBTest.cpp.i

CMakeFiles/AABBTest.dir/tests/AABBTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AABBTest.dir/tests/AABBTest.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shaft/Slinky2D/tests/AABBTest.cpp -o CMakeFiles/AABBTest.dir/tests/AABBTest.cpp.s

# Object files for target AABBTest
AABBTest_OBJECTS = \
"CMakeFiles/AABBTest.dir/tests/AABBTest.cpp.o"

# External object files for target AABBTest
AABBTest_EXTERNAL_OBJECTS =

AABBTest: CMakeFiles/AABBTest.dir/tests/AABBTest.cpp.o
AABBTest: CMakeFiles/AABBTest.dir/build.make
AABBTest: lib/libgtest_main.a
AABBTest: libSlinky2D.a
AABBTest: lib/libgtest.a
AABBTest: CMakeFiles/AABBTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/shaft/Slinky2D/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable AABBTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AABBTest.dir/link.txt --verbose=$(VERBOSE)
	/usr/local/Cellar/cmake/3.24.2/bin/cmake -D TEST_TARGET=AABBTest -D TEST_EXECUTABLE=/Users/shaft/Slinky2D/AABBTest -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/Users/shaft/Slinky2D -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_FILTER= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=AABBTest_TESTS -D CTEST_FILE=/Users/shaft/Slinky2D/AABBTest[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -D TEST_XML_OUTPUT_DIR= -P /usr/local/Cellar/cmake/3.24.2/share/cmake/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
CMakeFiles/AABBTest.dir/build: AABBTest
.PHONY : CMakeFiles/AABBTest.dir/build

CMakeFiles/AABBTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AABBTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AABBTest.dir/clean

CMakeFiles/AABBTest.dir/depend:
	cd /Users/shaft/Slinky2D && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/shaft/Slinky2D /Users/shaft/Slinky2D /Users/shaft/Slinky2D /Users/shaft/Slinky2D /Users/shaft/Slinky2D/CMakeFiles/AABBTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AABBTest.dir/depend
