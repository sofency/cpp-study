# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.28.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.28.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/sofency/vscode/cpp_learn/12-cmake/study

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/sofency/vscode/cpp_learn/12-cmake/study/build

# Include any dependencies generated for this target.
include CMakeFiles/Main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Main.dir/flags.make

CMakeFiles/Main.dir/main.cpp.o: CMakeFiles/Main.dir/flags.make
CMakeFiles/Main.dir/main.cpp.o: /Users/sofency/vscode/cpp_learn/12-cmake/study/main.cpp
CMakeFiles/Main.dir/main.cpp.o: CMakeFiles/Main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/sofency/vscode/cpp_learn/12-cmake/study/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Main.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Main.dir/main.cpp.o -MF CMakeFiles/Main.dir/main.cpp.o.d -o CMakeFiles/Main.dir/main.cpp.o -c /Users/sofency/vscode/cpp_learn/12-cmake/study/main.cpp

CMakeFiles/Main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Main.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sofency/vscode/cpp_learn/12-cmake/study/main.cpp > CMakeFiles/Main.dir/main.cpp.i

CMakeFiles/Main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Main.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sofency/vscode/cpp_learn/12-cmake/study/main.cpp -o CMakeFiles/Main.dir/main.cpp.s

CMakeFiles/Main.dir/src/compute.cpp.o: CMakeFiles/Main.dir/flags.make
CMakeFiles/Main.dir/src/compute.cpp.o: /Users/sofency/vscode/cpp_learn/12-cmake/study/src/compute.cpp
CMakeFiles/Main.dir/src/compute.cpp.o: CMakeFiles/Main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/sofency/vscode/cpp_learn/12-cmake/study/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Main.dir/src/compute.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Main.dir/src/compute.cpp.o -MF CMakeFiles/Main.dir/src/compute.cpp.o.d -o CMakeFiles/Main.dir/src/compute.cpp.o -c /Users/sofency/vscode/cpp_learn/12-cmake/study/src/compute.cpp

CMakeFiles/Main.dir/src/compute.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Main.dir/src/compute.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sofency/vscode/cpp_learn/12-cmake/study/src/compute.cpp > CMakeFiles/Main.dir/src/compute.cpp.i

CMakeFiles/Main.dir/src/compute.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Main.dir/src/compute.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sofency/vscode/cpp_learn/12-cmake/study/src/compute.cpp -o CMakeFiles/Main.dir/src/compute.cpp.s

# Object files for target Main
Main_OBJECTS = \
"CMakeFiles/Main.dir/main.cpp.o" \
"CMakeFiles/Main.dir/src/compute.cpp.o"

# External object files for target Main
Main_EXTERNAL_OBJECTS =

/Users/sofency/vscode/cpp_learn/12-cmake/study/bin/Main: CMakeFiles/Main.dir/main.cpp.o
/Users/sofency/vscode/cpp_learn/12-cmake/study/bin/Main: CMakeFiles/Main.dir/src/compute.cpp.o
/Users/sofency/vscode/cpp_learn/12-cmake/study/bin/Main: CMakeFiles/Main.dir/build.make
/Users/sofency/vscode/cpp_learn/12-cmake/study/bin/Main: CMakeFiles/Main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/sofency/vscode/cpp_learn/12-cmake/study/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable /Users/sofency/vscode/cpp_learn/12-cmake/study/bin/Main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Main.dir/build: /Users/sofency/vscode/cpp_learn/12-cmake/study/bin/Main
.PHONY : CMakeFiles/Main.dir/build

CMakeFiles/Main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Main.dir/clean

CMakeFiles/Main.dir/depend:
	cd /Users/sofency/vscode/cpp_learn/12-cmake/study/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sofency/vscode/cpp_learn/12-cmake/study /Users/sofency/vscode/cpp_learn/12-cmake/study /Users/sofency/vscode/cpp_learn/12-cmake/study/build /Users/sofency/vscode/cpp_learn/12-cmake/study/build /Users/sofency/vscode/cpp_learn/12-cmake/study/build/CMakeFiles/Main.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Main.dir/depend

