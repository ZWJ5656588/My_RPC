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
include proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/depend.make

# Include the progress variables for this target.
include proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/progress.make

# Include the compile flags for this target's objects.
include proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/flags.make

proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/RpcChannel.cc.o: proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/flags.make
proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/RpcChannel.cc.o: ../proto_rpc/rpc_framework/RpcChannel.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/work/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/RpcChannel.cc.o"
	cd /work/build/proto_rpc/rpc_framework && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rpc_framework.dir/RpcChannel.cc.o -c /work/proto_rpc/rpc_framework/RpcChannel.cc

proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/RpcChannel.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rpc_framework.dir/RpcChannel.cc.i"
	cd /work/build/proto_rpc/rpc_framework && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /work/proto_rpc/rpc_framework/RpcChannel.cc > CMakeFiles/rpc_framework.dir/RpcChannel.cc.i

proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/RpcChannel.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rpc_framework.dir/RpcChannel.cc.s"
	cd /work/build/proto_rpc/rpc_framework && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /work/proto_rpc/rpc_framework/RpcChannel.cc -o CMakeFiles/rpc_framework.dir/RpcChannel.cc.s

proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/RpcServer.cc.o: proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/flags.make
proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/RpcServer.cc.o: ../proto_rpc/rpc_framework/RpcServer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/work/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/RpcServer.cc.o"
	cd /work/build/proto_rpc/rpc_framework && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rpc_framework.dir/RpcServer.cc.o -c /work/proto_rpc/rpc_framework/RpcServer.cc

proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/RpcServer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rpc_framework.dir/RpcServer.cc.i"
	cd /work/build/proto_rpc/rpc_framework && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /work/proto_rpc/rpc_framework/RpcServer.cc > CMakeFiles/rpc_framework.dir/RpcServer.cc.i

proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/RpcServer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rpc_framework.dir/RpcServer.cc.s"
	cd /work/build/proto_rpc/rpc_framework && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /work/proto_rpc/rpc_framework/RpcServer.cc -o CMakeFiles/rpc_framework.dir/RpcServer.cc.s

proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/RpcCodec.cc.o: proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/flags.make
proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/RpcCodec.cc.o: ../proto_rpc/rpc_framework/RpcCodec.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/work/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/RpcCodec.cc.o"
	cd /work/build/proto_rpc/rpc_framework && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rpc_framework.dir/RpcCodec.cc.o -c /work/proto_rpc/rpc_framework/RpcCodec.cc

proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/RpcCodec.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rpc_framework.dir/RpcCodec.cc.i"
	cd /work/build/proto_rpc/rpc_framework && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /work/proto_rpc/rpc_framework/RpcCodec.cc > CMakeFiles/rpc_framework.dir/RpcCodec.cc.i

proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/RpcCodec.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rpc_framework.dir/RpcCodec.cc.s"
	cd /work/build/proto_rpc/rpc_framework && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /work/proto_rpc/rpc_framework/RpcCodec.cc -o CMakeFiles/rpc_framework.dir/RpcCodec.cc.s

# Object files for target rpc_framework
rpc_framework_OBJECTS = \
"CMakeFiles/rpc_framework.dir/RpcChannel.cc.o" \
"CMakeFiles/rpc_framework.dir/RpcServer.cc.o" \
"CMakeFiles/rpc_framework.dir/RpcCodec.cc.o"

# External object files for target rpc_framework
rpc_framework_EXTERNAL_OBJECTS =

proto_rpc/rpc_framework/librpc_framework.a: proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/RpcChannel.cc.o
proto_rpc/rpc_framework/librpc_framework.a: proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/RpcServer.cc.o
proto_rpc/rpc_framework/librpc_framework.a: proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/RpcCodec.cc.o
proto_rpc/rpc_framework/librpc_framework.a: proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/build.make
proto_rpc/rpc_framework/librpc_framework.a: proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/work/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library librpc_framework.a"
	cd /work/build/proto_rpc/rpc_framework && $(CMAKE_COMMAND) -P CMakeFiles/rpc_framework.dir/cmake_clean_target.cmake
	cd /work/build/proto_rpc/rpc_framework && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rpc_framework.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/build: proto_rpc/rpc_framework/librpc_framework.a

.PHONY : proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/build

proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/clean:
	cd /work/build/proto_rpc/rpc_framework && $(CMAKE_COMMAND) -P CMakeFiles/rpc_framework.dir/cmake_clean.cmake
.PHONY : proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/clean

proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/depend:
	cd /work/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /work /work/proto_rpc/rpc_framework /work/build /work/build/proto_rpc/rpc_framework /work/build/proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : proto_rpc/rpc_framework/CMakeFiles/rpc_framework.dir/depend

