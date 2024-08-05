## Introduction

### What Is CMake?

CMake is a cross-platform tool designed to manage the build process of software projects. It uses simple configuration files called CMakeLists.txt to generate native build scripts for various platforms, such as Makefiles for Unix or project files for Visual Studio.

### Benefits Of Using CMake

Cross-Platform: Works on Windows, macOS, and Linux.
Flexibility: Can generate build files for different build systems.
Modularity: Easy to manage complex projects with multiple components.
Community Support: Widely used and well-documented.

### CMake Installation

To install CMake on a Linux system, you can use your package manager. For example, on Ubuntu, you can run:

```
sudo apt-get update
sudo apt-get install cmake
```

Verify the installation by running:

```
cmake --version
```

## Build HelloWorld Project

Create a directory for your project:

```
mkdir HelloWorld
cd HelloWorld
```

Create a simple C++ source file:

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