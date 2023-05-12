# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_SOURCE_DIR = /run/media/yuxinz/Data/Backup/DaiXue/CS100/CS100-HW8_9

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /run/media/yuxinz/Data/Backup/DaiXue/CS100/CS100-HW8_9

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

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Available install components are: \"Devel\" \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components
.PHONY : list_install_components/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local/fast

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /run/media/yuxinz/Data/Backup/DaiXue/CS100/CS100-HW8_9/CMakeFiles /run/media/yuxinz/Data/Backup/DaiXue/CS100/CS100-HW8_9//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /run/media/yuxinz/Data/Backup/DaiXue/CS100/CS100-HW8_9/CMakeFiles 0
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
# Target rules for targets named ProvidedFramework

# Build rule for target.
ProvidedFramework: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 ProvidedFramework
.PHONY : ProvidedFramework

# fast build rule for target.
ProvidedFramework/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ProvidedFramework.dir/build.make CMakeFiles/ProvidedFramework.dir/build
.PHONY : ProvidedFramework/fast

#=============================================================================
# Target rules for targets named PartForYou

# Build rule for target.
PartForYou: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 PartForYou
.PHONY : PartForYou

# fast build rule for target.
PartForYou/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/PartForYou.dir/build.make CMakeFiles/PartForYou.dir/build
.PHONY : PartForYou/fast

#=============================================================================
# Target rules for targets named part1

# Build rule for target.
part1: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 part1
.PHONY : part1

# fast build rule for target.
part1/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/part1.dir/build.make CMakeFiles/part1.dir/build
.PHONY : part1/fast

#=============================================================================
# Target rules for targets named part2

# Build rule for target.
part2: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 part2
.PHONY : part2

# fast build rule for target.
part2/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/part2.dir/build.make CMakeFiles/part2.dir/build
.PHONY : part2/fast

#=============================================================================
# Target rules for targets named part3

# Build rule for target.
part3: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 part3
.PHONY : part3

# fast build rule for target.
part3/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/part3.dir/build.make CMakeFiles/part3.dir/build
.PHONY : part3/fast

#=============================================================================
# Target rules for targets named part4

# Build rule for target.
part4: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 part4
.PHONY : part4

# fast build rule for target.
part4/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/part4.dir/build.make CMakeFiles/part4.dir/build
.PHONY : part4/fast

#=============================================================================
# Target rules for targets named Dawnbreaker

# Build rule for target.
Dawnbreaker: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 Dawnbreaker
.PHONY : Dawnbreaker

# fast build rule for target.
Dawnbreaker/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Dawnbreaker.dir/build.make CMakeFiles/Dawnbreaker.dir/build
.PHONY : Dawnbreaker/fast

#=============================================================================
# Target rules for targets named SOIL

# Build rule for target.
SOIL: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 SOIL
.PHONY : SOIL

# fast build rule for target.
SOIL/fast:
	$(MAKE) $(MAKESILENT) -f SOIL/CMakeFiles/SOIL.dir/build.make SOIL/CMakeFiles/SOIL.dir/build
.PHONY : SOIL/fast

#=============================================================================
# Target rules for targets named freeglut

# Build rule for target.
freeglut: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 freeglut
.PHONY : freeglut

# fast build rule for target.
freeglut/fast:
	$(MAKE) $(MAKESILENT) -f freeglut/CMakeFiles/freeglut.dir/build.make freeglut/CMakeFiles/freeglut.dir/build
.PHONY : freeglut/fast

#=============================================================================
# Target rules for targets named freeglut_static

# Build rule for target.
freeglut_static: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 freeglut_static
.PHONY : freeglut_static

# fast build rule for target.
freeglut_static/fast:
	$(MAKE) $(MAKESILENT) -f freeglut/CMakeFiles/freeglut_static.dir/build.make freeglut/CMakeFiles/freeglut_static.dir/build
.PHONY : freeglut_static/fast

src/PartForYou/GameObjects.o: src/PartForYou/GameObjects.cpp.o
.PHONY : src/PartForYou/GameObjects.o

# target to build an object file
src/PartForYou/GameObjects.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/PartForYou.dir/build.make CMakeFiles/PartForYou.dir/src/PartForYou/GameObjects.cpp.o
.PHONY : src/PartForYou/GameObjects.cpp.o

src/PartForYou/GameObjects.i: src/PartForYou/GameObjects.cpp.i
.PHONY : src/PartForYou/GameObjects.i

# target to preprocess a source file
src/PartForYou/GameObjects.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/PartForYou.dir/build.make CMakeFiles/PartForYou.dir/src/PartForYou/GameObjects.cpp.i
.PHONY : src/PartForYou/GameObjects.cpp.i

src/PartForYou/GameObjects.s: src/PartForYou/GameObjects.cpp.s
.PHONY : src/PartForYou/GameObjects.s

# target to generate assembly for a file
src/PartForYou/GameObjects.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/PartForYou.dir/build.make CMakeFiles/PartForYou.dir/src/PartForYou/GameObjects.cpp.s
.PHONY : src/PartForYou/GameObjects.cpp.s

src/PartForYou/GameWorld.o: src/PartForYou/GameWorld.cpp.o
.PHONY : src/PartForYou/GameWorld.o

# target to build an object file
src/PartForYou/GameWorld.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/PartForYou.dir/build.make CMakeFiles/PartForYou.dir/src/PartForYou/GameWorld.cpp.o
.PHONY : src/PartForYou/GameWorld.cpp.o

src/PartForYou/GameWorld.i: src/PartForYou/GameWorld.cpp.i
.PHONY : src/PartForYou/GameWorld.i

# target to preprocess a source file
src/PartForYou/GameWorld.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/PartForYou.dir/build.make CMakeFiles/PartForYou.dir/src/PartForYou/GameWorld.cpp.i
.PHONY : src/PartForYou/GameWorld.cpp.i

src/PartForYou/GameWorld.s: src/PartForYou/GameWorld.cpp.s
.PHONY : src/PartForYou/GameWorld.s

# target to generate assembly for a file
src/PartForYou/GameWorld.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/PartForYou.dir/build.make CMakeFiles/PartForYou.dir/src/PartForYou/GameWorld.cpp.s
.PHONY : src/PartForYou/GameWorld.cpp.s

src/ProvidedFramework/GameManager.o: src/ProvidedFramework/GameManager.cpp.o
.PHONY : src/ProvidedFramework/GameManager.o

# target to build an object file
src/ProvidedFramework/GameManager.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ProvidedFramework.dir/build.make CMakeFiles/ProvidedFramework.dir/src/ProvidedFramework/GameManager.cpp.o
.PHONY : src/ProvidedFramework/GameManager.cpp.o

src/ProvidedFramework/GameManager.i: src/ProvidedFramework/GameManager.cpp.i
.PHONY : src/ProvidedFramework/GameManager.i

# target to preprocess a source file
src/ProvidedFramework/GameManager.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ProvidedFramework.dir/build.make CMakeFiles/ProvidedFramework.dir/src/ProvidedFramework/GameManager.cpp.i
.PHONY : src/ProvidedFramework/GameManager.cpp.i

src/ProvidedFramework/GameManager.s: src/ProvidedFramework/GameManager.cpp.s
.PHONY : src/ProvidedFramework/GameManager.s

# target to generate assembly for a file
src/ProvidedFramework/GameManager.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ProvidedFramework.dir/build.make CMakeFiles/ProvidedFramework.dir/src/ProvidedFramework/GameManager.cpp.s
.PHONY : src/ProvidedFramework/GameManager.cpp.s

src/ProvidedFramework/ObjectBase.o: src/ProvidedFramework/ObjectBase.cpp.o
.PHONY : src/ProvidedFramework/ObjectBase.o

# target to build an object file
src/ProvidedFramework/ObjectBase.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ProvidedFramework.dir/build.make CMakeFiles/ProvidedFramework.dir/src/ProvidedFramework/ObjectBase.cpp.o
.PHONY : src/ProvidedFramework/ObjectBase.cpp.o

src/ProvidedFramework/ObjectBase.i: src/ProvidedFramework/ObjectBase.cpp.i
.PHONY : src/ProvidedFramework/ObjectBase.i

# target to preprocess a source file
src/ProvidedFramework/ObjectBase.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ProvidedFramework.dir/build.make CMakeFiles/ProvidedFramework.dir/src/ProvidedFramework/ObjectBase.cpp.i
.PHONY : src/ProvidedFramework/ObjectBase.cpp.i

src/ProvidedFramework/ObjectBase.s: src/ProvidedFramework/ObjectBase.cpp.s
.PHONY : src/ProvidedFramework/ObjectBase.s

# target to generate assembly for a file
src/ProvidedFramework/ObjectBase.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ProvidedFramework.dir/build.make CMakeFiles/ProvidedFramework.dir/src/ProvidedFramework/ObjectBase.cpp.s
.PHONY : src/ProvidedFramework/ObjectBase.cpp.s

src/ProvidedFramework/SpriteManager.o: src/ProvidedFramework/SpriteManager.cpp.o
.PHONY : src/ProvidedFramework/SpriteManager.o

# target to build an object file
src/ProvidedFramework/SpriteManager.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ProvidedFramework.dir/build.make CMakeFiles/ProvidedFramework.dir/src/ProvidedFramework/SpriteManager.cpp.o
.PHONY : src/ProvidedFramework/SpriteManager.cpp.o

src/ProvidedFramework/SpriteManager.i: src/ProvidedFramework/SpriteManager.cpp.i
.PHONY : src/ProvidedFramework/SpriteManager.i

# target to preprocess a source file
src/ProvidedFramework/SpriteManager.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ProvidedFramework.dir/build.make CMakeFiles/ProvidedFramework.dir/src/ProvidedFramework/SpriteManager.cpp.i
.PHONY : src/ProvidedFramework/SpriteManager.cpp.i

src/ProvidedFramework/SpriteManager.s: src/ProvidedFramework/SpriteManager.cpp.s
.PHONY : src/ProvidedFramework/SpriteManager.s

# target to generate assembly for a file
src/ProvidedFramework/SpriteManager.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ProvidedFramework.dir/build.make CMakeFiles/ProvidedFramework.dir/src/ProvidedFramework/SpriteManager.cpp.s
.PHONY : src/ProvidedFramework/SpriteManager.cpp.s

src/ProvidedFramework/WorldBase.o: src/ProvidedFramework/WorldBase.cpp.o
.PHONY : src/ProvidedFramework/WorldBase.o

# target to build an object file
src/ProvidedFramework/WorldBase.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ProvidedFramework.dir/build.make CMakeFiles/ProvidedFramework.dir/src/ProvidedFramework/WorldBase.cpp.o
.PHONY : src/ProvidedFramework/WorldBase.cpp.o

src/ProvidedFramework/WorldBase.i: src/ProvidedFramework/WorldBase.cpp.i
.PHONY : src/ProvidedFramework/WorldBase.i

# target to preprocess a source file
src/ProvidedFramework/WorldBase.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ProvidedFramework.dir/build.make CMakeFiles/ProvidedFramework.dir/src/ProvidedFramework/WorldBase.cpp.i
.PHONY : src/ProvidedFramework/WorldBase.cpp.i

src/ProvidedFramework/WorldBase.s: src/ProvidedFramework/WorldBase.cpp.s
.PHONY : src/ProvidedFramework/WorldBase.s

# target to generate assembly for a file
src/ProvidedFramework/WorldBase.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ProvidedFramework.dir/build.make CMakeFiles/ProvidedFramework.dir/src/ProvidedFramework/WorldBase.cpp.s
.PHONY : src/ProvidedFramework/WorldBase.cpp.s

src/main.o: src/main.cpp.o
.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Dawnbreaker.dir/build.make CMakeFiles/Dawnbreaker.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i
.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Dawnbreaker.dir/build.make CMakeFiles/Dawnbreaker.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s
.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Dawnbreaker.dir/build.make CMakeFiles/Dawnbreaker.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/part1/a.o: src/part1/a.cpp.o
.PHONY : src/part1/a.o

# target to build an object file
src/part1/a.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/part1.dir/build.make CMakeFiles/part1.dir/src/part1/a.cpp.o
.PHONY : src/part1/a.cpp.o

src/part1/a.i: src/part1/a.cpp.i
.PHONY : src/part1/a.i

# target to preprocess a source file
src/part1/a.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/part1.dir/build.make CMakeFiles/part1.dir/src/part1/a.cpp.i
.PHONY : src/part1/a.cpp.i

src/part1/a.s: src/part1/a.cpp.s
.PHONY : src/part1/a.s

# target to generate assembly for a file
src/part1/a.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/part1.dir/build.make CMakeFiles/part1.dir/src/part1/a.cpp.s
.PHONY : src/part1/a.cpp.s

src/part2/b.o: src/part2/b.cpp.o
.PHONY : src/part2/b.o

# target to build an object file
src/part2/b.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/part2.dir/build.make CMakeFiles/part2.dir/src/part2/b.cpp.o
.PHONY : src/part2/b.cpp.o

src/part2/b.i: src/part2/b.cpp.i
.PHONY : src/part2/b.i

# target to preprocess a source file
src/part2/b.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/part2.dir/build.make CMakeFiles/part2.dir/src/part2/b.cpp.i
.PHONY : src/part2/b.cpp.i

src/part2/b.s: src/part2/b.cpp.s
.PHONY : src/part2/b.s

# target to generate assembly for a file
src/part2/b.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/part2.dir/build.make CMakeFiles/part2.dir/src/part2/b.cpp.s
.PHONY : src/part2/b.cpp.s

src/part3/c.o: src/part3/c.cpp.o
.PHONY : src/part3/c.o

# target to build an object file
src/part3/c.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/part3.dir/build.make CMakeFiles/part3.dir/src/part3/c.cpp.o
.PHONY : src/part3/c.cpp.o

src/part3/c.i: src/part3/c.cpp.i
.PHONY : src/part3/c.i

# target to preprocess a source file
src/part3/c.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/part3.dir/build.make CMakeFiles/part3.dir/src/part3/c.cpp.i
.PHONY : src/part3/c.cpp.i

src/part3/c.s: src/part3/c.cpp.s
.PHONY : src/part3/c.s

# target to generate assembly for a file
src/part3/c.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/part3.dir/build.make CMakeFiles/part3.dir/src/part3/c.cpp.s
.PHONY : src/part3/c.cpp.s

src/part4/d.o: src/part4/d.cpp.o
.PHONY : src/part4/d.o

# target to build an object file
src/part4/d.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/part4.dir/build.make CMakeFiles/part4.dir/src/part4/d.cpp.o
.PHONY : src/part4/d.cpp.o

src/part4/d.i: src/part4/d.cpp.i
.PHONY : src/part4/d.i

# target to preprocess a source file
src/part4/d.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/part4.dir/build.make CMakeFiles/part4.dir/src/part4/d.cpp.i
.PHONY : src/part4/d.cpp.i

src/part4/d.s: src/part4/d.cpp.s
.PHONY : src/part4/d.s

# target to generate assembly for a file
src/part4/d.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/part4.dir/build.make CMakeFiles/part4.dir/src/part4/d.cpp.s
.PHONY : src/part4/d.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... install"
	@echo "... install/local"
	@echo "... install/strip"
	@echo "... list_install_components"
	@echo "... rebuild_cache"
	@echo "... Dawnbreaker"
	@echo "... PartForYou"
	@echo "... ProvidedFramework"
	@echo "... SOIL"
	@echo "... freeglut"
	@echo "... freeglut_static"
	@echo "... part1"
	@echo "... part2"
	@echo "... part3"
	@echo "... part4"
	@echo "... src/PartForYou/GameObjects.o"
	@echo "... src/PartForYou/GameObjects.i"
	@echo "... src/PartForYou/GameObjects.s"
	@echo "... src/PartForYou/GameWorld.o"
	@echo "... src/PartForYou/GameWorld.i"
	@echo "... src/PartForYou/GameWorld.s"
	@echo "... src/ProvidedFramework/GameManager.o"
	@echo "... src/ProvidedFramework/GameManager.i"
	@echo "... src/ProvidedFramework/GameManager.s"
	@echo "... src/ProvidedFramework/ObjectBase.o"
	@echo "... src/ProvidedFramework/ObjectBase.i"
	@echo "... src/ProvidedFramework/ObjectBase.s"
	@echo "... src/ProvidedFramework/SpriteManager.o"
	@echo "... src/ProvidedFramework/SpriteManager.i"
	@echo "... src/ProvidedFramework/SpriteManager.s"
	@echo "... src/ProvidedFramework/WorldBase.o"
	@echo "... src/ProvidedFramework/WorldBase.i"
	@echo "... src/ProvidedFramework/WorldBase.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/part1/a.o"
	@echo "... src/part1/a.i"
	@echo "... src/part1/a.s"
	@echo "... src/part2/b.o"
	@echo "... src/part2/b.i"
	@echo "... src/part2/b.s"
	@echo "... src/part3/c.o"
	@echo "... src/part3/c.i"
	@echo "... src/part3/c.s"
	@echo "... src/part4/d.o"
	@echo "... src/part4/d.i"
	@echo "... src/part4/d.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
