# Introduction

## What Is CMake?

CMake is a cross-platform tool designed to manage the build process of software projects. It uses simple configuration files called CMakeLists.txt to generate native build scripts for various platforms, such as Makefiles for Unix or project files for Visual Studio.

In this article, we'll talk about using CMake on Unix-like systems. Before exploring more about CMake, let's make sure we have a complete understanding of [GNU Make](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/GNU_Make).

CMake is a scripting language written in C++ programming language. It includes several components, each serving a specific purpose in the build and testing workflow: cmake, ctest and cpack.

```
worker@7e4a84e41875:~/study_workspace/CPP_Build_Toolchain$ which cmake
/usr/bin/cmake
worker@7e4a84e41875:~/study_workspace/CPP_Build_Toolchain$ which ctest
/usr/bin/ctest
worker@7e4a84e41875:~/study_workspace/CPP_Build_Toolchain$ which cpack
/usr/bin/cpack
```

**CMake** is the core component of the CMake package that generating compiler-independent build instruction.
**CTest** is a testing tool that comes with CMake. It is used to automate the execution of tests for a project.
**CPack** is a packaging tool that comes with CMake. It is used to create installers and packages for software projects.

## Benefits Of Using CMake

**Compatibility**: Works on Windows, macOS, and Linux. Compatible with all mordern C++ standards (C++11, C++14, C++17, ...).

**Flexibility**: Can generate build files for different build systems and various compilers such as GCC, CLang, MSVC. Most of the IDE support CMake, and CMake also support those IDE.

**Popularity**: CMake is widely used. The chance to find a preinstalled module/library with CMake is higher than any other build system. 

**Modularity**: Easy to manage complex projects with multiple components.

### CMake Installation

Install via package manager tool. For example in Linux:

```
sudo apt-get update
sudo apt-get install cmake
```

Or download CMake source code and compile yourself:

```
wget https://github.com/Kitware/CMake/releases/download/v3.30.2/cmake-3.30.2.tar.gz
tar -xzvf cmake-3.30.2.tar.gz
cd cmake-3.30.2
./bootstrap
make
sudo make install
```

Verify the installation by running:

```
worker@7e4a84e41875:~/study_workspace$ cmake --version
cmake version 3.10.2

CMake suite maintained and supported by Kitware (kitware.com/cmake).
```

# Build HelloWorld Project

As all new programmers, we start with HelloWorld project.

[https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/CMake/SampleProjects/01_HelloWorld](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/CMake/SampleProjects/01_HelloWorld)

It appears a simple source file:

```
// main.cpp
#include <iostream>

int main()
{
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
```

Create a CMakeLists.txt file:

```
cmake_minimum_required(VERSION 3.10)
project(HelloWorld)

add_executable(HelloWorld main.cpp)
```

Generate build files and compile:

```
mkdir build
cd build
cmake ..
make
```

Run the executable:

```
./HelloWorld
```

Generally, CMake is considered easier to set up and use compared to [GNU Autotools](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/GNU_Autotools).

CMake reads the ```CMakeLists.txt``` file and generates the [Makefile](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/GNU_Make) file.

![](https://raw.githubusercontent.com/nguyenchiemminhvu/CPP_Build_Toolchain/master/CMake/CMake_Build_Process.png)

Now, the only thing we care for is the syntax of writing CMakeLists.txt file.

# CMakeLists.txt Syntax And Commands

## General Outline Of CMakeLists.txt

**Minimum CMake Version**: Specify the minimum required version of CMake.

```
cmake_minimum_required(VERSION 3.10)
```

**Project Name and Version**: Define the name and version of the project.

```
project(MyProject VERSION 1.0)
```

**Specify C++ Standard** (if applicable): Set the C++ standard to be used.

```
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
```

**Include Directories**: Specify directories to be included during the build process.

```
include_directories(${PROJECT_SOURCE_DIR}/include)
```

**Source Files**: List the source files to be compiled.

```
set(SOURCES
    src/main.cpp
    src/other_file.cpp
)
```

**Add Executable or Library**: Define the executable or library to be built.

```
add_executable(MyExecutable ${SOURCES})
# or for a library
add_library(MyLibrary ${SOURCES})
```

**Link Libraries**: Link against other libraries.

```
target_link_libraries(MyExecutable PRIVATE SomeLibrary)
```

**Add Subdirectories**: Include other CMakeLists.txt files from subdirectories.

```
add_subdirectory(src)
add_subdirectory(tests)
```

**Custom Commands and Targets**: Define custom commands and targets if needed.

```
add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/generated_file.cpp
    COMMAND some_command
    DEPENDS some_dependency
)
```

**Install Rules**: Specify installation rules.

```
install(TARGETS MyExecutable DESTINATION bin)
install(FILES ${PROJECT_SOURCE_DIR}/include/my_header.h DESTINATION include)
```

**Testing**: Enable and define tests.

```
enable_testing()
add_test(NAME MyTest COMMAND MyExecutable)
```

**Options and Configurations**: Define options and configurations.

```
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
```

This is a basic structure and can be expanded based on the specific needs of your project.

Don't be afraid at the first sight. Let's walk through each component of CMakeList.txt file.

## Basic Syntax And Structure

### cmake_minimum_required

A top-level CMakeLists.txt file typically starts with specifying the minimum required version of CMake and the project name:

```
cmake_minimum_required(VERSION <min_version>...<max_version> [FATAL_ERROR])
```

```VERSION <min_version>```: Specifies the minimum required version of CMake. This is a mandatory argument.

```<max_version>```: (Optional) Specifies the maximum version of CMake that is supported. This is rarely used.

```FATAL_ERROR```: (Optional) If specified, CMake will stop processing and report an error if the version requirement is not met.

For example:

```
cmake_minimum_required(VERSION 3.10...3.20)
```

### project

The ```project``` command is used to define the name, version, and supported language of a project.

```
project(<project-name> [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]]
        [DESCRIPTION <project-description>]
        [HOMEPAGE_URL <url>]
        [LANGUAGES <language-name>...])
```

```<project-name>```: The name of the project. This is a mandatory argument.

```VERSION <major>[.<minor>[.<patch>[.<tweak>]]]```: (Optional) Specifies the version of the project.

```DESCRIPTION <project-description>```: (Optional) Provides a description of the project.

```HOMEPAGE_URL <url>```: (Optional) Specifies the homepage URL for the project.

```LANGUAGES <language-name>...```: (Optional) Specifies the programming languages used in the project. Common languages include C, CXX (C++), Fortran, etc.

For example:

```
project(libNmea VERSION 1.0.1 DESCRIPTION "Generate NMEA sentences" HOMEPAGE_URL "https://nmea.sourceforge.net" LANGUAGE C CXX)
```

Variables Set by project command:

```PROJECT_NAME```: The name of the project.

```PROJECT_VERSION```: The full version string of the project.

```PROJECT_VERSION_MAJOR```: The major version number.

```PROJECT_VERSION_MINOR```: The minor version number.

```PROJECT_VERSION_PATCH```: The patch version number.

```PROJECT_VERSION_TWEAK```: The tweak version number.

```PROJECT_DESCRIPTION```: The description of the project.

```PROJECT_HOMEPAGE_URL```: The homepage URL of the project.

```PROJECT_SOURCE_DIR```: The source directory of the project.

```PROJECT_BINARY_DIR```: The binary directory of the project.

Modify project command in HelloWorld project for example:

```
cmake_minimum_required(VERSION 3.10)

project(HelloWorld VERSION 1.0.0 DESCRIPTION "Print HelloWorld on Console" LANGUAGES C CXX)

message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "Project Version: ${PROJECT_VERSION}")
message(STATUS "Project Description: ${PROJECT_DESCRIPTION}")
message(STATUS "Project Source Dir: ${PROJECT_SOURCE_DIR}")
message(STATUS "Project Binary Dir: ${PROJECT_BINARY_DIR}")

add_executable(HelloWorld main.cpp)
```

```
worker@7e4a84e41875:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/01_HelloWorld/build$ cmake ..
...
-- Project Name: HelloWorld
-- Project Version: 1.0.0
-- Project Description: Print HelloWorld on Console
-- Project Source Dir: /home/worker/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/01_HelloWorld
-- Project Binary Dir: /home/worker/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/01_HelloWorld/build
```

### set variables

The ```set``` command is used to define and manipulate variables. These variables can be used to control the build process, store configuration options, path, and other data.

```
set(<variable> <value>... [CACHE <type> <docstring> [FORCE]])
```

```<variable>```: The name of the variable to set.

```<value>```: The value(s) to assign to the variable. Multiple values are separated by spaces.

```CACHE```: Indicates that the variable should be stored in the CMake cache.

```<type>```: The type of the cache variable (e.g., STRING, BOOL, PATH, FILEPATH).

```<docstring>```: A description of the cache variable.

```FORCE```: Forces the cache variable to be set to the specified value, even if it already exists.

For example:

```
set(MY_VARIABLE "Hello, World!")
message(STATUS "The value of MY_VARIABLE is: ${MY_VARIABLE}")

set(MY_CACHE_VARIABLE "default_value" CACHE STRING "This is a cache variable")
set(MY_CACHE_VARIABLE "new_value" CACHE STRING "This is a cache variable" FORCE)

set(SOURCES
    src/main.cpp
    src/helper.cpp
    src/utils.cpp
)

add_executable(MyExecutable ${SOURCES})
```

To set an environment variable:

```
set(ENV{<variable_name>} <value>)
```

```ENV{<variable_name>}```: The name of the environment variable to set.
```<value>```: The value to assign to the environment variable.

For example:

```
set(ENV{MY_ENV_VAR} "some_value")
message(STATUS "The value of environment variable MY_ENV_VAR: $ENV{MY_ENV_VAR}")
```

This sets the environment variable MY_ENV_VAR to "some_value".

### include_directories

The ```include_directories``` command is used to specify directories that the compiler should search for header files during the build process. In case all necessary header files are located in standard system directories like ```/usr/include```, ```/usr/local/include```, or other directories that the compiler searches by default, we don't need to use ```include_directories``` command in CMake.

```
include_directories([AFTER|BEFORE] [SYSTEM] dir1 [dir2 ...])
```

```AFTER```: Adds the directories to the end of the list of include directories.

```BEFORE```: Adds the directories to the beginning of the list of include directories.

```SYSTEM```: Marking directories as system include directories can be useful to suppress warnings from third-party headers.

```dir1 dir2 ...```: The directories to be added to the include path.

For example:

```
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
```

While ```include_directories``` command is a global command that affects all targets, it's often better to use target-specific commands like ```target_include_directories``` to avoid unintended side effects.

```
target_include_directories(<target> [SYSTEM] [AFTER|BEFORE]
  <INTERFACE|PUBLIC|PRIVATE> [items1...]
  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
```

```<target>```: The name of the target to which the include directories will be applied.

```SYSTEM```: Marking directories as system include directories can be useful to suppress warnings from third-party headers.

```AFTER | BEFORE```: Controls the order in which directories are added to the include path. AFTER adds directories to the end, and BEFORE adds them to the beginning.

```<INTERFACE|PUBLIC|PRIVATE>```: Specifies the scope of the include directories.

```INTERFACE```: Include directories are used by targets that link to this target but not by the target itself.

```PUBLIC```: Include directories are used by both the target itself and by targets that link to this target.

```PRIVATE```: Include directories are used only by the target itself.

For example:

```
cmake_minimum_required(VERSION 3.10)
project(MyProject)

add_library(MyLibrary src/mylibrary.cpp)

target_include_directories(MyLibrary
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_SOURCE_DIR}/ext_include
    SYSTEM
        ${CMAKE_SOURCE_DIR}/third_party/include
)
```

In this example, CMakeLists.txt file specify a target MyLibrary to be built as library.

```PUBLIC ${CMAKE_SOURCE_DIR}/include```: The include directory is added to the include path for both MyLibrary and any target that links to MyLibrary.

```PRIVATE ${CMAKE_SOURCE_DIR}/ext_include```: The src directory is added to the include path only for MyLibrary.

```SYSTEM ${CMAKE_SOURCE_DIR}/third_party/include```: The third_party/include directory is added as a system include directory, which can suppress warnings from headers in this directory.

### add_executable

The ```add_executable``` command is used to define an executable target from a set of source files.

```
add_executable(<name> [WIN32] [MACOSX_BUNDLE] [EXCLUDE_FROM_ALL]
               [source1] [source2 ...])
```

```<name>```: The name of the executable target.

```[WIN32]```: Optional. Specifies that the executable is a Windows GUI application on Windows. This option sets the WIN32 property of the target.

```[MACOSX_BUNDLE]```: Optional. Specifies that the executable is a macOS bundle. This option sets the MACOSX_BUNDLE property of the target.

```[EXCLUDE_FROM_ALL]```: Optional. Excludes the target from the default build target. This means the executable will not be built unless explicitly specified.

```[source1] [source2 ...]```: A list of source files that will be compiled to create the executable.

For example:

```
add_executable(SimpleMath main.cpp geometry.cpp algebra.cpp)
```

### add_library

The ```add_library``` is used to define a library target from a set of source files.

```
add_library(<name> [STATIC | SHARED | MODULE]
            [EXCLUDE_FROM_ALL]
            [source1] [source2 ...])
```

```<name>```: The name of the library target.

```[STATIC | SHARED | MODULE]```: Optional. Specifies the type of library to be created. If not specified, the default type is STATIC.

```STATIC```: Creates a static library.

```SHARED```: Creates a shared library.

```MODULE```: Creates a module library, a type of shared library that is not linked into an executable but is loaded at runtime. This is often used for plugins.

```[EXCLUDE_FROM_ALL]```: Optional. Excludes the target from the default build target. This means the library will not be built unless explicitly specified.

```[source1] [source2 ...]```: A list of source files that will be compiled to create the library.

For example:

```
add_library(LibFormattedData STATIC my_json.cpp my_xml.cpp my_csv.cpp)
or
add_library(LibFormattedData SHARED my_json.cpp my_xml.cpp my_csv.cpp)
```

When using ```add_library``` command without specifying STATIC, or SHARED, or MODULE option, the type of library that will be built depends on the value of the BUILD_SHARED_LIBS variable.

```
add_library(SampleLib ${SampleSources})
```

behaves as if written

```
if(BUILD_SHARED_LIBS)
    add_library(SampleLib SHARED ${SampleSources})
else()
    add_library(SampleLib STATIC ${SampleSources})
endif()
```

CMake does not define BUILD_SHARED_LIBS by default, but projects often create a cache entry for it using the ```option``` command:

```
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
```

**Is it possible to build both static and shared library for one target?**

No, it is not possible, but it requires two different target names.

```
set(LIB_SOURCES my_json.cpp my_xml.cpp my_csv.cpp)
add_library(LibFormattedDataStatic STATIC ${LIB_SOURCES})
add_library(LibFormattedDataShared SHARED ${LIB_SOURCES})
```

### target_link_libraries

The ```target_link_libraries``` command is used to specify libraries or targets that a particular target (such as an executable or another library) should be linked against. The command plays an important role in dependency management between different parts of a project, ensure that linker tool can resolve symbols correctly.

```
target_link_libraries(<target> [item1 [item2 [...]]]
                      [<keyword> <value>]...)
```

```<target>```: The name of the target to which we want to link libraries. The named ```<target>``` must have been created by a command such as ```add_executable()``` or ```add_library()```.

```[item1 [item2 [...]]]```: A list of libraries or targets to link against. The named ```items``` must be created by add_library() within the project or from Imported libraries. Item names starting with -, but not -l or -framework, are treated as linker flags, but preferred to use ```target_link_options``` command to add linker flags explicitly.

```[<keyword> <value>]...```: Optional keywords and values to specify additional linking properties.

**Keywords**

```PRIVATE```: The libraries specified after this keyword are linked only to the target and are not propagated to other targets that link against this target.

```PUBLIC```: The libraries specified after this keyword are linked to the target and are also propagated to other targets that link against this target.

```INTERFACE```: The libraries specified after this keyword are not linked to the target itself but are propagated to other targets that link against this target.

For example:

```
add_library(LibSimpleMath STATIC geometry.cpp algebra.cpp)
add_library(LibFormattedData STATIC my_json.cpp my_xml.cpp my_csv.cpp)

add_executable(MathExe main.cpp)
target_link_libraries(MathExe PRIVATE LibSimpleMath LibFormattedData)
```

### link_directories

The ```link_directories``` command is used to specify the directories where the linker should look for libraries when linking a target. In case all necessary libraries are located in standard system directories like ```/usr/lib```, ```/usr/local/lib```, or other directories that the linker searches by default, we don't need to use ```link_directories``` command in CMake.

```
link_directories(directory1 [directory2 ...])
```

```directory1 [directory2 ...]```: A list of directories to be added to the linker search path.

For example:

```
add_library(SimpleMD5 ${CMAKE_CURRENT_SOURCE_DIR}/opensource/src/md5.cpp)
add_library(SimpleBase64 ${CMAKE_CURRENT_SOURCE_DIR}/opensource/src/base64.cpp)

add_executable(SimpleEncryptor src/main.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/opensource/include)

# Note: This is generally not required if we are building the libraries within the same project.
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/opensource/build/)

target_link_libraries(SimpleEncryptor SimpleMD5 SimpleBase64)
```

While ```link_directories``` command is a global command that affects all targets, it's often better to use target-specific commands like ```target_link_directories``` to avoid unintended side effects. (New in version 3.13)

```
target_link_directories(<target> [BEFORE] <INTERFACE|PUBLIC|PRIVATE> [items1 [items2 ...]])
```

```<target>```: The name of the target to which we want to add link directories.

```BEFORE (optional)```: If specified, the directories will be added to the beginning of the search path.

```<INTERFACE|PUBLIC|PRIVATE>```: Specifies the scope of the directories.

```INTERFACE```: The directories are used by targets that link against this target but not by the target itself.

```PUBLIC```: The directories are used by both the target and targets that link against this target.

```PRIVATE```: The directories are used only by the target itself.

```[items1 [items2 ...]]```: A list of directories to be added to the linker search path.

For example:

```
add_library(SimpleMD5 ${CMAKE_CURRENT_SOURCE_DIR}/opensource/src/md5.cpp)
target_include_directories(SimpleMD5 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/opensource/include)

add_library(SimpleBase64 ${CMAKE_CURRENT_SOURCE_DIR}/opensource/src/base64.cpp)
target_include_directories(SimpleBase64 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/opensource/include)

add_executable(SimpleEncryptor src/main.cpp)
target_include_directories(SimpleEncryptor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/opensource/include)

# Note: This is generally not required if we are building the libraries within the same project.
target_link_directories(SimpleEncryptor ${CMAKE_CURRENT_SOURCE_DIR}/opensource/build/)

target_link_libraries(SimpleEncryptor SimpleMD5 SimpleBase64)
```

### target_sources

The ```target_sources``` is used to specify additional source files for a target (an executable or library). It is useful to organize and manage source files more effectively within CMake project.

```
target_sources(<target>
  <INTERFACE|PUBLIC|PRIVATE> [items1...]
  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
```

```<target>```: The name of the target to which we want to add source files.

```[PRIVATE | PUBLIC | INTERFACE]```: These keywords specify the scope of the source files being added. They determine how the source files are treated with respect to the target's usage requirements.

```PRIVATE```: The source files are used only for the target itself.

```PUBLIC```: The source files are used for the target and are also propagated to targets that link against this target.

```INTERFACE```: The source files are not used for the target itself but are propagated to targets that link against this target.

For example:

```
add_executable(MyExe main.cpp)

target_sources(MyExe
    PRIVATE
        src/file1.cpp
        src/file2.cpp
    PUBLIC
        src/file3.cpp
        src/file4.cpp
)
```

### target_compile_options

The ```target_compile_options``` is used to specify additional compiler options that are necessary for a target at compilation stage.

```
target_compile_options(<target> [BEFORE] <INTERFACE|PUBLIC|PRIVATE> [items1...])
```

```<target>```: The name of the target to which you want to add compiler options.

```BEFORE (optional)```: If specified, the options will be added before any options that are added by CMake or other commands. This can be useful if you need to ensure that your options take precedence.

```<INTERFACE|PUBLIC|PRIVATE>```: Specifies the scope of the options.

```INTERFACE```: The options are used by targets that link to this target, but not by the target itself.

```PUBLIC```: The options are used by both the target itself and by targets that link to this target.

```PRIVATE```: The options are used only by the target itself.

```[items1...]```: The actual compiler options you want to add.

For example:

```
add_executable(SampleProgram main.cpp)

target_compile_options(SampleProgram PRIVATE -Wall -Wextra -fpermissive)
```

### target_link_options

The ```target_link_options``` command is used to specify linker flags that are necessary for the linker when building a target. It was introduced in CMake 3.13.

```
target_link_options(<target> [BEFORE] <INTERFACE|PUBLIC|PRIVATE> [items1...])
```

```<target>```: The name of the target to which you want to add linker options.

```BEFORE (optional)```: If specified, the options will be added before any options that are added by CMake or other commands. This can be useful if you need to ensure that your options take precedence.

```<INTERFACE|PUBLIC|PRIVATE>```: Specifies the scope of the options.

```INTERFACE```: The options are used by targets that link to this target, but not by the target itself.

```PUBLIC```: The options are used by both the target itself and by targets that link to this target.

```PRIVATE```: The options are used only by the target itself.

```[items1...]```: The actual linker options you want to add.

For example:

```
add_executable(SampleProgram main.cpp)

target_link_libraries(SampleProgram LibUtil)
target_link_options(SampleProgram PRIVATE -Wl,--no-undefined)
```

### add_definitions

The ```add_definitions``` command is used to add preprocessor definitions to the compilation of source files for targets in the current directory. This command can be used to add other compilation flags, but it is intended to add preprocessor definitions.

```
add_definitions(-D<definition> ...)
```

```-D<definition>```: This specifies a preprocessor definition. The -D flag is followed by the definition you want to add. You can add multiple definitions by separating them with spaces.

For example:

```
add_definitions(-DDEBUG -DVERSION=2 -DUSE_CHINA_SHIFT_SHARED_OBJ)
```

### target_compile_definitions

In order to add definitions for just a specific target, use ```target_compile_definitions``` command instead, which provides more control and recommended approach in modern CMake.

```
target_compile_definitions(<target> [<INTERFACE|PUBLIC|PRIVATE>] [items1...])
```

```<target>```: The name of the target to which you want to add the preprocessor definitions.

```<INTERFACE|PUBLIC|PRIVATE>```: Specifies the scope of the definitions.

```PRIVATE```: The definitions are used only when compiling the target itself.

```PUBLIC```: The definitions are used both when compiling the target itself and when compiling other targets that link to this target.

```INTERFACE```: The definitions are used only when compiling other targets that link to this target.

```[items1...]```: The list of preprocessor definitions to add.

For example:

```
cmake_minimum_required(VERSION 3.10)
project(SampleProject)

add_executable(SampleProgram main.cpp)
target_compile_definitions(SampleProgram PRIVATE DEBUG VERSION=2)
```

### add_subdirectory

The ```add_subdirectory``` command is used to add sub-directories to the build, allow us to include another CMakeLists.txt file from a sub-directory, which can define additional targets, libraries, and other build-related settings. It is useful for organizing large projects into smaller components.

```
add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL])
```

```source_dir```: The relative or absolute path to the source directory containing the CMakeLists.txt file you want to include.

```binary_dir (optional)```: The directory where the build files for the subdirectory will be placed. If not specified, it defaults to the same directory as source_dir.

```EXCLUDE_FROM_ALL (optional)```: If specified, the targets in the subdirectory will not be built unless explicitly requested. This is useful for optional components or examples that should not be built by default.

For example, consider a sample project with the following structure:

```
project_root/
├── CMakeLists.txt
├── src/
│   ├── CMakeLists.txt
│   ├── main.cpp
├── lib/
│   ├── CMakeLists.txt
│   ├── mylib.cpp
│   ├── mylib.h
```

**Top-level CMakeLists.txt**
```
cmake_minimum_required(VERSION 3.10)
project(SampleProject)

add_subdirectory(src)
add_subdirectory(lib)
```

**src/CMakeLists.txt**
```
add_executable(SampleProgram main.cpp)

target_link_libraries(SampleProgram PRIVATE SampleLib)
```

**lib/CMakeLists.txt**
```
add_library(SampleLib STATIC util.cpp)
```

The top-level CMakeLists.txt file tells CMake to process the CMakeLists.txt files in src and lib sub-folders.

The src/CMakeLists.txt file defines a executable file called SampleProgram from main.cpp file, linked with SampleLib library which is defined in the lib subdirectory.

The lib/CMakeLists.txt file defines a library target SampleLib from util.cpp file.

## Practice the basis

[https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/CMake/SampleProjects/02_BuildSubDirs](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/CMake/SampleProjects/02_BuildSubDirs)

```
worker@7e4a84e41875:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/02_BuildSubDirs$ tree
.
├── CMakeLists.txt
├── main.cpp
├── opensource
│   ├── CMakeLists.txt
│   └── jsoncpp
│       ├── include
│       │   └── json
│       │       ├── allocator.h
│       │       ├── assertions.h
│       │       ├── config.h
│       │       ├── forwards.h
│       │       ├── json.h
│       │       ├── json_features.h
│       │       ├── reader.h
│       │       ├── value.h
│       │       ├── version.h
│       │       └── writer.h
│       └── src
│           ├── json_reader.cpp
│           ├── json_tool.h
│           ├── json_value.cpp
│           ├── json_valueiterator.inl
│           └── json_writer.cpp
├── simple_algo.cpp
├── simple_algo.h
├── simple_math.cpp
└── simple_math.h
```

**Top-level CMakeLists.txt**
```
cmake_minimum_required(VERSION 3.10)
project(Utility VERSION 1.0 DESCRIPTION "Simple utility features" LANGUAGES C CXX)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/opensource)

add_executable(utility main.cpp)

target_sources(
    utility
    PRIVATE
        simple_algo.cpp
        simple_math.cpp
)

target_include_directories(
    utility
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/opensource/jsoncpp/include
)

target_link_libraries(utility PRIVATE jsoncpp)
```

**opensource/CMakeLists.txt**
```
cmake_minimum_required(VERSION 3.10)
project(JSONCPP VERSION 1.0 DESCRIPTION "jsoncpp opensource library" LANGUAGES C CXX)

set(JSONCPP_SOURCES SHARED
    jsoncpp/src/json_reader.cpp
    jsoncpp/src/json_value.cpp
    jsoncpp/src/json_writer.cpp
)

add_library(jsoncpp ${JSONCPP_SOURCES})

target_include_directories(jsoncpp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/jsoncpp/include)
```

## Advance Syntax And Structure

### add_custom_target

The ```add_custom_target``` command is used to add a target with the given name that executes the given commands. The added targets are not directly associated with building source files into executables or libraries, they has no output files and are always considered out-of-date even if the commands try to create the file with the name of the target.

```
add_custom_target(<name> [ALL] [command1 [args1...]] [command2 [args2...]] ...
                  [DEPENDS [depend1 [depend2 ...]]]
                  [BYPRODUCTS [file1 [file2 ...]]]
                  [WORKING_DIRECTORY dir]
                  [COMMENT comment]
                  [VERBATIM] [USES_TERMINAL]
                  [COMMAND_EXPAND_LISTS]
                  [SOURCES src1 [src2 ...]])
```

```<name>```: The name of the custom target.

```ALL```: If specified, the custom target will be built when the default all target is built.

```COMMAND```: Specifies a command to be executed. Multiple COMMAND arguments can be provided.

```DEPENDS```: Specifies files or targets that this target depends on. These dependencies will be built before the custom target.

```BYPRODUCTS```: Specifies files that are produced as a result of the custom target. This helps CMake understand the outputs of the custom command.

```WORKING_DIRECTORY```: Specifies the working directory in which the command will be executed.

```COMMENT```: Provides a comment that will be displayed when the target is built.

```VERBATIM```: Ensures that the command is passed to the shell exactly as written, without any modifications.

```USES_TERMINAL```: Indicates that the command uses the terminal for interactive input.

```COMMAND_EXPAND_LISTS```: Expands lists in the command arguments.

```SOURCES```: Specifies source files associated with the target. This is mainly for IDE integration.

By default, nothing depends on the custom target. Using ```add_dependencies``` command to create dependencies to or from other targets.

The ```add_dependencies``` command is used to add dependencies between top-level targets. This ensures that a target is built only after its dependencies have been built. It is useful when we have custom targets or when we need to enforce a specific build order.

```
add_dependencies(<target> [<dependency>...])
```

```<target>```: The name of the target that you want to add dependencies to.

```<dependency>```: One or more names of targets that ```<target>``` depends on.

For example:

```
add_custom_target(generate_data
    COMMAND ${CMAKE_COMMAND} -E echo "Generating data..."
    COMMENT "Running data generating script"
)

add_custom_target(process_data
    COMMAND ${CMAKE_COMMAND} -E echo "Processing data..."
    DEPENDS generate_data
    COMMENT "Running data processing script"
)

add_custom_target(all_targets ALL)
add_dependencies(all_targets process_data)
```

Result of running build process:

```
mkdir build
cd build
cmake ..
make

Scanning dependencies of target generate_data
[ 50%] Running data generating script
Generating data...
[ 50%] Built target generate_data
Scanning dependencies of target process_data
[100%] Running data processing script
Processing data...
[100%] Built target process_data
Scanning dependencies of target all_targets
[100%] Built target all_targets
```

### add_custom_command

The ```add_custom_command``` command is used to define custom build rules, allow us to specify commands to be executed at build time, which can generate files or perform other tasks that are not parts of the standard compilation process.

There are 2 primary ways to use ```add_custom_command```:

**Adding custom commands to produce an output. (Generate files as part of the build process)**

```
add_custom_command(
    OUTPUT <output1> [<output2> ...]
    COMMAND <command1> [ARGS <arg1> <arg2> ...] [<command2> [ARGS <arg1> <arg2> ...] ...]
    [MAIN_DEPENDENCY <main_dependency>]
    [DEPENDS [<dependency1> ...]]
    [BYPRODUCTS [<byproduct1> ...]]
    [IMPLICIT_DEPENDS <lang1> <dep1> ...]
    [WORKING_DIRECTORY <dir>]
    [COMMENT <comment>]
    [DEPFILE <depfile>]
    [JOB_POOL <pool>]
    [VERBATIM]
    [APPEND]
    [USES_TERMINAL]
    [COMMAND_EXPAND_LISTS]
)
```

This defines a command to generate specified OUTPUT file(s).

```OUTPUT```: Specifies the files that will be generated by the custom command. These files are considered outputs of the build step and can be used as dependencies for other build steps.

```COMMAND```: Specifies the command to be executed. You can provide multiple commands, each with its own set of arguments. The ARGS keyword is optional and can be used to specify arguments for the command.

```MAIN_DEPENDENCY```: Specifies the main dependency file. This is useful for cases where the custom command generates an output file from a single input file.

```DEPENDS```: Lists additional files or targets that the custom command depends on. These dependencies ensure that the custom command is executed only after the specified dependencies are up-to-date.

```BYPRODUCTS```: Specifies files that are produced as side effects of the custom command. These files are not the primary outputs but are still important for the build process.

```IMPLICIT_DEPENDS```: Specifies implicit dependencies for the custom command. This is useful for languages that have implicit dependencies, such as C++ header files.

```WORKING_DIRECTORY```: Specifies the working directory in which the command will be executed.

```COMMENT```: Provides a comment that will be displayed when the custom command is executed. This can be useful for providing context or information to the user.

```DEPFILE```: Specifies a dependency file that lists additional dependencies for the custom command. This is often used with compilers that generate dependency files.

```JOB_POOL```: Specifies a job pool for the custom command. This can be used to control the concurrency of custom commands.

```VERBATIM```: Ensures that the command and its arguments are passed to the shell exactly as specified. This is important for commands that require precise argument formatting.

```APPEND```: Appends the custom command to the existing commands for the specified output files. This allows you to add multiple custom commands for the same output.

```USES_TERMINAL```: Indicates that the custom command uses a terminal for its execution. This is useful for commands that require user interaction or produce output that should be visible to the user.

```COMMAND_EXPAND_LISTS```: Expands lists in the command arguments. This is useful for commands that take a variable number of arguments.

For example:

```

```

**Adding custom commands to a target (executable or library). (Execute commands before or after building a target)**

```
add_custom_command(TARGET <target>
                   PRE_BUILD | PRE_LINK | POST_BUILD
                   COMMAND command1 [ARGS] [args1...]
                   [COMMAND command2 [ARGS] [args2...] ...]
                   [BYPRODUCTS [files...]]
                   [WORKING_DIRECTORY dir]
                   [COMMENT comment]
                   [VERBATIM]
                   [COMMAND_EXPAND_LISTS])
```

This defines a new command that will be associated with building the specified ```<target>```. The ```<target>``` must be defined in the current directory; targets defined in other directories may not be specified.

```TARGET <target>```: Specifies the name of the target to which the custom command will be attached. This can be any target defined in your CMake project, such as an executable or library.

```PRE_BUILD | PRE_LINK | POST_BUILD```: Indicates at which stage of the target's build process the custom command should be executed:

```PRE_BUILD```: Executes the command before the build step of the target.

```PRE_LINK```: Executes the command before the linking step of the target.

```POST_BUILD```: Executes the command after the target has been built.

```COMMAND command1 [ARGS] [args1...]```: Specifies the command to be executed and its arguments. You can include multiple ```COMMAND``` entries if you want to execute a sequence of commands. The ARGS keyword is optional and can be used to make the command arguments clearer but is not necessary.

```BYPRODUCTS [files...]```: Lists any additional files that are produced by the custom command. These byproducts are not the main outputs but are still generated as a result of running the command. This helps CMake understand the side effects of the command.

```WORKING_DIRECTORY dir```: Sets the working directory in which the command should be executed. If not specified, the working directory will be the build directory.

```COMMENT comment```: Provides a comment or message that will be displayed when the command runs. This is useful for giving additional context or information in the build output.

```VERBATIM```: Ensures that the command and its arguments are passed exactly as specified, without any modification or interpretation by CMake. This is important for ensuring that special characters and spaces in arguments are handled correctly.

```COMMAND_EXPAND_LISTS```: Expands lists in command arguments. When specified, if any argument is a list, it will be expanded into individual arguments rather than being treated as a single argument.

### install

The ```install``` command is used to specify how files, directories, executables, libraries, and other build outputs should be installed to a specified directory on the system.

The ```install``` command has various forms to handle different types of installations.

```
install(TARGETS targets... [options...])
install(FILES files... [options...])
install(DIRECTORY directories... [options...])
install(SCRIPT script)
install(CODE code)
```

**Install Targets**

Install executables, libraries, or modules.

```
install(TARGETS target1 [target2 ...]
        [EXPORT <export-name>]
        [RUNTIME|LIBRARY|ARCHIVE|FRAMEWORK|BUNDLE|PRIVATE_HEADER|PUBLIC_HEADER|RESOURCE]
        [DESTINATION <dir>]
        [PERMISSIONS permissions...]
        [CONFIGURATIONS [Debug|Release|...]]
        [COMPONENT <component>]
        [NAMELINK_ONLY|NAMELINK_SKIP]
        [EXCLUDE_FROM_ALL]
        [OPTIONAL])
```

**Install Files**

Install individual files.

```
install(FILES file1 [file2 ...]
        DESTINATION <dir>
        [PERMISSIONS permissions...]
        [CONFIGURATIONS [Debug|Release|...]]
        [COMPONENT <component>]
        [RENAME <name>]
        [OPTIONAL])
```

**Install Directory**

Install a directory sub-tree of headers.

```
install(DIRECTORY dir1 [dir2 ...]
        DESTINATION <dir>
        [FILE_PERMISSIONS permissions...]
        [DIRECTORY_PERMISSIONS permissions...]
        [USE_SOURCE_PERMISSIONS]
        [FILES_MATCHING]
        [PATTERN <pattern> [REGEX] [EXCLUDE]]
        [CONFIGURATIONS [Debug|Release|...]]
        [COMPONENT <component>])
```

**Install Script**

Invoke CMake script during installation process.

```
install(SCRIPT <script-file>)
```

**Install Code**

Invoke CMake code during installation process.

```
install(CODE <code>)
```

### enable_testing and add_test

The ```enable_testing``` command is used to enable testing capabilities within a CMake project. It is essential for integrated testing frameworks like CTest, allows us the define and run tests as part of the build process. It is often used in conjuction with ```add_test``` command to create a complete test setup.

```
add_test(NAME <test_name> COMMAND <command> [args...])
```

```<test_name>```: The name assigned to the test. This name is used to reference the test in CTest and other CMake commands.

```<command>```: The command to run the test. This typically includes the path to an executable or script, followed by any necessary arguments.

For example:

```
cmake_minimum_required(VERSION 3.10)

project(HelloWorld VERSION 1.0.0 DESCRIPTION "Print HelloWorld on Console" LANGUAGES C CXX)

add_executable(HelloWorld main.cpp)

enable_testing()
add_test(NAME HelloWorldTest COMMAND HelloWorld --test)
set_tests_properties(HelloWorldTest PROPERTIES TIMEOUT 10)
```

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/01_HelloWorld$ mkdir build
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/01_HelloWorld$ cd build/
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/01_HelloWorld/build$ cmake ..
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/01_HelloWorld/build$ make
[ 50%] Building CXX object CMakeFiles/HelloWorld.dir/main.cpp.o
[100%] Linking CXX executable HelloWorld
[100%] Built target HelloWorld
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/01_HelloWorld/build$ ./HelloWorld 
Hello World
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/01_HelloWorld/build$ ctest
Test project /home/ncmv/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/01_HelloWorld/build
    Start 1: HelloWorldTest
1/1 Test #1: HelloWorldTest ...................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.00 sec
```

### option

The ```option``` command is used to define configurable options for a CMake project. These options can be enabled or disabled by user when configuring the project, providing a way to control build features or settings.

```
option(<option_variable> "description" [initial_value])
```

```<option_variable>```: The name of the variable to define.

```"description"```: A brief description of what the option does.

```[initial_value]```: The initial value of the option, which can be ON or OFF. If not specified, it defaults to OFF.

For example:

```
cmake_minimum_required(VERSION 3.10)
project(SampleProject)

option(ENABLE_MULTITHREADING "Allow to use multithreading features" ON)

add_executable(SampleProgram main.cpp)

if(ENABLE_MULTITHREADING)
    message(STATUS "Multithreading is enabled.")
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag("-std=c++11" HAS_CXX11_FLAG)

    if(HAS_CXX11_FLAG)
        target_compile_options(SampleProgram PRIVATE -std=c++11)
        find_package(Threads REQUIRED)
        target_link_libraries(SampleProgram PRIVATE Threads::Threads)
    else()
        message(STATUS "Compiler does not support C++11 Threads.")
    endif()
else()
    message(STATUS "Multithreading is disabled.")
endif()
```

### conditional statements

The ```if...elseif...else...endif``` statements are used to control the flow of CMakeLists.txt script based on conditions.

```
if(condition)
    # Commands to execute if condition is true
elseif(condition2)
    # Commands to execute if condition2 is true
else()
    # Commands to execute if all conditions are false
endif()
```

CMake supports a variety of conditions that can be used in conditional statements.

**Boolean values**

For example:

```
if(FEATURE_X_AVAILABLE)
    message(STATUS "FEATURE_X_AVAILABLE variable is set to TRUE/ON")
endif()
```

**Comparison operators**

```Equality```: STREQUAL, EQUAL

```Inequality```: STRNOTEQUAL, NOTEQUAL

```Greater/Less```: GREATER, LESS, GREATER_EQUAL, LESS_EQUAL

For example:

```
if(CXX_COMPILE_TOOL STREQUAL "g++")
    message(STATUS "Compile source files using g++")
endif()
```

**Logical operators**

```AND```: Logical AND

```OR```: Logical OR

```NOT```: Logical NOT

For example:

```
if(USE_NO_OPTIMAL_OPTIONS and CONTINUE_WITH_WARNING)
    message(STATUS "Accept build warning")
endif()
```

**Existing checks**

```DEFINED```: Checks if a variable is defined

For example:

```
if(DEFINED SAMPLE_VAR)
    message(STATUS "SAMPLE_VAR variable is defined")
endif()
```

**File checks**

```EXISTS```: Checks if a file or directory exists

```IS_DIRECTORY```: Checks if a path is a directory

```IS_SYMLINK```: Checks if a path is a symbolic link

```
if(EXISTS "/usr/bin/cmake")
    message(STATUS "Found CMake tool")
endif()
```

### while

### foreach

### break

### continue

### function and endfunction

### block and endblock

### return

### find commands

**find_file**

**find_library**

**find_package**

**find_path**

**find_program**

### export

### try_compile

### try_run

### Configuring Build Types

Typical values of built-in build types include:

```Release```: high optimization level, no debug info, code or asserts. ```-O3 -DNDEBUG```

```Debug```: No optimization, asserts enabled, [custom debug (output) code enabled], debug info included in executable (so you can step through the code with a debugger and have address to source-file:line-number translation). ```-O0 -g```

```RelWithDebInfo```: optimized, with debug info, but no debug (output) code or asserts. ```-O2 -g -DNDEBUG```

```MinSizeRel```: same as Release but optimizing for size rather than speed. ```-Os -DNDEBUG```

```
set(CMAKE_BUILD_TYPE Debug)

or

set(CMAKE_BUILD_TYPE Release)
```

or

```
mkdir Debug
cd Debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
make

or

mkdir Release
cd Release
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

# Conclusion

CMake is a versatile and powerful tool for managing the build process of software projects. By understanding its basic and advanced features, we can efficiently handle dependencies, organize your project, and troubleshoot common issues.

To truly understand CMake, it's essential to practice and build a sample project on your own. This hands-on experience will help you grasp the concepts better and become more proficient in using CMake for your projects.

[https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/CMake/SampleProjects/03_LocationService](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/CMake/SampleProjects/03_LocationService)

I encourage you to take up the challenge and try building the sample project before seeking the solution.

[https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/blob/master/CMake/SampleProjects/03_LocationService/CMakeLists.txt](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/blob/master/CMake/SampleProjects/03_LocationService/CMakeLists.txt)

----

**References**

[https://cmake.org/cmake/help/latest/guide/tutorial/index.html](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)

[https://blog.feabhas.com/2021/07/cmake-part-1-the-dark-arts/](https://blog.feabhas.com/2021/07/cmake-part-1-the-dark-arts/)

[https://blog.feabhas.com/2021/07/cmake-part-2-release-and-debug-builds/](https://blog.feabhas.com/2021/07/cmake-part-2-release-and-debug-builds/)

[https://blog.feabhas.com/2021/08/cmake-part-3-source-file-organisation/?fbclid=IwAR094ep-_EYNix0WLa60D2OlRrDGEAjFn3kK740mw4b98i2GfR9VsUY35is](https://blog.feabhas.com/2021/08/cmake-part-3-source-file-organisation/?fbclid=IwAR094ep-_EYNix0WLa60D2OlRrDGEAjFn3kK740mw4b98i2GfR9VsUY35is)