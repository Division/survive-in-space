# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = "/Applications/CMake 2.8-8.app/Contents/bin/cmake"

# The command to remove a file.
RM = "/Applications/CMake 2.8-8.app/Contents/bin/cmake" -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = "/Applications/CMake 2.8-8.app/Contents/bin/ccmake"

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Sidorenko/Downloads/bullet-2.80-rev2531

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Sidorenko/Downloads/bullet-2.80-rev2531

# Include any dependencies generated for this target.
include src/MiniCL/CMakeFiles/MiniCL.dir/depend.make

# Include the progress variables for this target.
include src/MiniCL/CMakeFiles/MiniCL.dir/progress.make

# Include the compile flags for this target's objects.
include src/MiniCL/CMakeFiles/MiniCL.dir/flags.make

src/MiniCL/MiniCL.framework/Versions/2.80/Headers/MiniCLTaskScheduler.h: src/MiniCL/MiniCLTaskScheduler.h
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Copying OS X content src/MiniCL/MiniCL.framework/Versions/2.80/Headers/MiniCLTaskScheduler.h"
	$(CMAKE_COMMAND) -E copy /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL/MiniCLTaskScheduler.h src/MiniCL/MiniCL.framework/Versions/2.80/Headers/MiniCLTaskScheduler.h

src/MiniCL/MiniCL.framework/Versions/2.80/Headers/cl.h: src/MiniCL/cl.h
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Copying OS X content src/MiniCL/MiniCL.framework/Versions/2.80/Headers/cl.h"
	$(CMAKE_COMMAND) -E copy /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL/cl.h src/MiniCL/MiniCL.framework/Versions/2.80/Headers/cl.h

src/MiniCL/MiniCL.framework/Versions/2.80/Headers/cl_gl.h: src/MiniCL/cl_gl.h
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Copying OS X content src/MiniCL/MiniCL.framework/Versions/2.80/Headers/cl_gl.h"
	$(CMAKE_COMMAND) -E copy /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL/cl_gl.h src/MiniCL/MiniCL.framework/Versions/2.80/Headers/cl_gl.h

src/MiniCL/MiniCL.framework/Versions/2.80/Headers/cl_platform.h: src/MiniCL/cl_platform.h
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Copying OS X content src/MiniCL/MiniCL.framework/Versions/2.80/Headers/cl_platform.h"
	$(CMAKE_COMMAND) -E copy /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL/cl_platform.h src/MiniCL/MiniCL.framework/Versions/2.80/Headers/cl_platform.h

src/MiniCL/MiniCL.framework/Versions/2.80/Headers/cl_MiniCL_Defs.h: src/MiniCL/cl_MiniCL_Defs.h
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Copying OS X content src/MiniCL/MiniCL.framework/Versions/2.80/Headers/cl_MiniCL_Defs.h"
	$(CMAKE_COMMAND) -E copy /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL/cl_MiniCL_Defs.h src/MiniCL/MiniCL.framework/Versions/2.80/Headers/cl_MiniCL_Defs.h

src/MiniCL/MiniCL.framework/Versions/2.80/Headers/MiniCLTask/MiniCLTask.h: src/MiniCL/MiniCLTask/MiniCLTask.h
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Copying OS X content src/MiniCL/MiniCL.framework/Versions/2.80/Headers/MiniCLTask/MiniCLTask.h"
	$(CMAKE_COMMAND) -E copy /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL/MiniCLTask/MiniCLTask.h src/MiniCL/MiniCL.framework/Versions/2.80/Headers/MiniCLTask/MiniCLTask.h

src/MiniCL/CMakeFiles/MiniCL.dir/MiniCL.o: src/MiniCL/CMakeFiles/MiniCL.dir/flags.make
src/MiniCL/CMakeFiles/MiniCL.dir/MiniCL.o: src/MiniCL/MiniCL.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Sidorenko/Downloads/bullet-2.80-rev2531/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/MiniCL/CMakeFiles/MiniCL.dir/MiniCL.o"
	cd /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MiniCL.dir/MiniCL.o -c /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL/MiniCL.cpp

src/MiniCL/CMakeFiles/MiniCL.dir/MiniCL.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MiniCL.dir/MiniCL.i"
	cd /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL/MiniCL.cpp > CMakeFiles/MiniCL.dir/MiniCL.i

src/MiniCL/CMakeFiles/MiniCL.dir/MiniCL.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MiniCL.dir/MiniCL.s"
	cd /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL/MiniCL.cpp -o CMakeFiles/MiniCL.dir/MiniCL.s

src/MiniCL/CMakeFiles/MiniCL.dir/MiniCL.o.requires:
.PHONY : src/MiniCL/CMakeFiles/MiniCL.dir/MiniCL.o.requires

src/MiniCL/CMakeFiles/MiniCL.dir/MiniCL.o.provides: src/MiniCL/CMakeFiles/MiniCL.dir/MiniCL.o.requires
	$(MAKE) -f src/MiniCL/CMakeFiles/MiniCL.dir/build.make src/MiniCL/CMakeFiles/MiniCL.dir/MiniCL.o.provides.build
.PHONY : src/MiniCL/CMakeFiles/MiniCL.dir/MiniCL.o.provides

src/MiniCL/CMakeFiles/MiniCL.dir/MiniCL.o.provides.build: src/MiniCL/CMakeFiles/MiniCL.dir/MiniCL.o

src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTaskScheduler.o: src/MiniCL/CMakeFiles/MiniCL.dir/flags.make
src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTaskScheduler.o: src/MiniCL/MiniCLTaskScheduler.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Sidorenko/Downloads/bullet-2.80-rev2531/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTaskScheduler.o"
	cd /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MiniCL.dir/MiniCLTaskScheduler.o -c /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL/MiniCLTaskScheduler.cpp

src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTaskScheduler.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MiniCL.dir/MiniCLTaskScheduler.i"
	cd /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL/MiniCLTaskScheduler.cpp > CMakeFiles/MiniCL.dir/MiniCLTaskScheduler.i

src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTaskScheduler.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MiniCL.dir/MiniCLTaskScheduler.s"
	cd /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL/MiniCLTaskScheduler.cpp -o CMakeFiles/MiniCL.dir/MiniCLTaskScheduler.s

src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTaskScheduler.o.requires:
.PHONY : src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTaskScheduler.o.requires

src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTaskScheduler.o.provides: src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTaskScheduler.o.requires
	$(MAKE) -f src/MiniCL/CMakeFiles/MiniCL.dir/build.make src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTaskScheduler.o.provides.build
.PHONY : src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTaskScheduler.o.provides

src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTaskScheduler.o.provides.build: src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTaskScheduler.o

src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTask/MiniCLTask.o: src/MiniCL/CMakeFiles/MiniCL.dir/flags.make
src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTask/MiniCLTask.o: src/MiniCL/MiniCLTask/MiniCLTask.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Sidorenko/Downloads/bullet-2.80-rev2531/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTask/MiniCLTask.o"
	cd /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MiniCL.dir/MiniCLTask/MiniCLTask.o -c /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL/MiniCLTask/MiniCLTask.cpp

src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTask/MiniCLTask.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MiniCL.dir/MiniCLTask/MiniCLTask.i"
	cd /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL/MiniCLTask/MiniCLTask.cpp > CMakeFiles/MiniCL.dir/MiniCLTask/MiniCLTask.i

src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTask/MiniCLTask.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MiniCL.dir/MiniCLTask/MiniCLTask.s"
	cd /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL/MiniCLTask/MiniCLTask.cpp -o CMakeFiles/MiniCL.dir/MiniCLTask/MiniCLTask.s

src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTask/MiniCLTask.o.requires:
.PHONY : src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTask/MiniCLTask.o.requires

src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTask/MiniCLTask.o.provides: src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTask/MiniCLTask.o.requires
	$(MAKE) -f src/MiniCL/CMakeFiles/MiniCL.dir/build.make src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTask/MiniCLTask.o.provides.build
.PHONY : src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTask/MiniCLTask.o.provides

src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTask/MiniCLTask.o.provides.build: src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTask/MiniCLTask.o

# Object files for target MiniCL
MiniCL_OBJECTS = \
"CMakeFiles/MiniCL.dir/MiniCL.o" \
"CMakeFiles/MiniCL.dir/MiniCLTaskScheduler.o" \
"CMakeFiles/MiniCL.dir/MiniCLTask/MiniCLTask.o"

# External object files for target MiniCL
MiniCL_EXTERNAL_OBJECTS =

src/MiniCL/MiniCL.framework/Versions/2.80/MiniCL: src/MiniCL/CMakeFiles/MiniCL.dir/MiniCL.o
src/MiniCL/MiniCL.framework/Versions/2.80/MiniCL: src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTaskScheduler.o
src/MiniCL/MiniCL.framework/Versions/2.80/MiniCL: src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTask/MiniCLTask.o
src/MiniCL/MiniCL.framework/Versions/2.80/MiniCL: src/MiniCL/CMakeFiles/MiniCL.dir/build.make
src/MiniCL/MiniCL.framework/Versions/2.80/MiniCL: src/BulletMultiThreaded/BulletMultiThreaded.framework/Versions/2.80/BulletMultiThreaded
src/MiniCL/MiniCL.framework/Versions/2.80/MiniCL: src/BulletDynamics/BulletDynamics.framework/Versions/2.80/BulletDynamics
src/MiniCL/MiniCL.framework/Versions/2.80/MiniCL: src/BulletCollision/BulletCollision.framework/Versions/2.80/BulletCollision
src/MiniCL/MiniCL.framework/Versions/2.80/MiniCL: src/LinearMath/LinearMath.framework/Versions/2.80/LinearMath
src/MiniCL/MiniCL.framework/Versions/2.80/MiniCL: src/MiniCL/CMakeFiles/MiniCL.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library MiniCL.framework/Versions/2.80/MiniCL"
	cd /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MiniCL.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/MiniCL/CMakeFiles/MiniCL.dir/build: src/MiniCL/MiniCL.framework/Versions/2.80/MiniCL
src/MiniCL/CMakeFiles/MiniCL.dir/build: src/MiniCL/MiniCL.framework/Versions/2.80/Headers/MiniCLTask/MiniCLTask.h
src/MiniCL/CMakeFiles/MiniCL.dir/build: src/MiniCL/MiniCL.framework/Versions/2.80/Headers/MiniCLTaskScheduler.h
src/MiniCL/CMakeFiles/MiniCL.dir/build: src/MiniCL/MiniCL.framework/Versions/2.80/Headers/cl.h
src/MiniCL/CMakeFiles/MiniCL.dir/build: src/MiniCL/MiniCL.framework/Versions/2.80/Headers/cl_MiniCL_Defs.h
src/MiniCL/CMakeFiles/MiniCL.dir/build: src/MiniCL/MiniCL.framework/Versions/2.80/Headers/cl_gl.h
src/MiniCL/CMakeFiles/MiniCL.dir/build: src/MiniCL/MiniCL.framework/Versions/2.80/Headers/cl_platform.h
.PHONY : src/MiniCL/CMakeFiles/MiniCL.dir/build

src/MiniCL/CMakeFiles/MiniCL.dir/requires: src/MiniCL/CMakeFiles/MiniCL.dir/MiniCL.o.requires
src/MiniCL/CMakeFiles/MiniCL.dir/requires: src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTaskScheduler.o.requires
src/MiniCL/CMakeFiles/MiniCL.dir/requires: src/MiniCL/CMakeFiles/MiniCL.dir/MiniCLTask/MiniCLTask.o.requires
.PHONY : src/MiniCL/CMakeFiles/MiniCL.dir/requires

src/MiniCL/CMakeFiles/MiniCL.dir/clean:
	cd /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL && $(CMAKE_COMMAND) -P CMakeFiles/MiniCL.dir/cmake_clean.cmake
.PHONY : src/MiniCL/CMakeFiles/MiniCL.dir/clean

src/MiniCL/CMakeFiles/MiniCL.dir/depend:
	cd /Users/Sidorenko/Downloads/bullet-2.80-rev2531 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Sidorenko/Downloads/bullet-2.80-rev2531 /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL /Users/Sidorenko/Downloads/bullet-2.80-rev2531 /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL/CMakeFiles/MiniCL.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/MiniCL/CMakeFiles/MiniCL.dir/depend

