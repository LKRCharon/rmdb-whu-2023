# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/charon/rmdb

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/charon/rmdb/build

# Include any dependencies generated for this target.
include src/replacer/CMakeFiles/lru_replacer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/replacer/CMakeFiles/lru_replacer.dir/compiler_depend.make

# Include the progress variables for this target.
include src/replacer/CMakeFiles/lru_replacer.dir/progress.make

# Include the compile flags for this target's objects.
include src/replacer/CMakeFiles/lru_replacer.dir/flags.make

src/replacer/CMakeFiles/lru_replacer.dir/lru_replacer.cpp.o: src/replacer/CMakeFiles/lru_replacer.dir/flags.make
src/replacer/CMakeFiles/lru_replacer.dir/lru_replacer.cpp.o: /home/charon/rmdb/src/replacer/lru_replacer.cpp
src/replacer/CMakeFiles/lru_replacer.dir/lru_replacer.cpp.o: src/replacer/CMakeFiles/lru_replacer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/charon/rmdb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/replacer/CMakeFiles/lru_replacer.dir/lru_replacer.cpp.o"
	cd /home/charon/rmdb/build/src/replacer && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/replacer/CMakeFiles/lru_replacer.dir/lru_replacer.cpp.o -MF CMakeFiles/lru_replacer.dir/lru_replacer.cpp.o.d -o CMakeFiles/lru_replacer.dir/lru_replacer.cpp.o -c /home/charon/rmdb/src/replacer/lru_replacer.cpp

src/replacer/CMakeFiles/lru_replacer.dir/lru_replacer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lru_replacer.dir/lru_replacer.cpp.i"
	cd /home/charon/rmdb/build/src/replacer && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/charon/rmdb/src/replacer/lru_replacer.cpp > CMakeFiles/lru_replacer.dir/lru_replacer.cpp.i

src/replacer/CMakeFiles/lru_replacer.dir/lru_replacer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lru_replacer.dir/lru_replacer.cpp.s"
	cd /home/charon/rmdb/build/src/replacer && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/charon/rmdb/src/replacer/lru_replacer.cpp -o CMakeFiles/lru_replacer.dir/lru_replacer.cpp.s

# Object files for target lru_replacer
lru_replacer_OBJECTS = \
"CMakeFiles/lru_replacer.dir/lru_replacer.cpp.o"

# External object files for target lru_replacer
lru_replacer_EXTERNAL_OBJECTS =

lib/liblru_replacer.a: src/replacer/CMakeFiles/lru_replacer.dir/lru_replacer.cpp.o
lib/liblru_replacer.a: src/replacer/CMakeFiles/lru_replacer.dir/build.make
lib/liblru_replacer.a: src/replacer/CMakeFiles/lru_replacer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/charon/rmdb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../lib/liblru_replacer.a"
	cd /home/charon/rmdb/build/src/replacer && $(CMAKE_COMMAND) -P CMakeFiles/lru_replacer.dir/cmake_clean_target.cmake
	cd /home/charon/rmdb/build/src/replacer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lru_replacer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/replacer/CMakeFiles/lru_replacer.dir/build: lib/liblru_replacer.a
.PHONY : src/replacer/CMakeFiles/lru_replacer.dir/build

src/replacer/CMakeFiles/lru_replacer.dir/clean:
	cd /home/charon/rmdb/build/src/replacer && $(CMAKE_COMMAND) -P CMakeFiles/lru_replacer.dir/cmake_clean.cmake
.PHONY : src/replacer/CMakeFiles/lru_replacer.dir/clean

src/replacer/CMakeFiles/lru_replacer.dir/depend:
	cd /home/charon/rmdb/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/charon/rmdb /home/charon/rmdb/src/replacer /home/charon/rmdb/build /home/charon/rmdb/build/src/replacer /home/charon/rmdb/build/src/replacer/CMakeFiles/lru_replacer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/replacer/CMakeFiles/lru_replacer.dir/depend

