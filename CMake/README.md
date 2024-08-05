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

### Basic Syntax And Structure

A CMakeLists.txt file typically starts with specifying the minimum required version of CMake and the project name:

```
cmake_minimum_required(VERSION 3.10)
project(MyProject)
```

### Common Commands

add_executable: Defines an executable target.

```
add_executable(MyExecutable main.cpp)
```

add_library: Defines a library target.

```
add_library(MyLibrary mylib.cpp)
```

target_link_libraries: Links libraries to targets.

```
target_link_libraries(MyExecutable MyLibrary)
```

### Variables And Cache Variables

Setting variables:

```
set(MY_VAR "Hello")
```

Using variables:

```
message(${MY_VAR})
```

Cache variables (persist between runs):

```
set(MY_CACHE_VAR "World" CACHE STRING "A cached variable")
```

## Hanlding Dependencies

### Finding And Using Libraries

Using find_package:

```
find_package(SomeLibrary REQUIRED)
target_link_libraries(MyExecutable SomeLibrary::SomeLibrary)
```

### Download Dependencies

Using FetchContent:

```
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.10.0
)
FetchContent_MakeAvailable(googletest)
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