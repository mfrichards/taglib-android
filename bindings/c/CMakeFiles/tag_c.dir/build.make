# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/spmfr/work/taglib-1.7

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/spmfr/work/taglib-1.7

# Include any dependencies generated for this target.
include bindings/c/CMakeFiles/tag_c.dir/depend.make

# Include the progress variables for this target.
include bindings/c/CMakeFiles/tag_c.dir/progress.make

# Include the compile flags for this target's objects.
include bindings/c/CMakeFiles/tag_c.dir/flags.make

bindings/c/CMakeFiles/tag_c.dir/tag_c.cpp.o: bindings/c/CMakeFiles/tag_c.dir/flags.make
bindings/c/CMakeFiles/tag_c.dir/tag_c.cpp.o: bindings/c/tag_c.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/spmfr/work/taglib-1.7/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object bindings/c/CMakeFiles/tag_c.dir/tag_c.cpp.o"
	cd /home/spmfr/work/taglib-1.7/bindings/c && /home/spmfr/android/android-ndk-r6b/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/arm-linux-androideabi-g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tag_c.dir/tag_c.cpp.o -c /home/spmfr/work/taglib-1.7/bindings/c/tag_c.cpp

bindings/c/CMakeFiles/tag_c.dir/tag_c.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tag_c.dir/tag_c.cpp.i"
	cd /home/spmfr/work/taglib-1.7/bindings/c && /home/spmfr/android/android-ndk-r6b/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/arm-linux-androideabi-g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/spmfr/work/taglib-1.7/bindings/c/tag_c.cpp > CMakeFiles/tag_c.dir/tag_c.cpp.i

bindings/c/CMakeFiles/tag_c.dir/tag_c.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tag_c.dir/tag_c.cpp.s"
	cd /home/spmfr/work/taglib-1.7/bindings/c && /home/spmfr/android/android-ndk-r6b/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/arm-linux-androideabi-g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/spmfr/work/taglib-1.7/bindings/c/tag_c.cpp -o CMakeFiles/tag_c.dir/tag_c.cpp.s

bindings/c/CMakeFiles/tag_c.dir/tag_c.cpp.o.requires:
.PHONY : bindings/c/CMakeFiles/tag_c.dir/tag_c.cpp.o.requires

bindings/c/CMakeFiles/tag_c.dir/tag_c.cpp.o.provides: bindings/c/CMakeFiles/tag_c.dir/tag_c.cpp.o.requires
	$(MAKE) -f bindings/c/CMakeFiles/tag_c.dir/build.make bindings/c/CMakeFiles/tag_c.dir/tag_c.cpp.o.provides.build
.PHONY : bindings/c/CMakeFiles/tag_c.dir/tag_c.cpp.o.provides

bindings/c/CMakeFiles/tag_c.dir/tag_c.cpp.o.provides.build: bindings/c/CMakeFiles/tag_c.dir/tag_c.cpp.o
.PHONY : bindings/c/CMakeFiles/tag_c.dir/tag_c.cpp.o.provides.build

# Object files for target tag_c
tag_c_OBJECTS = \
"CMakeFiles/tag_c.dir/tag_c.cpp.o"

# External object files for target tag_c
tag_c_EXTERNAL_OBJECTS =

build/armeabi/lib/libtag_c.so: bindings/c/CMakeFiles/tag_c.dir/tag_c.cpp.o
build/armeabi/lib/libtag_c.so: build/armeabi/lib/libtag.so
build/armeabi/lib/libtag_c.so: bindings/c/CMakeFiles/tag_c.dir/build.make
build/armeabi/lib/libtag_c.so: bindings/c/CMakeFiles/tag_c.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library ../../build/armeabi/lib/libtag_c.so"
	cd /home/spmfr/work/taglib-1.7/bindings/c && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tag_c.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bindings/c/CMakeFiles/tag_c.dir/build: build/armeabi/lib/libtag_c.so
.PHONY : bindings/c/CMakeFiles/tag_c.dir/build

# Object files for target tag_c
tag_c_OBJECTS = \
"CMakeFiles/tag_c.dir/tag_c.cpp.o"

# External object files for target tag_c
tag_c_EXTERNAL_OBJECTS =

bindings/c/CMakeFiles/CMakeRelink.dir/libtag_c.so: bindings/c/CMakeFiles/tag_c.dir/tag_c.cpp.o
bindings/c/CMakeFiles/CMakeRelink.dir/libtag_c.so: build/armeabi/lib/libtag.so
bindings/c/CMakeFiles/CMakeRelink.dir/libtag_c.so: bindings/c/CMakeFiles/tag_c.dir/build.make
bindings/c/CMakeFiles/CMakeRelink.dir/libtag_c.so: bindings/c/CMakeFiles/tag_c.dir/relink.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library CMakeFiles/CMakeRelink.dir/libtag_c.so"
	cd /home/spmfr/work/taglib-1.7/bindings/c && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tag_c.dir/relink.txt --verbose=$(VERBOSE)

# Rule to relink during preinstall.
bindings/c/CMakeFiles/tag_c.dir/preinstall: bindings/c/CMakeFiles/CMakeRelink.dir/libtag_c.so
.PHONY : bindings/c/CMakeFiles/tag_c.dir/preinstall

bindings/c/CMakeFiles/tag_c.dir/requires: bindings/c/CMakeFiles/tag_c.dir/tag_c.cpp.o.requires
.PHONY : bindings/c/CMakeFiles/tag_c.dir/requires

bindings/c/CMakeFiles/tag_c.dir/clean:
	cd /home/spmfr/work/taglib-1.7/bindings/c && $(CMAKE_COMMAND) -P CMakeFiles/tag_c.dir/cmake_clean.cmake
.PHONY : bindings/c/CMakeFiles/tag_c.dir/clean

bindings/c/CMakeFiles/tag_c.dir/depend:
	cd /home/spmfr/work/taglib-1.7 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/spmfr/work/taglib-1.7 /home/spmfr/work/taglib-1.7/bindings/c /home/spmfr/work/taglib-1.7 /home/spmfr/work/taglib-1.7/bindings/c /home/spmfr/work/taglib-1.7/bindings/c/CMakeFiles/tag_c.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bindings/c/CMakeFiles/tag_c.dir/depend
