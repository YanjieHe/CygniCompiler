# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

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
CMAKE_SOURCE_DIR = /home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly/build

# Include any dependencies generated for this target.
include CMakeFiles/Disassembly.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Disassembly.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Disassembly.dir/flags.make

CMakeFiles/Disassembly.dir/ByteCodeReader.cpp.o: CMakeFiles/Disassembly.dir/flags.make
CMakeFiles/Disassembly.dir/ByteCodeReader.cpp.o: ../ByteCodeReader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Disassembly.dir/ByteCodeReader.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Disassembly.dir/ByteCodeReader.cpp.o -c /home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly/ByteCodeReader.cpp

CMakeFiles/Disassembly.dir/ByteCodeReader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Disassembly.dir/ByteCodeReader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly/ByteCodeReader.cpp > CMakeFiles/Disassembly.dir/ByteCodeReader.cpp.i

CMakeFiles/Disassembly.dir/ByteCodeReader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Disassembly.dir/ByteCodeReader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly/ByteCodeReader.cpp -o CMakeFiles/Disassembly.dir/ByteCodeReader.cpp.s

CMakeFiles/Disassembly.dir/ByteCodeViewer.cpp.o: CMakeFiles/Disassembly.dir/flags.make
CMakeFiles/Disassembly.dir/ByteCodeViewer.cpp.o: ../ByteCodeViewer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Disassembly.dir/ByteCodeViewer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Disassembly.dir/ByteCodeViewer.cpp.o -c /home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly/ByteCodeViewer.cpp

CMakeFiles/Disassembly.dir/ByteCodeViewer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Disassembly.dir/ByteCodeViewer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly/ByteCodeViewer.cpp > CMakeFiles/Disassembly.dir/ByteCodeViewer.cpp.i

CMakeFiles/Disassembly.dir/ByteCodeViewer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Disassembly.dir/ByteCodeViewer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly/ByteCodeViewer.cpp -o CMakeFiles/Disassembly.dir/ByteCodeViewer.cpp.s

CMakeFiles/Disassembly.dir/Instruction.cpp.o: CMakeFiles/Disassembly.dir/flags.make
CMakeFiles/Disassembly.dir/Instruction.cpp.o: ../Instruction.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Disassembly.dir/Instruction.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Disassembly.dir/Instruction.cpp.o -c /home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly/Instruction.cpp

CMakeFiles/Disassembly.dir/Instruction.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Disassembly.dir/Instruction.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly/Instruction.cpp > CMakeFiles/Disassembly.dir/Instruction.cpp.i

CMakeFiles/Disassembly.dir/Instruction.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Disassembly.dir/Instruction.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly/Instruction.cpp -o CMakeFiles/Disassembly.dir/Instruction.cpp.s

CMakeFiles/Disassembly.dir/Test.cpp.o: CMakeFiles/Disassembly.dir/flags.make
CMakeFiles/Disassembly.dir/Test.cpp.o: ../Test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Disassembly.dir/Test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Disassembly.dir/Test.cpp.o -c /home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly/Test.cpp

CMakeFiles/Disassembly.dir/Test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Disassembly.dir/Test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly/Test.cpp > CMakeFiles/Disassembly.dir/Test.cpp.i

CMakeFiles/Disassembly.dir/Test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Disassembly.dir/Test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly/Test.cpp -o CMakeFiles/Disassembly.dir/Test.cpp.s

CMakeFiles/Disassembly.dir/main.cpp.o: CMakeFiles/Disassembly.dir/flags.make
CMakeFiles/Disassembly.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Disassembly.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Disassembly.dir/main.cpp.o -c /home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly/main.cpp

CMakeFiles/Disassembly.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Disassembly.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly/main.cpp > CMakeFiles/Disassembly.dir/main.cpp.i

CMakeFiles/Disassembly.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Disassembly.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly/main.cpp -o CMakeFiles/Disassembly.dir/main.cpp.s

# Object files for target Disassembly
Disassembly_OBJECTS = \
"CMakeFiles/Disassembly.dir/ByteCodeReader.cpp.o" \
"CMakeFiles/Disassembly.dir/ByteCodeViewer.cpp.o" \
"CMakeFiles/Disassembly.dir/Instruction.cpp.o" \
"CMakeFiles/Disassembly.dir/Test.cpp.o" \
"CMakeFiles/Disassembly.dir/main.cpp.o"

# External object files for target Disassembly
Disassembly_EXTERNAL_OBJECTS =

Disassembly: CMakeFiles/Disassembly.dir/ByteCodeReader.cpp.o
Disassembly: CMakeFiles/Disassembly.dir/ByteCodeViewer.cpp.o
Disassembly: CMakeFiles/Disassembly.dir/Instruction.cpp.o
Disassembly: CMakeFiles/Disassembly.dir/Test.cpp.o
Disassembly: CMakeFiles/Disassembly.dir/main.cpp.o
Disassembly: CMakeFiles/Disassembly.dir/build.make
Disassembly: CMakeFiles/Disassembly.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable Disassembly"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Disassembly.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Disassembly.dir/build: Disassembly

.PHONY : CMakeFiles/Disassembly.dir/build

CMakeFiles/Disassembly.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Disassembly.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Disassembly.dir/clean

CMakeFiles/Disassembly.dir/depend:
	cd /home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly /home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly /home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly/build /home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly/build /home/jasonhe/Documents/MyCode/CPP/JuCi++/Disassembly/build/CMakeFiles/Disassembly.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Disassembly.dir/depend
