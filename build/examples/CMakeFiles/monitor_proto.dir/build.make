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
CMAKE_SOURCE_DIR = /work

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /work/build

# Include any dependencies generated for this target.
include examples/CMakeFiles/monitor_proto.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/monitor_proto.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/monitor_proto.dir/flags.make

examples/monitor.pb.h: ../examples/monitor.proto
examples/monitor.pb.h: /usr/local/bin/protoc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/work/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running cpp protocol buffer compiler on monitor.proto"
	cd /work/build/examples && /usr/local/bin/protoc --cpp_out /work/build/examples -I /work/examples /work/examples/monitor.proto

examples/monitor.pb.cc: examples/monitor.pb.h
	@$(CMAKE_COMMAND) -E touch_nocreate examples/monitor.pb.cc

examples/CMakeFiles/monitor_proto.dir/monitor.pb.cc.o: examples/CMakeFiles/monitor_proto.dir/flags.make
examples/CMakeFiles/monitor_proto.dir/monitor.pb.cc.o: examples/monitor.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/work/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object examples/CMakeFiles/monitor_proto.dir/monitor.pb.cc.o"
	cd /work/build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/monitor_proto.dir/monitor.pb.cc.o -c /work/build/examples/monitor.pb.cc

examples/CMakeFiles/monitor_proto.dir/monitor.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/monitor_proto.dir/monitor.pb.cc.i"
	cd /work/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /work/build/examples/monitor.pb.cc > CMakeFiles/monitor_proto.dir/monitor.pb.cc.i

examples/CMakeFiles/monitor_proto.dir/monitor.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/monitor_proto.dir/monitor.pb.cc.s"
	cd /work/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /work/build/examples/monitor.pb.cc -o CMakeFiles/monitor_proto.dir/monitor.pb.cc.s

# Object files for target monitor_proto
monitor_proto_OBJECTS = \
"CMakeFiles/monitor_proto.dir/monitor.pb.cc.o"

# External object files for target monitor_proto
monitor_proto_EXTERNAL_OBJECTS =

examples/libmonitor_proto.a: examples/CMakeFiles/monitor_proto.dir/monitor.pb.cc.o
examples/libmonitor_proto.a: examples/CMakeFiles/monitor_proto.dir/build.make
examples/libmonitor_proto.a: examples/CMakeFiles/monitor_proto.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/work/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libmonitor_proto.a"
	cd /work/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/monitor_proto.dir/cmake_clean_target.cmake
	cd /work/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/monitor_proto.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/monitor_proto.dir/build: examples/libmonitor_proto.a

.PHONY : examples/CMakeFiles/monitor_proto.dir/build

examples/CMakeFiles/monitor_proto.dir/clean:
	cd /work/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/monitor_proto.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/monitor_proto.dir/clean

examples/CMakeFiles/monitor_proto.dir/depend: examples/monitor.pb.h
examples/CMakeFiles/monitor_proto.dir/depend: examples/monitor.pb.cc
	cd /work/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /work /work/examples /work/build /work/build/examples /work/build/examples/CMakeFiles/monitor_proto.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/monitor_proto.dir/depend
