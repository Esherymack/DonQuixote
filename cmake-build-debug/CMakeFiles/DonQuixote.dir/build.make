# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\esher\Documents\programming\school\370\assignments\DonQuixote

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\esher\Documents\programming\school\370\assignments\DonQuixote\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\DonQuixote.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\DonQuixote.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\DonQuixote.dir\flags.make

CMakeFiles\DonQuixote.dir\DonQuixote.cpp.obj: CMakeFiles\DonQuixote.dir\flags.make
CMakeFiles\DonQuixote.dir\DonQuixote.cpp.obj: ..\DonQuixote.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\esher\Documents\programming\school\370\assignments\DonQuixote\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DonQuixote.dir/DonQuixote.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\DonQuixote.dir\DonQuixote.cpp.obj /FdCMakeFiles\DonQuixote.dir\ /FS -c C:\Users\esher\Documents\programming\school\370\assignments\DonQuixote\DonQuixote.cpp
<<

CMakeFiles\DonQuixote.dir\DonQuixote.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DonQuixote.dir/DonQuixote.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx64\x64\cl.exe > CMakeFiles\DonQuixote.dir\DonQuixote.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\esher\Documents\programming\school\370\assignments\DonQuixote\DonQuixote.cpp
<<

CMakeFiles\DonQuixote.dir\DonQuixote.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DonQuixote.dir/DonQuixote.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\DonQuixote.dir\DonQuixote.cpp.s /c C:\Users\esher\Documents\programming\school\370\assignments\DonQuixote\DonQuixote.cpp
<<

CMakeFiles\DonQuixote.dir\utils.cpp.obj: CMakeFiles\DonQuixote.dir\flags.make
CMakeFiles\DonQuixote.dir\utils.cpp.obj: ..\utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\esher\Documents\programming\school\370\assignments\DonQuixote\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/DonQuixote.dir/utils.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\DonQuixote.dir\utils.cpp.obj /FdCMakeFiles\DonQuixote.dir\ /FS -c C:\Users\esher\Documents\programming\school\370\assignments\DonQuixote\utils.cpp
<<

CMakeFiles\DonQuixote.dir\utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DonQuixote.dir/utils.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx64\x64\cl.exe > CMakeFiles\DonQuixote.dir\utils.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\esher\Documents\programming\school\370\assignments\DonQuixote\utils.cpp
<<

CMakeFiles\DonQuixote.dir\utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DonQuixote.dir/utils.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\DonQuixote.dir\utils.cpp.s /c C:\Users\esher\Documents\programming\school\370\assignments\DonQuixote\utils.cpp
<<

CMakeFiles\DonQuixote.dir\glerror_utility.cpp.obj: CMakeFiles\DonQuixote.dir\flags.make
CMakeFiles\DonQuixote.dir\glerror_utility.cpp.obj: ..\glerror_utility.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\esher\Documents\programming\school\370\assignments\DonQuixote\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/DonQuixote.dir/glerror_utility.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\DonQuixote.dir\glerror_utility.cpp.obj /FdCMakeFiles\DonQuixote.dir\ /FS -c C:\Users\esher\Documents\programming\school\370\assignments\DonQuixote\glerror_utility.cpp
<<

CMakeFiles\DonQuixote.dir\glerror_utility.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DonQuixote.dir/glerror_utility.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx64\x64\cl.exe > CMakeFiles\DonQuixote.dir\glerror_utility.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\esher\Documents\programming\school\370\assignments\DonQuixote\glerror_utility.cpp
<<

CMakeFiles\DonQuixote.dir\glerror_utility.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DonQuixote.dir/glerror_utility.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\DonQuixote.dir\glerror_utility.cpp.s /c C:\Users\esher\Documents\programming\school\370\assignments\DonQuixote\glerror_utility.cpp
<<

# Object files for target DonQuixote
DonQuixote_OBJECTS = \
"CMakeFiles\DonQuixote.dir\DonQuixote.cpp.obj" \
"CMakeFiles\DonQuixote.dir\utils.cpp.obj" \
"CMakeFiles\DonQuixote.dir\glerror_utility.cpp.obj"

# External object files for target DonQuixote
DonQuixote_EXTERNAL_OBJECTS =

..\bin\DonQuixote.exe: CMakeFiles\DonQuixote.dir\DonQuixote.cpp.obj
..\bin\DonQuixote.exe: CMakeFiles\DonQuixote.dir\utils.cpp.obj
..\bin\DonQuixote.exe: CMakeFiles\DonQuixote.dir\glerror_utility.cpp.obj
..\bin\DonQuixote.exe: CMakeFiles\DonQuixote.dir\build.make
..\bin\DonQuixote.exe: CMakeFiles\DonQuixote.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\esher\Documents\programming\school\370\assignments\DonQuixote\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ..\bin\DonQuixote.exe"
	"C:\Program Files\JetBrains\CLion 2020.2\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\DonQuixote.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x64\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x64\mt.exe --manifests  -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx64\x64\link.exe /nologo @CMakeFiles\DonQuixote.dir\objects1.rsp @<<
 /out:..\bin\DonQuixote.exe /implib:DonQuixote.lib /pdb:C:\Users\esher\Documents\programming\school\370\assignments\DonQuixote\bin\DonQuixote.pdb /version:0.0  /machine:x64 /debug /INCREMENTAL /subsystem:console   -LIBPATH:C:\Users\esher\Documents\programming\school\370\assignments\DonQuixote\lib\Win  opengl32.lib glfw3.lib glew32.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\DonQuixote.dir\build: ..\bin\DonQuixote.exe

.PHONY : CMakeFiles\DonQuixote.dir\build

CMakeFiles\DonQuixote.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\DonQuixote.dir\cmake_clean.cmake
.PHONY : CMakeFiles\DonQuixote.dir\clean

CMakeFiles\DonQuixote.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\esher\Documents\programming\school\370\assignments\DonQuixote C:\Users\esher\Documents\programming\school\370\assignments\DonQuixote C:\Users\esher\Documents\programming\school\370\assignments\DonQuixote\cmake-build-debug C:\Users\esher\Documents\programming\school\370\assignments\DonQuixote\cmake-build-debug C:\Users\esher\Documents\programming\school\370\assignments\DonQuixote\cmake-build-debug\CMakeFiles\DonQuixote.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\DonQuixote.dir\depend

