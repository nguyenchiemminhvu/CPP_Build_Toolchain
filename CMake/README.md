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

**Community Support**: Widely used and well-documented.

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

A CMakeLists.txt file typically starts with specifying the minimum required version of CMake and the project name:

```
cmake_minimum_required(VERSION 3.10)
project(MyProject)
```

## Advanced Features

### Custom Commands And Targets

Adding custom commands:

```
add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/generated_file.cpp
    COMMAND ${CMAKE_COMMAND} -E echo "Generating file"
    COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_BINARY_DIR}/generated_file.cpp
)
add_custom_target(generate DEPENDS ${CMAKE_BINARY_DIR}/generated_file.cpp)
```

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