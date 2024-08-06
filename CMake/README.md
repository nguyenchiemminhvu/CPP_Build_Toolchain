## Introduction

### What Is CMake?

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

### Benefits Of Using CMake

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

## Build HelloWorld Project

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

## CMakeLists.txt Syntax And Commands

### General Outline Of CMakeLists.txt

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

### Basic Syntax And Structure

#### cmake_minimum_required

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

#### project

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

#### set variables

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

#### include_directories

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
include_directories(${CMAKE_SOURCE_DIR}/include)
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

#### add_executable



#### add_library



#### target_link_libraries



#### add_subdirectory



### Practice the basic

#### Build jsoncpp lib

[]()

#### Build source and lib in sub directories

[]()

### Advanced Features

#### add_custom_command

Adding custom commands:

```
add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/generated_file.cpp
    COMMAND ${CMAKE_COMMAND} -E echo "Generating file"
    COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_BINARY_DIR}/generated_file.cpp
)
add_custom_target(generate DEPENDS ${CMAKE_BINARY_DIR}/generated_file.cpp)
```

#### install

#### enable_testing

#### add_test

#### option

### Configuring Build Types

Setting build types:

```
set(CMAKE_BUILD_TYPE Debug)
```

## Best Pratices

### Organizing CMake Projects

Directory structure:

```
MyProject/
├── CMakeLists.txt
├── src/
│   └── main.cpp
└── include/
    └── myheader.h
```

### Writing Maintainable CMakeLists.txt Files

Modularize with subdirectories:

```
add_subdirectory(src)
add_subdirectory(include)
```

### Common Pitfall And How To Avoid

Avoid hardcoding paths: Use variables like ${CMAKE_SOURCE_DIR} and ${CMAKE_BINARY_DIR}.

Use modern CMake practices: Prefer target_* commands over global settings.

## Debugging And Troubleshooting

### Common Errors

Missing files: Ensure all source files are listed in CMakeLists.txt.

Library not found: Check if the library is installed and paths are correctly set.

### CMake Debugging Tools And Options

Verbose output:

```
cmake --trace ..
```

Check variable values:

```
message("MY_VAR is ${MY_VAR}")
```

## Conclusion

CMake is a versatile and powerful tool for managing the build process of software projects. By understanding its basic and advanced features, you can efficiently handle dependencies, organize your project, and troubleshoot common issues.

**References**

[https://cmake.org/cmake/help/latest/guide/tutorial/index.html](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)

[https://blog.feabhas.com/2021/07/cmake-part-1-the-dark-arts/](https://blog.feabhas.com/2021/07/cmake-part-1-the-dark-arts/)

[https://blog.feabhas.com/2021/07/cmake-part-2-release-and-debug-builds/](https://blog.feabhas.com/2021/07/cmake-part-2-release-and-debug-builds/)

[https://blog.feabhas.com/2021/08/cmake-part-3-source-file-organisation/?fbclid=IwAR094ep-_EYNix0WLa60D2OlRrDGEAjFn3kK740mw4b98i2GfR9VsUY35is](https://blog.feabhas.com/2021/08/cmake-part-3-source-file-organisation/?fbclid=IwAR094ep-_EYNix0WLa60D2OlRrDGEAjFn3kK740mw4b98i2GfR9VsUY35is)