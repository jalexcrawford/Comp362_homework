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
CMAKE_SOURCE_DIR = /home/alex/Desktop/comp362/CrawfordAlexLab04/lect04code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alex/Desktop/comp362/CrawfordAlexLab04/lect04code/cmake

# Include any dependencies generated for this target.
include CMakeFiles/shm_POSIX_time_server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/shm_POSIX_time_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/shm_POSIX_time_server.dir/flags.make

CMakeFiles/shm_POSIX_time_server.dir/shm_POSIX/shm_POSIX_time_server.c.o: CMakeFiles/shm_POSIX_time_server.dir/flags.make
CMakeFiles/shm_POSIX_time_server.dir/shm_POSIX/shm_POSIX_time_server.c.o: ../shm_POSIX/shm_POSIX_time_server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Desktop/comp362/CrawfordAlexLab04/lect04code/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/shm_POSIX_time_server.dir/shm_POSIX/shm_POSIX_time_server.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shm_POSIX_time_server.dir/shm_POSIX/shm_POSIX_time_server.c.o   -c /home/alex/Desktop/comp362/CrawfordAlexLab04/lect04code/shm_POSIX/shm_POSIX_time_server.c

CMakeFiles/shm_POSIX_time_server.dir/shm_POSIX/shm_POSIX_time_server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shm_POSIX_time_server.dir/shm_POSIX/shm_POSIX_time_server.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alex/Desktop/comp362/CrawfordAlexLab04/lect04code/shm_POSIX/shm_POSIX_time_server.c > CMakeFiles/shm_POSIX_time_server.dir/shm_POSIX/shm_POSIX_time_server.c.i

CMakeFiles/shm_POSIX_time_server.dir/shm_POSIX/shm_POSIX_time_server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shm_POSIX_time_server.dir/shm_POSIX/shm_POSIX_time_server.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alex/Desktop/comp362/CrawfordAlexLab04/lect04code/shm_POSIX/shm_POSIX_time_server.c -o CMakeFiles/shm_POSIX_time_server.dir/shm_POSIX/shm_POSIX_time_server.c.s

# Object files for target shm_POSIX_time_server
shm_POSIX_time_server_OBJECTS = \
"CMakeFiles/shm_POSIX_time_server.dir/shm_POSIX/shm_POSIX_time_server.c.o"

# External object files for target shm_POSIX_time_server
shm_POSIX_time_server_EXTERNAL_OBJECTS =

bin/shm_POSIX_time_server: CMakeFiles/shm_POSIX_time_server.dir/shm_POSIX/shm_POSIX_time_server.c.o
bin/shm_POSIX_time_server: CMakeFiles/shm_POSIX_time_server.dir/build.make
bin/shm_POSIX_time_server: CMakeFiles/shm_POSIX_time_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alex/Desktop/comp362/CrawfordAlexLab04/lect04code/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin/shm_POSIX_time_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/shm_POSIX_time_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/shm_POSIX_time_server.dir/build: bin/shm_POSIX_time_server

.PHONY : CMakeFiles/shm_POSIX_time_server.dir/build

CMakeFiles/shm_POSIX_time_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/shm_POSIX_time_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/shm_POSIX_time_server.dir/clean

CMakeFiles/shm_POSIX_time_server.dir/depend:
	cd /home/alex/Desktop/comp362/CrawfordAlexLab04/lect04code/cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alex/Desktop/comp362/CrawfordAlexLab04/lect04code /home/alex/Desktop/comp362/CrawfordAlexLab04/lect04code /home/alex/Desktop/comp362/CrawfordAlexLab04/lect04code/cmake /home/alex/Desktop/comp362/CrawfordAlexLab04/lect04code/cmake /home/alex/Desktop/comp362/CrawfordAlexLab04/lect04code/cmake/CMakeFiles/shm_POSIX_time_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/shm_POSIX_time_server.dir/depend

