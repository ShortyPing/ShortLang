# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/shortping/CLionProjects/SLang

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/shortping/CLionProjects/SLang

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/shortping/CLionProjects/SLang/CMakeFiles /home/shortping/CLionProjects/SLang//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/shortping/CLionProjects/SLang/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named SLang

# Build rule for target.
SLang: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 SLang
.PHONY : SLang

# fast build rule for target.
SLang/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SLang.dir/build.make CMakeFiles/SLang.dir/build
.PHONY : SLang/fast

src/config.o: src/config.c.o
.PHONY : src/config.o

# target to build an object file
src/config.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SLang.dir/build.make CMakeFiles/SLang.dir/src/config.c.o
.PHONY : src/config.c.o

src/config.i: src/config.c.i
.PHONY : src/config.i

# target to preprocess a source file
src/config.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SLang.dir/build.make CMakeFiles/SLang.dir/src/config.c.i
.PHONY : src/config.c.i

src/config.s: src/config.c.s
.PHONY : src/config.s

# target to generate assembly for a file
src/config.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SLang.dir/build.make CMakeFiles/SLang.dir/src/config.c.s
.PHONY : src/config.c.s

src/f_read.o: src/f_read.c.o
.PHONY : src/f_read.o

# target to build an object file
src/f_read.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SLang.dir/build.make CMakeFiles/SLang.dir/src/f_read.c.o
.PHONY : src/f_read.c.o

src/f_read.i: src/f_read.c.i
.PHONY : src/f_read.i

# target to preprocess a source file
src/f_read.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SLang.dir/build.make CMakeFiles/SLang.dir/src/f_read.c.i
.PHONY : src/f_read.c.i

src/f_read.s: src/f_read.c.s
.PHONY : src/f_read.s

# target to generate assembly for a file
src/f_read.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SLang.dir/build.make CMakeFiles/SLang.dir/src/f_read.c.s
.PHONY : src/f_read.c.s

src/lifecycle.o: src/lifecycle.c.o
.PHONY : src/lifecycle.o

# target to build an object file
src/lifecycle.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SLang.dir/build.make CMakeFiles/SLang.dir/src/lifecycle.c.o
.PHONY : src/lifecycle.c.o

src/lifecycle.i: src/lifecycle.c.i
.PHONY : src/lifecycle.i

# target to preprocess a source file
src/lifecycle.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SLang.dir/build.make CMakeFiles/SLang.dir/src/lifecycle.c.i
.PHONY : src/lifecycle.c.i

src/lifecycle.s: src/lifecycle.c.s
.PHONY : src/lifecycle.s

# target to generate assembly for a file
src/lifecycle.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SLang.dir/build.make CMakeFiles/SLang.dir/src/lifecycle.c.s
.PHONY : src/lifecycle.c.s

src/main.o: src/main.c.o
.PHONY : src/main.o

# target to build an object file
src/main.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SLang.dir/build.make CMakeFiles/SLang.dir/src/main.c.o
.PHONY : src/main.c.o

src/main.i: src/main.c.i
.PHONY : src/main.i

# target to preprocess a source file
src/main.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SLang.dir/build.make CMakeFiles/SLang.dir/src/main.c.i
.PHONY : src/main.c.i

src/main.s: src/main.c.s
.PHONY : src/main.s

# target to generate assembly for a file
src/main.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SLang.dir/build.make CMakeFiles/SLang.dir/src/main.c.s
.PHONY : src/main.c.s

src/memory.o: src/memory.c.o
.PHONY : src/memory.o

# target to build an object file
src/memory.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SLang.dir/build.make CMakeFiles/SLang.dir/src/memory.c.o
.PHONY : src/memory.c.o

src/memory.i: src/memory.c.i
.PHONY : src/memory.i

# target to preprocess a source file
src/memory.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SLang.dir/build.make CMakeFiles/SLang.dir/src/memory.c.i
.PHONY : src/memory.c.i

src/memory.s: src/memory.c.s
.PHONY : src/memory.s

# target to generate assembly for a file
src/memory.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SLang.dir/build.make CMakeFiles/SLang.dir/src/memory.c.s
.PHONY : src/memory.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... SLang"
	@echo "... src/config.o"
	@echo "... src/config.i"
	@echo "... src/config.s"
	@echo "... src/f_read.o"
	@echo "... src/f_read.i"
	@echo "... src/f_read.s"
	@echo "... src/lifecycle.o"
	@echo "... src/lifecycle.i"
	@echo "... src/lifecycle.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/memory.o"
	@echo "... src/memory.i"
	@echo "... src/memory.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

