# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/admin/learning/operatingSystem/pj2/PJ2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/admin/learning/operatingSystem/pj2/PJ2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/PJ2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PJ2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PJ2.dir/flags.make

CMakeFiles/PJ2.dir/code/src/library/disk.cpp.o: CMakeFiles/PJ2.dir/flags.make
CMakeFiles/PJ2.dir/code/src/library/disk.cpp.o: ../code/src/library/disk.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/admin/learning/operatingSystem/pj2/PJ2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PJ2.dir/code/src/library/disk.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PJ2.dir/code/src/library/disk.cpp.o -c /Users/admin/learning/operatingSystem/pj2/PJ2/code/src/library/disk.cpp

CMakeFiles/PJ2.dir/code/src/library/disk.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PJ2.dir/code/src/library/disk.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/admin/learning/operatingSystem/pj2/PJ2/code/src/library/disk.cpp > CMakeFiles/PJ2.dir/code/src/library/disk.cpp.i

CMakeFiles/PJ2.dir/code/src/library/disk.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PJ2.dir/code/src/library/disk.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/admin/learning/operatingSystem/pj2/PJ2/code/src/library/disk.cpp -o CMakeFiles/PJ2.dir/code/src/library/disk.cpp.s

CMakeFiles/PJ2.dir/code/src/library/fs.cpp.o: CMakeFiles/PJ2.dir/flags.make
CMakeFiles/PJ2.dir/code/src/library/fs.cpp.o: ../code/src/library/fs.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/admin/learning/operatingSystem/pj2/PJ2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/PJ2.dir/code/src/library/fs.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PJ2.dir/code/src/library/fs.cpp.o -c /Users/admin/learning/operatingSystem/pj2/PJ2/code/src/library/fs.cpp

CMakeFiles/PJ2.dir/code/src/library/fs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PJ2.dir/code/src/library/fs.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/admin/learning/operatingSystem/pj2/PJ2/code/src/library/fs.cpp > CMakeFiles/PJ2.dir/code/src/library/fs.cpp.i

CMakeFiles/PJ2.dir/code/src/library/fs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PJ2.dir/code/src/library/fs.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/admin/learning/operatingSystem/pj2/PJ2/code/src/library/fs.cpp -o CMakeFiles/PJ2.dir/code/src/library/fs.cpp.s

CMakeFiles/PJ2.dir/code/src/shell/sfssh.cpp.o: CMakeFiles/PJ2.dir/flags.make
CMakeFiles/PJ2.dir/code/src/shell/sfssh.cpp.o: ../code/src/shell/sfssh.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/admin/learning/operatingSystem/pj2/PJ2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/PJ2.dir/code/src/shell/sfssh.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PJ2.dir/code/src/shell/sfssh.cpp.o -c /Users/admin/learning/operatingSystem/pj2/PJ2/code/src/shell/sfssh.cpp

CMakeFiles/PJ2.dir/code/src/shell/sfssh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PJ2.dir/code/src/shell/sfssh.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/admin/learning/operatingSystem/pj2/PJ2/code/src/shell/sfssh.cpp > CMakeFiles/PJ2.dir/code/src/shell/sfssh.cpp.i

CMakeFiles/PJ2.dir/code/src/shell/sfssh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PJ2.dir/code/src/shell/sfssh.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/admin/learning/operatingSystem/pj2/PJ2/code/src/shell/sfssh.cpp -o CMakeFiles/PJ2.dir/code/src/shell/sfssh.cpp.s

# Object files for target PJ2
PJ2_OBJECTS = \
"CMakeFiles/PJ2.dir/code/src/library/disk.cpp.o" \
"CMakeFiles/PJ2.dir/code/src/library/fs.cpp.o" \
"CMakeFiles/PJ2.dir/code/src/shell/sfssh.cpp.o"

# External object files for target PJ2
PJ2_EXTERNAL_OBJECTS =

PJ2: CMakeFiles/PJ2.dir/code/src/library/disk.cpp.o
PJ2: CMakeFiles/PJ2.dir/code/src/library/fs.cpp.o
PJ2: CMakeFiles/PJ2.dir/code/src/shell/sfssh.cpp.o
PJ2: CMakeFiles/PJ2.dir/build.make
PJ2: CMakeFiles/PJ2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/admin/learning/operatingSystem/pj2/PJ2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable PJ2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PJ2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PJ2.dir/build: PJ2

.PHONY : CMakeFiles/PJ2.dir/build

CMakeFiles/PJ2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PJ2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PJ2.dir/clean

CMakeFiles/PJ2.dir/depend:
	cd /Users/admin/learning/operatingSystem/pj2/PJ2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/admin/learning/operatingSystem/pj2/PJ2 /Users/admin/learning/operatingSystem/pj2/PJ2 /Users/admin/learning/operatingSystem/pj2/PJ2/cmake-build-debug /Users/admin/learning/operatingSystem/pj2/PJ2/cmake-build-debug /Users/admin/learning/operatingSystem/pj2/PJ2/cmake-build-debug/CMakeFiles/PJ2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PJ2.dir/depend

