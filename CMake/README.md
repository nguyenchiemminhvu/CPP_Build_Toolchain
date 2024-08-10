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

## CMake Installation

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

# CMake Basic Syntax And Commands

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

## Basic Syntax And Commands

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

```<target>```: The name of the target to which we want to add compiler options.

```BEFORE (optional)```: If specified, the options will be added before any options that are added by CMake or other commands. This can be useful if we need to ensure that your options take precedence.

```<INTERFACE|PUBLIC|PRIVATE>```: Specifies the scope of the options.

```INTERFACE```: The options are used by targets that link to this target, but not by the target itself.

```PUBLIC```: The options are used by both the target itself and by targets that link to this target.

```PRIVATE```: The options are used only by the target itself.

```[items1...]```: The actual compiler options we want to add.

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

```<target>```: The name of the target to which we want to add linker options.

```BEFORE (optional)```: If specified, the options will be added before any options that are added by CMake or other commands. This can be useful if we need to ensure that your options take precedence.

```<INTERFACE|PUBLIC|PRIVATE>```: Specifies the scope of the options.

```INTERFACE```: The options are used by targets that link to this target, but not by the target itself.

```PUBLIC```: The options are used by both the target itself and by targets that link to this target.

```PRIVATE```: The options are used only by the target itself.

```[items1...]```: The actual linker options we want to add.

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

```-D<definition>```: This specifies a preprocessor definition. The -D flag is followed by the definition we want to add. We can add multiple definitions by separating them with spaces.

For example:

```
add_definitions(-DDEBUG -DVERSION=2 -DUSE_CHINA_SHIFT_SHARED_OBJ)
```

### target_compile_definitions

In order to add definitions for just a specific target, use ```target_compile_definitions``` command instead, which provides more control and recommended approach in modern CMake.

```
target_compile_definitions(<target> [<INTERFACE|PUBLIC|PRIVATE>] [items1...])
```

```<target>```: The name of the target to which we want to add the preprocessor definitions.

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

### add_dependencies

The ```add_dependencies``` command is used to add dependencies between top-level targets. This ensures that a target is built only after its dependencies have been built. It is useful when we have custom targets or when we need to enforce a specific build order.

```
add_dependencies(<target> [<dependency>...])
```

```<target>```: The name of the target that we want to add dependencies to.

```<dependency>```: One or more names of targets that ```<target>``` depends on.

For example:

```
add_custom_target(targetA
    COMMAND ${CMAKE_COMMAND} -E echo "Building targetA"
)

add_custom_target(targetB
    COMMAND ${CMAKE_COMMAND} -E echo "Building targetB"
)

add_custom_target(targetC
    COMMAND ${CMAKE_COMMAND} -E echo "Building targetC"
)

add_dependencies(targetC targetA targetB)
```

### add_subdirectory

The ```add_subdirectory``` command is used to add sub-directories to the build, allow us to include another CMakeLists.txt file from a sub-directory, which can define additional targets, libraries, and other build-related settings. It is useful for organizing large projects into smaller components.

```
add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL])
```

```source_dir```: The relative or absolute path to the source directory containing the CMakeLists.txt file we want to include.

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

# CMake Concepts

## CMake Build System in general

CMake build system manages a set of high-level logical targets. A build target could be an executable file, a library, or a custom target.

Executable file is program that we can run/execute. Declare an executable target by ```add_executable``` command.

Library is a collection of reusable code to be used be programs. Declare a library target by ```add_library``` command.

Custom target is special task or script to be executed during build process. Declare a custom target by ```add_custom_target``` and ```add_custom_command``` commands.

CMake build system defines how these targets are related to each other. This helps determine the order in which they should be built, ensure that everything is ready when needed. By managing the dependent relationship between targets, CMake also know which parts need to be rebuilt.

## CMake Advance Syntax And Commands

### include

The ```include``` command is used to load and execute another CMake script file. It is useful for reusing common CMake code across multiple CMake projects or organizing CMake code into more manageable pieces.

```
include(<file> [OPTIONAL] [RESULT_VARIABLE <var>] [NO_POLICY_SCOPE])
```

```<file>```: The path to the CMake script file we want to include. This can be a relative or absolute path. If the path is relative, it is interpreted relative to the current source directory.

```OPTIONAL```: If this keyword is specified, CMake will not produce an error if the file does not exist. Without this keyword, CMake will generate an error if the file is not found.

```RESULT_VARIABLE``` : If RESULT_VARIABLE is given the variable ```<var>``` will be set to the full filename which has been included or ```NOTFOUND``` if it failed.

```NO_POLICY_SCOPE```: If this keyword is specified, the policies set in the included file will not affect the including scope. This can be useful to avoid policy warnings or errors when including files that might set policies.

For example:

```
project/
├── CMakeLists.txt
├── cmake/
│   └── common.cmake
└── src/
    └── main.cpp
```

**cmake/common.cmake**
```
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
```

**top-level CMakeLists.txt**
```
cmake_minimum_required(VERSION 3.10)
project(SampleProject)

include(cmake/common.cmake)

add_executable(MyProject src/main.cpp)
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

The ```while``` command is used to create loops that execute a block of code repeatedly as long as the specified condition is true.

```
while(<condition>)
    <commands>
endwhile()
```

```condition```: A boolean expression that is evaluated before each iteration of the loop. If the condition evaluates to true, the loop body is executed. If it evaluates to false, the loop terminates.

For example:

```
cmake_minimum_required(VERSION 3.10)
project(SampleLoop)

set(providers "ublox;novatel;topcon;qualcomm")
list(LENGTH providers num_provider)
set(index 0)

while(index LESS num_provider)
    list(GET providers ${index} provider)
    add_subdirectory(${provider})
    math(EXPR index "${index} + 1")
endwhile()
```

### foreach

The ```foreach``` command is used to iterate over a list of items, performing a set of commands for each item in the list.

```
foreach(<loop_var> <items>)
  <commands>
endforeach()
```

```<loop_var>```: At the beginning of each iteration the variable ```<loop_var>``` will be set to the value of the current item.

```<items>```: is a list of items that are separated by semicolon or whitespace.

```<commands>```: The commands to execute for each item in the list.

Common patterns of ```foreach``` in CMake:

```
foreach(<loop_var> RANGE <stop>)
    # iterates over the numbers 0, 1, ... up to (and including) the nonnegative integer <stop>.
endforeach()

foreach(<loop_var> RANGE <start> <stop> [<step>])
    # iterates over the numbers from <start> up to at most <stop> in steps of <step>. If <step> is not specified, then the step size is 1.
endforeach()

foreach(<loop_var> IN [LISTS [<lists>]] [ITEMS [<items>]])
    # <lists> is a whitespace or semicolon separated list of list-valued variables.
endforeach()
```

For example:

**top-level feature.cmake script**
```
option(FeatureA "Feature A is enabled" ON)
option(FeatureB "Feature B is enabled" OFF)
option(FeatureC "Feature C is enabled" ON)
```

**top-level CMakeLists.txt**
```
cmake_minimum_required(VERSION 3.10)
project(SampleLoop)

include("features.cmake")

set(FEATURES "FeatureA" "FeatureB" "FeatureC")

foreach(FEATURE IN LISTS FEATURES)
    if(${FEATURE})
        message(STATUS "${FEATURE}")
    endif()
endforeach()
```

**CMake processing result**
```
worker@7e4a84e41875:~/study_workspace/CPP_Build_Toolchain/CMake/temp/build$ cmake ..
-- FeatureA
-- FeatureC
-- Configuring done
-- Generating done
```

### break

The ```break``` command is used to exit from a loop (```foreach``` or ```while```) early.

```
break()
```

For example:

```
cmake_minimum_required(VERSION 3.10)
project(SampleLoop)

include("features.cmake")

set(FEATURES "FeatureA" "FeatureB" "FeatureC")

foreach(FEATURE IN LISTS FEATURES)
    if(${FEATURE})
        message(STATUS "${FEATURE}")
    else()
        break()
    endif()
endforeach()
```

### continue

The ```continue``` command is used to skip the remaining commands in the current iteration of a loop and proceed the next iteration.

```
continue()
```

For example:

```
cmake_minimum_required(VERSION 3.10)
project(SampleLoop)

include("features.cmake")

set(FEATURES "FeatureA" "FeatureB" "FeatureC")

foreach(FEATURE IN LISTS FEATURES)
    if(${FEATURE})
        message(STATUS "${FEATURE}")
    else()
        continue()
    endif()
endforeach()
```

### function

The ```function``` command is used to define a reusable block of CMake code that can be called with different arguments. It is useful for organizing and modularizing CMake scripts.

```
function(<name> [<arg1> ... <argN>])
    # Commands
endfunction()
```

```<name>```: The name of the function.

```<arg1> ... <argN>```: Optional arguments that the function can accept.

Function in CMake is case-insensitive. A function defined as:

```
function(foo)
    <commands>
endfunction()
```

can be invoked via any of:

```
foo()
Foo()
FOO()
cmake_language(CALL foo)
```

However, it is strongly recommended to treat functions as case-sensitive.

For example:

```
cmake_minimum_required(VERSION 3.10)
project(SampleFunction)

function(print_message arg)
    message(STATUS "Message: ${arg}")
endfunction()

function(enable_feature feature)
    print_message("Enable ${feature} feature")
    option(${feature} "" ON)
endfunction()

function(disable_feature feature)
    print_message("Disable ${feature} feature")
    option(${feature} "" OFF)
endfunction()


enable_feature(CHINA_SHIFT)
enable_feature(ECALL)
enable_feature(DEAD_RECKONING)

disable_feature(TIME_SYNC)
disable_feature(DIAGNOSTICS)
```

### string

The ```string``` command is used to perform various operations on strings.

**General syntax**

```
string(<SUBCOMMAND> <ARGUMENTS>)
```

**Common use subcommands**

```
string(REGEX MATCH <regular_expression>
       <output variable> <input> [<input>...])
```
Matches a string against a regular expression and stores the first match in the output variable.

```
string(REGEX MATCHALL <regular_expression>
       <output variable> <input> [<input>...])
```
Matches all occurrences of a regular expression in a string and stores them in the output variable as a list.

```
string(REGEX REPLACE <regular_expression>
       <replace_expression> <output variable>
       <input> [<input>...])
```
Replaces occurrences of a regular expression in a string with a replacement expression.

```
string(REPLACE <match_string>
       <replace_string> <output variable>
       <input> [<input>...])
```
Replaces occurrences of a substring in a string with another substring.

```
string(CONCAT <output variable> [<input>...])
```
Concatenates multiple strings into a single string.

```
string(COMPARE EQUAL <string1> <string2> <output variable>)
```
Compares two strings for equality.

```
string(LENGTH <string> <output variable>)
```
Gets the length of a string.

```
string(FIND <string> <substring> <output variable> [REVERSE])
```
Finds a substring within a string and returns the position.

For example:

```
string(REGEX MATCH "Hello" MATCH_RESULT "Hello World")
message(STATUS "Matched string: ${MATCH_RESULT}")
```

```
string(REGEX MATCHALL "o" MATCH_RESULT "Hello World")
message(STATUS "Matched string: ${MATCH_RESULT}")
```

```
string(REPLACE "World" "CMake" REPLACE_RESULT "Hello World")
message(STATUS "New string: ${REPLACE_RESULT}")
```

```
string(REGEX REPLACE "W.*" "CMake" REPLACE_RESULT "Hello World")
message(STATUS "New string: ${REPLACE_RESULT}")
```

```
string(LENGTH "Hello CMake" LENGTH_RESULT)
message(STATUS "${LENGTH_RESULT}")
```

### list

The ```list``` command is used to manimulate lists. Lists in CMake are semcolon-separated strings.

**General syntax:**

```
list(SUBCOMMAND <list> [<args>...])
```

**Subcommands:**

```
list(LENGTH <list> <output variable>)
```
Gets the number of elements in a list and stores it in the specified output variable.

```
list(GET <list> <element index> [<element index> ...]
     <output variable>)
```
Retrieves elements from a list at specified indices and stores them in the specified output variable(s).

```
list(APPEND <list> [<element> ...])
```
Appends elements to the end of a list.

```
list(FIND <list> <value> <output variable>)
```
Finds the index of the first occurrence of an element in a list and stores it in the specified output variable. If the element is not found, the output variable is set to -1.

```
list(INSERT <list> <element_index> <element> [<element> ...])
```
Inserts elements into a list at a specified position.

```
list(REMOVE_ITEM <list> <value> [<value> ...])
```
Removes all occurrences of specified elements from a list.

```
list(REMOVE_AT <list> <index> [<index> ...])
```
Removes elements from a list at specified indices.

```
list(REMOVE_DUPLICATES <list>)
```
Removes duplicate elements from a list.

```
list(REVERSE <list>)
```
Reverses the order of elements in a list.

```
list(SORT <list>)
```
Sorts the elements of a list in ascending order by default.

For example:

```
set(LIST_LIBRARIES "jsoncpp" "xml" "database" "util" "math" "database")

list(REMOVE_DUPLICATES LIST_LIBRARIES)
list(REMOVE LIST_LIBRARIES "database")
list(LENGTH LIST_LIBRARIES NUM_LIBS)
list(GET LIST_LIBRARIES 0 FIRST_LIB)
```

### file

The ```file``` command is dedicated to file and path manipulation (read, write, copy, remove,...) requiring access to filesystem. Here are the different modes and their description:

**READ**

```
file(READ <filename> <variable> [OFFSET <offset>] [LIMIT <max-in>] [HEX])
```

Read content from a file called ```<filename>``` and store it in a ```<variable>```. Optionally start from the given ```<offset>``` and read at most ```<max-in>``` bytes. The ```HEX``` option causes data to be converted to a hexadecimal representation (useful for binary data).

```
file(STRINGS <filename> <variable> <options>...)
```

Parse a list of ASCII strings from ```<filename>``` and store it in ```<variable>```.

For example:

build_configs.txt
```
FEATURE_A=ON
FEATURE_B=OFF
FEATURE_C=ON
```

top-level CMakeLists.txt
```
file(READ "build_configs.txt" build_configs)
message(STATUS "${build_configs}")

file(STRINGS "build_configs.txt" build_configs)
message(STATUS "${build_configs}")
```

CMake processing result
```
worker@7e4a84e41875:~/study_workspace/CPP_Build_Toolchain/CMake/temp/build$ cmake ..
-- FEATURE_A=ON
FEATURE_B=OFF
FEATURE_C=ON
-- FEATURE_A=ON;FEATURE_B=OFF;FEATURE_C=ON
-- Configuring done
-- Generating done

```

**WRITE**

```
file(WRITE <filename> <content>...)
or
file(APPEND <filename> <content>...)
```

Write ```<content>``` into a file called ```<filename>```. If the file does not exist, it will be created. If the file already exists, ```WRITE``` mode will overwrite it and ```APPEND``` mode will append to the end.

For example:

```
cmake_minimum_required(VERSION 3.10)
project(SampleFile)

file(READ "build_configs.txt" build_configs)
message(STATUS "${build_configs}")

file(WRITE "${CMAKE_BINARY_DIR}/build_configs.txt" ${build_configs})
```

**RENAME**

```
file(RENAME <oldname> <newname> [RESULT <result>] [NO_REPLACE])
```

Move a file or directory within a filesystem from ```<oldname>``` to ```<newname>```, replacing the destination atomically.

For example:

```
file(RENAME "${CMAKE_BINARY_DIR}/build_configs.txt" "${CMAKE_BINARY_DIR}/build_configs_temp.txt")
```

**COPY**

```
file(COPY file1 [file2 ...] DESTINATION destination [FOLLOW_SYMLINK_CHAIN] [NO_SOURCE_PERMISSIONS] [USE_SOURCE_PERMISSIONS] [FILES_FROM_DIR directory])
```

Copies files to a destination.

For example:

```
file(COPY "source.txt" DESTINATION "${CMAKE_BINARY_DIR}/source.txt")
```

**DOWNLOAD**

```
file(DOWNLOAD url file [TIMEOUT timeout] [STATUS status] [LOG log] [SHOW_PROGRESS])
```

```TIMEOUT```: Set a timeout for the download.

```STATUS```: Variable to store the status of the download.

```LOG```: Variable to store the log of the download.

```SHOW_PROGRESS```: Show download progress.

Downloads a file from a URL.

For example:

```
file(DOWNLOAD
    http://graphics.stanford.edu/pub/3Dscanrep/bunny.tar.gz
    ${CMAKE_BINARY_DIR}/bunny.tar.gz
    SHOW_PROGRESS
)
```

**UPLOAD**

```
file(UPLOAD file url [TIMEOUT timeout] [STATUS status] [LOG log] [SHOW_PROGRESS])
```

```TIMEOUT```: Set a timeout for the upload.

```STATUS```: Variable to store the status of the upload.

```LOG```: Variable to store the log of the upload.

```SHOW_PROGRESS```: Show upload progress.

Uploads a file to a URL.

For example:

```
file(UPLOAD
    ${CMAKE_BINARY_DIR}/bunny.tar.gz
    http://graphics.stanford.edu/pub/3Dscanrep/
    SHOW_PROGRESS
)
```

**REMOVE**

```
file(REMOVE file1 [file2 ...])
or
file(REMOVE_RECURSE dir1 [dir2 ...])
```

Removes files or directories and their contents recursively.

For example:

```
file(REMOVE "example.txt")
```

**GLOB**

```
file(GLOB <variable> [LIST_DIRECTORIES true|false] [RELATIVE <path>] [CONFIGURE_DEPENDS] <globbing-expressions>...)

or

file(GLOB_RECURSE <variable> [FOLLOW_SYMLINKS] [LIST_DIRECTORIES true|false] [RELATIVE <path>] [CONFIGURE_DEPENDS] <globbing-expressions>...)
```

```<variable>```: The name of the variable where the results (i.e., paths to files or directories) will be stored.

```LIST_DIRECTORIES true|false```: ```true```: Includes directories in the search results. ```false```: Excludes directories and includes only files. This is the default behavior.

```RELATIVE```: If specified, the paths returned in the result will be relative to the provided ```<path>``` instead of being absolute paths.

```CONFIGURE_DEPENDS```: If specified, the list of files or directories will be re-evaluated at build time whenever the content of the searched directories changes.

```<globbing-expressions>```: The patterns used to match files or directories. These can include wildcards like *.cpp, *.h, etc. Multiple patterns can be provided.

Creates a list of files that match the globbing expressions, searching directories recursively.

For example:

```
cmake_minimum_required(VERSION 3.10)
project(SampleFile)

file(GLOB txt_files "*.txt")
foreach(txt_file ${txt_files})
    message(STATUS "Found text file: ${txt_file}")
endforeach()
```

```
worker@7e4a84e41875:~/study_workspace/CPP_Build_Toolchain/CMake/temp/build$ cmake ..
-- Found text file: /home/worker/study_workspace/CPP_Build_Toolchain/CMake/temp/CMakeLists.txt
-- Found text file: /home/worker/study_workspace/CPP_Build_Toolchain/CMake/temp/build_configs.txt
-- Configuring done
-- Generating done
```

Example to add all buildable sub-directories:

```
cmake_minimum_required(VERSION 3.10)
project(SampleFile)

file(GLOB subdirlist *)
foreach(subdir ${subdirlist})
    if (IS_DIRECTORY ${subdir} AND EXISTS ${subdir}/CMakeLists.txt)
        add_subdirectory(${subdir})
    endif()
endforeach()
```

### find commands

**find_file**

The ```find_file``` command is used to locate a file in a set of directories. It searches for a file with a specified name or pattern, and if found, it stores the full path to that file in a variable.

```
find_file(
  <VAR>
  name1 [name2 ...]
  [HINTS path1 [path2 ... ENV var]]
  [PATHS path1 [path2 ... ENV var]]
  [PATH_SUFFIXES suffix1 [suffix2 ...]]
  [DOC "cache documentation string"]
  [NO_DEFAULT_PATH]
  [NO_CMAKE_ENVIRONMENT_PATH]
  [NO_CMAKE_PATH]
  [NO_SYSTEM_ENVIRONMENT_PATH]
  [NO_CMAKE_SYSTEM_PATH]
  [CMAKE_FIND_ROOT_PATH_BOTH |
   ONLY_CMAKE_FIND_ROOT_PATH |
   NO_CMAKE_FIND_ROOT_PATH]
  [REQUIRED]
  [NO_CACHE]
)
```

```<VAR>```: The variable that stores the result. If the file is found, this variable is set to the full path; otherwise, it's set to NOTFOUND.

```name1 [name2 ...]```: The names of the files to search for.

```HINTS path1 [path2 ...] or PATHS path1 [path2 ...]```: Additional paths to be considered during the search.

```PATH_SUFFIXES suffix1 [suffix2 ...]```: Suffixes to append to each path during the search.

```DOC "cache documentation string"```: Documentation string for the cache entry.

```NO_DEFAULT_PATH```: Do not use default paths when searching.

```NO_CMAKE_ENVIRONMENT_PATH```: Do not search paths from the ```CMAKE_PREFIX_PATH``` environment variable.

```NO_CMAKE_PATH```: Skip the default CMake paths.

```NO_SYSTEM_ENVIRONMENT_PATH```: Do not search paths from the PATH environment variable.

```NO_CMAKE_SYSTEM_PATH```: Skip system paths.

```CMAKE_FIND_ROOT_PATH_BOTH | ONLY_CMAKE_FIND_ROOT_PATH | NO_CMAKE_FIND_ROOT_PATH```: Control whether the ```CMAKE_FIND_ROOT_PATH``` is used.

```REQUIRED```: If the file is not found, stop processing with an error.

```NO_CACHE```: The result will not be stored in the cache.

For example:

```
find_file(HEADER_PATH
    common.h
    PATHS ${CMAKE_CURRENT_SOURCE_DIR}
    PATH_SUFFIXES .h
    DOC "Path to header files"
)

message(STATUS "${HEADER_PATH}")
```

The search process for the find_file command in CMake follows a specific order, which is influenced by the options and paths provided.

```CMAKE_PREFIX_PATH```: Paths specified in the CMAKE_PREFIX_PATH environment variable.

```CMAKE_FRAMEWORK_PATH```: Paths for framework directories on macOS.

```CMAKE_APPBUNDLE_PATH```: Paths for application bundles on macOS.

```Paths specified with the PATHS option```: Custom paths defined by the user.

```Paths specified with the HINTS option```: Additional hints for the search.

```System Environment Paths```: Paths from the system's environment variables.

```CMake Variables```: Variables like ```CMAKE_SYSTEM_PREFIX_PATH```.

```CMAKE_FIND_ROOT_PATH```: Prefixed search paths if enabled.

```NO_DEFAULT_PATH```: Ignores all default paths and uses only those provided explicitly.

```NO_CMAKE_ENVIRONMENT_PATH```: Skips paths specified in ```CMAKE_PREFIX_PATH```.

```NO_CMAKE_PATH```: Ignores default CMake paths.

```NO_SYSTEM_ENVIRONMENT_PATH```: Skips paths from the system's environment variables.

```NO_CMAKE_SYSTEM_PATH```: Ignores system paths known to CMake.

```CMAKE_FIND_ROOT_PATH_MODE_PROGRAM```: Controls the behavior of ```CMAKE_FIND_ROOT_PATH```.

**find_path**

The ```find_path``` is used to locate a directory containing a named file.

```
find_path(<VAR> name1 [path1 path2 ...]
          [PATHS path1 path2 ... | HINTS path1 path2 ...]
          [REQUIRED]
          [NO_DEFAULT_PATH]
          [NO_CMAKE_ENVIRONMENT_PATH]
          [NO_CMAKE_PATH]
          [NO_SYSTEM_ENVIRONMENT_PATH]
          [NO_CMAKE_SYSTEM_PATH]
          [CMAKE_FIND_ROOT_PATH_BOTH | ONLY_CMAKE_FIND_ROOT_PATH | NO_CMAKE_FIND_ROOT_PATH]
          [DOC "cache documentation string"]
          [NO_PACKAGE_ROOT_PATH]
          [NO_CMAKE_PACKAGE_REGISTRY]
          [NO_CMAKE_BUILDS_PATH]
          [NO_CMAKE_SYSTEM_PACKAGE_REGISTRY]
          [NO_CMAKE_SYSTEM_BUILDS_PATH]
          [NAMES_PER_DIR]
          [NAMES name1 [name2 ...]]
          [PATH_SUFFIXES suffix1 [suffix2 ...]]
          [DOC "cache documentation string"]
          [CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY | NEVER | BOTH]
)
```

```<VAR>```: The variable that will store the path to the directory containing the specified file if found.

```name1```: The name of the file to search for.

```path1, path2, ...```: Optional paths to search in addition to the default paths.

```PATHS```: Specifies additional paths to search.

```HINTS```: Specifies additional paths to search, but with lower priority than PATHS.

```REQUIRED```: If the path is not found, an error will be reported.

```NO_DEFAULT_PATH```: Do not search in the default paths.

```NO_CMAKE_ENVIRONMENT_PATH```: Do not search the paths specified in the CMAKE_PREFIX_PATH environment variable.

```NO_CMAKE_PATH```: Do not search the paths specified in the CMAKE_PREFIX_PATH variable.

```NO_SYSTEM_ENVIRONMENT_PATH```: Do not search the system environment paths.

```NO_CMAKE_SYSTEM_PATH```: Do not search the system paths specified by CMake.

```CMAKE_FIND_ROOT_PATH_BOTH```: Search both the root path and the non-root path.

```ONLY_CMAKE_FIND_ROOT_PATH```: Search only the root path.

```NO_CMAKE_FIND_ROOT_PATH```: Do not search the root path.

```DOC```: Documentation string for the cache entry.

```NO_PACKAGE_ROOT_PATH```: Do not search the package root path.

```NO_CMAKE_PACKAGE_REGISTRY```: Do not search the CMake package registry.

```NO_CMAKE_BUILDS_PATH```: Do not search the CMake builds path.

```NO_CMAKE_SYSTEM_PACKAGE_REGISTRY```: Do not search the system package registry.

```NO_CMAKE_SYSTEM_BUILDS_PATH```: Do not search the system builds path.

```NAMES_PER_DIR```: Search for each name in each directory.

```NAMES```: Specifies additional names to search for.

```PATH_SUFFIXES```: Specifies suffixes to append to each search path.

```CMAKE_FIND_ROOT_PATH_MODE_INCLUDE```: Specifies how to handle the root path mode for includes.

For example:

```
file(GLOB_RECURSE HEADER_SUB_DIRS LIST_DIRECTORIES true /usr/include/* /usr/local/include/*)

find_file(HEADER_PATH
    iostream
    PATHS ${HEADER_SUB_DIRS}
    DOC "Path to header file iostream"
)

message(STATUS "${HEADER_PATH}")
```
```
worker@7e4a84e41875:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/temp/build$ cmake ..
-- /usr/include/c++/7/iostream
-- Configuring done
-- Generating done
```

**find_library**

The ```find_library``` is used to locate a library file on the file system.

```
find_library(
  <VAR>
  name1 [name2 ...]
  PATHS path1 [path2 ... ]
  [PATH_SUFFIXES suffix1 [suffix2 ...]]
  [DOC "cache documentation string"]
  [NO_DEFAULT_PATH]
  [NO_CMAKE_ENVIRONMENT_PATH]
  [NO_CMAKE_PATH]
  [NO_SYSTEM_ENVIRONMENT_PATH]
  [NO_CMAKE_SYSTEM_PATH]
  [CMAKE_FIND_ROOT_PATH_BOTH |
   ONLY_CMAKE_FIND_ROOT_PATH |
   NO_CMAKE_FIND_ROOT_PATH]
  [REQUIRED]
  [NO_CACHE]
)
```

```<VAR>```: The variable that stores the result. If the library is found, this variable is set to the full path; otherwise, it’s set to NOTFOUND.

```name1 [name2 ...]```: The names of the libraries to search for.

```PATHS path1 [path2 ...]```: Additional paths to be considered during the search.

```PATH_SUFFIXES suffix1 [suffix2 ...]```: Suffixes to append to each path during the search.

```DOC "cache documentation string"```: Documentation string for the cache entry.

```NO_DEFAULT_PATH```: Do not use default paths when searching.

```NO_CMAKE_ENVIRONMENT_PATH```: Do not search paths from the ```CMAKE_PREFIX_PATH``` environment variable.

```NO_CMAKE_PATH```: Skip the default CMake paths.

```NO_SYSTEM_ENVIRONMENT_PATH```: Do not search paths from the LIB environment variable.

```NO_CMAKE_SYSTEM_PATH```: Skip system paths.

```CMAKE_FIND_ROOT_PATH_BOTH | ONLY_CMAKE_FIND_ROOT_PATH | NO_CMAKE_FIND_ROOT_PATH```: Control whether the ```CMAKE_FIND_ROOT_PATH``` is used.

```REQUIRED```: If the library is not found, stop processing with an error.

```NO_CACHE```: The result will not be stored in the cache.

For example:

```
file(GLOB_RECURSE CURRENT_BIN_SUB_DIRS LIST_DIRECTORIES true ${CMAKE_CURRENT_BINARY_DIR}/*)

find_library(JSONCPP_LIB_PATH
    NAMES jsoncpp
    PATHS ${CURRENT_BIN_SUB_DIRS}
)

message(STATUS "Found ${JSONCPP_LIB_PATH}")
```

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/02_BuildSubDirs/build$ cmake ..
-- Found /home/ncmv/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/02_BuildSubDirs/build/opensource/libjsoncpp.so
-- Configuring done (0.0s)
-- Generating done (0.0s)
```

**find_program**

The ```find_program``` is used to locate an executable program on the system.

```
find_program(<VAR> name1 [path1 path2 ...]
             [HINTS path1 [path2 ...]]
             [PATHS path1 [path2 ...]]
             [PATH_SUFFIXES suffix1 [suffix2 ...]]
             [DOC "cache documentation string"]
             [NO_DEFAULT_PATH]
             [NO_CMAKE_ENVIRONMENT_PATH]
             [NO_CMAKE_PATH]
             [NO_SYSTEM_ENVIRONMENT_PATH]
             [NO_CMAKE_SYSTEM_PATH]
             [CMAKE_FIND_ROOT_PATH_BOTH |
              ONLY_CMAKE_FIND_ROOT_PATH |
              NO_CMAKE_FIND_ROOT_PATH])
```

```<VAR>```: The variable that will store the result of the search. If the program is found, this variable will contain the full path to the executable. If not found, it will be set to NOTFOUND.

```name1```: The name of the program we are looking for. We can specify multiple names to search for alternative programs.

```path1, path2, ...```: Optional paths where CMake should look for the program.

```HINTS```: Additional paths to search before the standard system paths.

```PATHS```: Additional paths to search after the standard system paths.

```PATH_SUFFIXES```: Suffixes to append to each search path.

```DOC```: A documentation string for the cache entry.

```NO_DEFAULT_PATH```: Do not search in the default paths.

```NO_CMAKE_ENVIRONMENT_PATH```: Do not search the paths specified in the CMAKE_PREFIX_PATH environment variable.

```NO_CMAKE_PATH```: Do not search the paths specified in the CMAKE_PREFIX_PATH CMake variable.

```NO_SYSTEM_ENVIRONMENT_PATH```: Do not search the system environment paths (e.g., PATH on Windows).

```NO_CMAKE_SYSTEM_PATH```: Do not search the system paths specified by CMake.

```CMAKE_FIND_ROOT_PATH_BOTH, ONLY_CMAKE_FIND_ROOT_PATH, NO_CMAKE_FIND_ROOT_PATH```: Control how the CMAKE_FIND_ROOT_PATH variable is used.

For example:

```
find_program(GIT_EXE git
    PATHS /usr/bin/ /usr/local/bin /opt/local/bin
)

if(GIT_EXE)
    message(STATUS "Found ${GIT_EXE}")
endif()
```
```
worker@7e4a84e41875:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/temp/build$ cmake ..
-- Found /usr/bin/git
-- Configuring done
-- Generating done
```

**find_package**

Find details in [CMake Packages](#cmake-packages) concept.

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

By default, nothing depends on the custom target.

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

```COMMAND```: Specifies the command to be executed. It is possible to provide multiple commands, each with its own set of arguments. The ARGS keyword is optional and can be used to specify arguments for the command.

```MAIN_DEPENDENCY```: Specifies the main dependency file. This is useful for cases where the custom command generates an output file from a single input file.

```DEPENDS```: Lists additional files or targets that the custom command depends on. These dependencies ensure that the custom command is executed only after the specified dependencies are up-to-date.

```BYPRODUCTS```: Specifies files that are produced as side effects of the custom command. These files are not the primary outputs but are still important for the build process.

```IMPLICIT_DEPENDS```: Specifies implicit dependencies for the custom command. This is useful for languages that have implicit dependencies, such as C++ header files.

```WORKING_DIRECTORY```: Specifies the working directory in which the command will be executed.

```COMMENT```: Provides a comment that will be displayed when the custom command is executed. This can be useful for providing context or information to the user.

```DEPFILE```: Specifies a dependency file that lists additional dependencies for the custom command. This is often used with compilers that generate dependency files.

```JOB_POOL```: Specifies a job pool for the custom command. This can be used to control the concurrency of custom commands.

```VERBATIM```: Ensures that the command and its arguments are passed to the shell exactly as specified. This is important for commands that require precise argument formatting.

```APPEND```: Appends the custom command to the existing commands for the specified output files. This allows us to add multiple custom commands for the same output.

```USES_TERMINAL```: Indicates that the custom command uses a terminal for its execution. This is useful for commands that require user interaction or produce output that should be visible to the user.

```COMMAND_EXPAND_LISTS```: Expands lists in the command arguments. This is useful for commands that take a variable number of arguments.

When the target that depends on these output files is built, CMake will automatically execute the custom command to generate the output files if they are out of date or missing.

For example:

**top-level CMakeLists.txt**
```
cmake_minimum_required(VERSION 3.10)
project(SampleCommand)

set(ENABLED_FEATURES
    CHINA_SHIFT
    DEAD_RECKONING
    EMERGENCY_CALL
    TIME_SYNC
)

string(REPLACE ";" "," ENABLED_FEATURES_STR "${ENABLED_FEATURES}")

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/generated.h
    COMMAND ${CMAKE_COMMAND} -DENABLED_FEATURES_STR=${ENABLED_FEATURES_STR} -P ${CMAKE_CURRENT_SOURCE_DIR}/generate.cmake
    BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/generated.h
)

add_custom_target(generate_features
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/generated.h
)

add_custom_target(all_targets ALL)
add_dependencies(all_targets generate_features)
```

**generate.cmake script**
```
if(DEFINED ENABLED_FEATURES_STR)
    string(REPLACE "," ";" ENABLED_FEATURES "${ENABLED_FEATURES_STR}")
    string(CONCAT GENERATED_CONTENT "#ifndef GENERATED_H\n#define GENERATED_H\n\n")

    foreach(FEATURE ${ENABLED_FEATURES})
        string(APPEND GENERATED_CONTENT "#define ${FEATURE}\n\n")
    endforeach()

    string(APPEND GENERATED_CONTENT "#endif\n")

    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/generated.h" ${GENERATED_CONTENT})
endif()
```

**Result:**
```
worker@7e4a84e41875:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/temp/build$ cmake ..
-- Configuring done
-- Generating done
-- Build files have been written to: /home/worker/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/temp/build

worker@7e4a84e41875:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/temp/build$ make
[100%] Built target generate_features
[100%] Built target all_targets

worker@7e4a84e41875:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/temp/build$ cat generated.h
#ifndef GENERATED_H
#define GENERATED_H

#define CHINA_SHIFT

#define DEAD_RECKONING

#define EMERGENCY_CALL

#define TIME_SYNC

#endif
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

```COMMAND command1 [ARGS] [args1...]```: Specifies the command to be executed and its arguments. We can include multiple ```COMMAND``` entries if we want to execute a sequence of commands. The ARGS keyword is optional and can be used to make the command arguments clearer but is not necessary.

```BYPRODUCTS [files...]```: Lists any additional files that are produced by the custom command. These byproducts are not the main outputs but are still generated as a result of running the command. This helps CMake understand the side effects of the command.

```WORKING_DIRECTORY dir```: Sets the working directory in which the command should be executed. If not specified, the working directory will be the build directory.

```COMMENT comment```: Provides a comment or message that will be displayed when the command runs. This is useful for giving additional context or information in the build output.

```VERBATIM```: Ensures that the command and its arguments are passed exactly as specified, without any modification or interpretation by CMake. This is important for ensuring that special characters and spaces in arguments are handled correctly.

```COMMAND_EXPAND_LISTS```: Expands lists in command arguments. When specified, if any argument is a list, it will be expanded into individual arguments rather than being treated as a single argument.

For example:

**top-level CMakeLists.txt**
```
cmake_minimum_required(VERSION 3.10)
project(SampleCommand)

add_library(sample_lib SHARED util.cpp)

set(LIB_VERSION "0.0.0")

add_custom_command(
    TARGET sample_lib
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:sample_lib> $<TARGET_FILE_DIR:sample_lib>/libsample_lib.so.${LIB_VERSION}
    COMMAND ${CMAKE_COMMAND} -E create_symlink libsample_lib.so.${LIB_VERSION} $<TARGET_FILE_DIR:sample_lib>/libsample_lib.so
    COMMAND ${CMAKE_COMMAND} -E echo "sample_lib build is finished"
    VERBATIM
)
```

**Build result:**
```
worker@7e4a84e41875:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/temp/build$ cmake ..
-- Configuring done
-- Generating done
-- Build files have been written to: /home/worker/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/temp/build

worker@7e4a84e41875:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/temp/build$ make
Scanning dependencies of target sample_lib
[ 50%] Building CXX object CMakeFiles/sample_lib.dir/util.cpp.o
[100%] Linking CXX shared library libsample_lib.so
sample_lib build is finished
[100%] Built target sample_lib

worker@7e4a84e41875:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/temp/build$ ll
total 48
drwxr-xr-x 3 worker worker  4096 Aug  8 16:35 ./
drwxrwxr-x 3 worker worker  4096 Aug  8 16:29 ../
lrwxrwxrwx 1 worker worker    22 Aug  8 16:35 libsample_lib.so -> libsample_lib.so.0.0.0*
-rwxr-xr-x 1 worker worker  7440 Aug  8 16:35 libsample_lib.so.0.0.0*
```

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

The variants of ```install``` command have some common options:

```DESTINATION```: Specifies the directory within the install prefix where the files should be installed.

```PERMISSIONS```: Sets the permissions for the installed files like OWNER_READ, OWNER_WRITE, OWNER_EXECUTE, GROUP_READ, GROUP_WRITE, GROUP_EXECUTE, WORLD_READ, WORLD_WRITE, and WORLD_EXECUTE.

```CONFIGURATIONS```: Specifies a list of build configurations for which the install rule applies. Common configurations include Debug, Release, RelWithDebInfo, and MinSizeRel.

```COMPONENT```: Assigns the install rule to a specific component, which can be used to group files for installation.

```RENAME```: Specifies a new name for the installed file.

```OPTIONAL```: Indicates that the installation of the file is optional. If the file does not exist, CMake will not generate an error.

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

```TARGETS target1 [target2 ...]```: Specifies the targets to be installed. You can list multiple targets separated by spaces.

```EXPORT``` : This option is used to export the targets to a CMake package configuration file. The ```<export-name>``` is the name of the export set.

```RUNTIME|LIBRARY|ARCHIVE|FRAMEWORK|BUNDLE|PRIVATE_HEADER|PUBLIC_HEADER|RESOURCE```: These options specify the type of target being installed:

```RUNTIME```: For executables and DLLs.

```LIBRARY```: For shared libraries.

```ARCHIVE```: For static libraries.

```FRAMEWORK```: For macOS frameworks.

```BUNDLE```: For macOS application bundles.

```PRIVATE_HEADER```: For private headers.

```PUBLIC_HEADER```: For public headers.

```RESOURCE```: For resource files.

```NAMELINK_ONLY|NAMELINK_SKIP```: These options are used for shared libraries:

```NAMELINK_ONLY```: Installs only the symlink to the shared library.

```NAMELINK_SKIP```: Skips the installation of the symlink.

```EXCLUDE_FROM_ALL```: Excludes the target from the default installation set. This means the target will not be installed unless explicitly specified.

For example:

```
add_library(util SHARED util.cpp)

install(
    TARGETS util
    LIBRARY DESTINATION lib
    PRIVATE_HEADER
)
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

```FILES file1 [file2 ...]```: Specifies the files to be installed. It is possible to list multiple files separated by spaces.

For example:

```
install(
    FILES config.txt readme.md
    DESTINATION share/docs
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
    CONFIGURATIONS Release
    COMPONENT documentation
    OPTIONAL
)
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
```

```DIRECTORY dir1 [dir2 ...]```: Specifies the directories to be installed. You can list multiple directories separated by spaces.

```FILES_MATCHING```: Installs only files that match the specified patterns.

```PATTERN [REGEX] [EXCLUDE]```: Specifies a pattern to match files or directories. The REGEX option treats the pattern as a regular expression. The EXCLUDE option excludes files or directories that match the pattern.

For example:

```
add_executable(Dummy src/main.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

install(
    DIRECTORY include/
    DESTINATION include
    FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
    DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    FILES_MATCHING
    PATTERN "*.h"
)
```
```
worker@7e4a84e41875:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/temp/build$ sudo make install
[100%] Built target Dummy
Install the project...
-- Install configuration: ""
-- Up-to-date: /usr/local/include
-- Installing: /usr/local/include/util.h
```

**Install Script**

Invoke CMake script during installation process.

```
install(SCRIPT <script-file>)
```

```SCRIPT```: Specifies the path to the CMake script file that should be executed during the installation process. The path can be relative to the source or build directory, or it can be an absolute path.

For example:

```
cmake_minimum_required(VERSION 3.10)
project(SampleInstall)

install(SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/sample.cmake)
```
```
worker@7e4a84e41875:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/temp/build$ make install
Install the project...
-- Install configuration: ""
-- Hello from sample.cmake
```

**Install Code**

Invoke CMake code during installation process.

```
install(CODE <code>)
```

```CODE```: Specifies the CMake code to be executed during the installation process. The code should be a string containing valid CMake commands.

For example:

```
install(CODE
    "
    file(UPLOAD
        ${CMAKE_BINARY_DIR}/example.txt
        http://example.com/
        TIMEOUT 3
        STATUS upload_status
        SHOW_PROGRESS
    )
    
    message(STATUS \"Upload status: \${upload_status}\")
    "
)
```
```
worker@7e4a84e41875:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/temp/build$ make install
Install the project...
-- Install configuration: ""
-- Upload status: 28;"Timeout was reached"
```

**Export targets**

Export targets for use by other projects.

```
install(EXPORT <export-name> DESTINATION <dir>
        [NAMESPACE <namespace>] [FILE <name>.cmake]
        [PERMISSIONS permissions...]
        [CONFIGURATIONS [Debug|Release|...]]
        [EXPORT_LINK_INTERFACE_LIBRARIES]
        [COMPONENT <component>])
```

```EXPORT```: Specifies the name of the export set. This name is used to refer to the set of targets being exported.

```NAMESPACE```: Specifies a namespace to be prepended to the target names when they are imported. This helps to avoid name conflicts.

```FILE .cmake```: Specifies the name of the CMake package configuration file that will be generated. If not specified, the default name is ```<export-name>.cmake```.

```EXPORT_LINK_INTERFACE_LIBRARIES```: Exports the link interface libraries of the targets. This is useful if the targets have dependencies that need to be included when they are imported.

For example:

**Build libutil.so and export to SampleUtilTargetConfig package**
```
add_library(util SHARED util.cpp)

install(
    TARGETS util
    EXPORT SampleUtilTarget
    LIBRARY DESTINATION lib
)

install(
    EXPORT SampleUtilTarget
    DESTINATION share/SampleUtilTarget
    NAMESPACE Util::
    FILE SampleUtilTargetConfig.cmake
)
```
```
worker@7e4a84e41875:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/temp/build$ sudo make install
[100%] Built target util
Install the project...
-- Install configuration: ""
-- Up-to-date: /usr/local/lib/libutil.so
-- Installing: /usr/local/share/SampleUtilTarget/SampleUtilTargetConfig.cmake
-- Installing: /usr/local/share/SampleUtilTarget/SampleUtilTargetConfig-noconfig.cmake
```

**Build an executable linked with libutil.so from exported package**
```
add_executable(UtilUsage main.cpp)

find_package(SampleUtilTarget REQUIRED PATHS /usr/local/share/SampleUtilTarget)
target_link_libraries(UtilUsage Util::util)
```
```
worker@7e4a84e41875:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/temp/build$ make
[ 50%] Linking CXX executable UtilUsage
[100%] Built target UtilUsage
```

Refer to [CMake Packages](#cmake-packages) for more details.

### export

The ```export``` command is used to create and manage export files that describe the build targets in a project during build process. These export files can then be used by other projects.

**Export targets to a file**

```
export(TARGETS target1 target2 ... FILE <filename>)
```

```TARGETS```: Specifies the targets to be exported.

```FILE```: Specifies the file to which the targets will be exported.

**Export targets to a package**

```
export(EXPORT <export-name> FILE <filename> NAMESPACE <namespace> ...)
```

```EXPORT```: Specifies the name of the export set.

```FILE```: Specifies the file to which the export set will be written.

```NAMESPACE```: Specifies a namespace to be prepended to the target names when they are imported.

**Export targets for installation**

```
install(EXPORT <export-name> DESTINATION <dir> FILE <filename> NAMESPACE <namespace> ...)
```

```EXPORT```: Specifies the name of the export set.

```DESTINATION```: Specifies the directory where the export file will be installed.

```FILE```: Specifies the name of the export file.

```NAMESPACE```: Specifies a namespace to be prepended to the target names when they are imported.

For example:

**Export package SampleUtilTarget at CMake processing stage**
```
add_library(util SHARED util.cpp)

export(TARGETS util FILE SampleUtilTargetConfig.cmake)

install(
    TARGETS util
    EXPORT SampleUtilTarget
    LIBRARY DESTINATION lib
)

install(
    EXPORT SampleUtilTarget
    FILE SampleUtilTargetConfig.cmake
    DESTINATION lib/cmake/SampleUtilTarget
)
```
```
worker@7e4a84e41875:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/temp/build$ cmake ..
-- Configuring done
-- Generating done
-- Build files have been written to: /home/worker/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/temp/build

worker@7e4a84e41875:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/temp/build$ ll
drwxr-xr-x 3 worker worker  4096 Aug  8 19:03 ./
drwxrwxr-x 3 worker worker  4096 Aug  8 18:50 ../
-rw-r--r-- 1 worker worker  2051 Aug  8 19:03 SampleUtilTargetConfig.cmake

worker@7e4a84e41875:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/temp/build$ sudo make install
[100%] Built target util
Install the project...
-- Install configuration: ""
-- Up-to-date: /usr/local/lib/libutil.so
-- Up-to-date: /usr/local/lib/cmake/SampleUtilTarget/SampleUtilTargetConfig.cmake
-- Installing: /usr/local/lib/cmake/SampleUtilTarget/SampleUtilTargetConfig-noconfig.cmake
```

### try_compile

The ```try_compile``` command is used to test if a small piece of code can be compiled. It is useful for checking if certain features, functions, or libraries are available on the system.

```
try_compile(
    <result_variable>
    <binary_dir>
    <source_dir|source_file>
    [CMAKE_FLAGS <flags>...]
    [COMPILE_DEFINITIONS <compile_definitions>...]
    [LINK_LIBRARIES <libraries>...]
    [OUTPUT_VARIABLE <output_variable>]
    [COPY_FILE <copy_file>]
    [COPY_FILE_ERROR <copy_file_error>]
)
```

```result_variable```: The name of the variable that will store the result of the compilation test. It will be set to TRUE if the compilation succeeds and FALSE otherwise.

```binary_dir```: The directory where the test project will be built. This should be a unique directory to avoid conflicts with other tests.

```source_dir|source_file```: The source directory or file to be compiled. If a directory is specified, it should contain a CMakeLists.txt file. If a file is specified, it should be a single source file.

```CMAKE_FLAGS```: Additional flags to pass to the CMake configuration step. This can include definitions, options, and other CMake variables.

```COMPILE_DEFINITIONS```: Preprocessor definitions to be used during the compilation.

```LINK_LIBRARIES```: Libraries to link against during the compilation.

```OUTPUT_VARIABLE```: A variable to store the output of the compilation process.

```COPY_FILE```: A file to copy if the compilation succeeds.

```COPY_FILE_ERROR```: A variable to store any error that occurs while copying the file specified in ```COPY_FILE```.

For example:

```
set(TEMP_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/test_lambda")

file(WRITE 
    "${TEMP_BINARY_DIR}/test.cpp"
    "
    #include <iostream>
    int main()
    {
        auto f = [](){ std::cout << \"Hello World\" << std::endl; };
        f();
        return 0;
    }
    "
)

try_compile(
    COMPILE_RESULT
    ${TEMP_BINARY_DIR}
    ${TEMP_BINARY_DIR}/test.cpp
    CMAKE_FLAGS -DCMAKE_CXX_STANDARD=11
)

if(COMPILE_RESULT)
    message(STATUS "C++11 Lambda feature is compiled successfully")
else()
    message(STATUS "C++11 Lambda feature is not available")
endif()
```

### try_run

The ```try_run``` command is used to compile and run a small piece of code to test if certain features, functions, or libraries are available and working correctly on the system.

```
try_run(
    <run_result_variable>
    <compile_result_variable>
    <binary_dir>
    <source_dir|source_file>
    [CMAKE_FLAGS <flags>...]
    [COMPILE_DEFINITIONS <compile_definitions>...]
    [LINK_LIBRARIES <libraries>...]
    [OUTPUT_VARIABLE <output_variable>]
    [COPY_FILE <copy_file>]
    [COPY_FILE_ERROR <copy_file_error>]
    [RUN_OUTPUT_VARIABLE <run_output_variable>]
    [ARGS <args>...]
    [WORKING_DIRECTORY <dir>]
    [LINK_OPTIONS <options>...]
    [LINK_DIRECTORIES <directories>...]
    [LINK_OPTIONS_BEFORE <options>...]
    [LINK_DIRECTORIES_BEFORE <directories>...]
)
```

```run_result_variable```: The name of the variable that will store the result of running the compiled executable. It will be set to the return code of the executable.

```compile_result_variable```: The name of the variable that will store the result of the compilation test. It will be set to TRUE if the compilation succeeds and FALSE otherwise.

```binary_dir```: The directory where the test project will be built. This should be a unique directory to avoid conflicts with other tests.

```source_dir|source_file```: The source directory or file to be compiled. If a directory is specified, it should contain a CMakeLists.txt file. If a file is specified, it should be a single source file.

```CMAKE_FLAGS```: Additional flags to pass to the CMake configuration step. This can include definitions, options, and other CMake variables.

```COMPILE_DEFINITIONS```: Preprocessor definitions to be used during the compilation.

```LINK_LIBRARIES```: Libraries to link against during the compilation.

```OUTPUT_VARIABLE```: A variable to store the output of the compilation process.

```COPY_FILE```: A file to copy if the compilation succeeds.

```COPY_FILE_ERROR```: A variable to store any error that occurs while copying the file specified in COPY_FILE.

```RUN_OUTPUT_VARIABLE```: A variable to store the output of the executable when it is run.

```ARGS```: Arguments to pass to the executable when it is run.

```WORKING_DIRECTORY```: The working directory to use when running the executable.

```LINK_OPTIONS```: Options to be used during the linking process.

```LINK_DIRECTORIES```: Directories to search for libraries during the linking process.

```LINK_OPTIONS_BEFORE```: Options to be used before the linking process.

```LINK_DIRECTORIES_BEFORE```: Directories to search for libraries before the linking process.

For example:

```
set(TEMP_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/test_lambda")

file(WRITE 
    "${TEMP_BINARY_DIR}/test.cpp"
    "
    #include <iostream>
    int main()
    {
        auto f = [](){ std::cout << \"Hello World\" << std::endl; };
        f();
        return 0;
    }
    "
)

try_run(
    RUN_RESULT
    COMPILE_RESULT
    ${TEMP_BINARY_DIR}
    ${TEMP_BINARY_DIR}/test.cpp
    CMAKE_FLAGS -DCMAKE_CXX_STANDARD=11
    RUN_OUTPUT_VARIABLE RUN_OUTPUT
)

if(COMPILE_RESULT)
    message(STATUS "C++11 Lambda feature is compiled successfully")
    if(RUN_RESULT EQUAL 0)
        message(STATUS "C++11 Lambda feature is run successfully")
        message(STATUS "${RUN_OUTPUT}")
    else()
        message(STATUS "${RUN_RESULT}")
    endif()
else()
    message(STATUS "C++11 Lambda feature is not available")
endif()
```

### execute_process

The ```execute_process``` command is used to execute one or more child process during the configuration phase of CMake project.

```
execute_process(COMMAND <cmd1> [<args1>...]
                [COMMAND <cmd2> [<args2>...] ...]
                [WORKING_DIRECTORY <directory>]
                [TIMEOUT <seconds>]
                [RESULT_VARIABLE <variable>]
                [RESULTS_VARIABLE <variable>]
                [OUTPUT_VARIABLE <variable>]
                [ERROR_VARIABLE <variable>]
                [OUTPUT_QUIET]
                [ERROR_QUIET]
                [OUTPUT_STRIP_TRAILING_WHITESPACE]
                [ERROR_STRIP_TRAILING_WHITESPACE]
                [ENCODING <name>])
```

```COMMAND [...]```: Specifies the command to execute and its arguments. We can specify multiple commands to be executed in sequence.

```WORKING_DIRECTORY``` : Sets the working directory for the command. If not specified, the current source directory is used.

```TIMEOUT``` : Specifies a timeout for the command execution. If the command does not complete within the given time, it will be terminated.

```RESULT_VARIABLE``` : Stores the result of the command execution (e.g., the return code) in the specified variable.

```RESULTS_VARIABLE``` : Stores the results of all commands executed in sequence in the specified variable.

```OUTPUT_VARIABLE``` : Captures the standard output of the command and stores it in the specified variable.

```ERROR_VARIABLE``` : Captures the standard error output of the command and stores it in the specified variable.

```OUTPUT_QUIET```: Suppresses the standard output of the command.

```ERROR_QUIET```: Suppresses the standard error output of the command.

```OUTPUT_STRIP_TRAILING_WHITESPACE```: Strips trailing whitespace from the captured standard output.

```ERROR_STRIP_TRAILING_WHITESPACE```: Strips trailing whitespace from the captured standard error output.

```ENCODING``` : Specifies the encoding of the output and error variables. This is useful for handling non-ASCII characters.

For example:

```
message(STATUS "Generate a child process to check current local git status")

execute_process(
    COMMAND git status
    OUTPUT_VARIABLE echo_output
    RESULT_VARIABLE echo_result
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE
)

message(STATUS "OUTPUT: ${echo_output}")
message(STATUS "RESULT: ${echo_result}")

execute_process(
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_SOURCE_DIR}/sample.cmake
    OUTPUT_VARIABLE echo_output
    RESULT_VARIABLE echo_result
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

message(STATUS "OUTPUT: ${echo_output}")
message(STATUS "RESULT: ${echo_result}")
```

### Configuring Build Types

Typical values of built-in build types include:

```Release```: high optimization level, no debug info, code or asserts. ```-O3 -DNDEBUG```

```Debug```: No optimization, asserts enabled, [custom debug (output) code enabled], debug info included in executable (so we can step through the code with a debugger and have address to source-file:line-number translation). ```-O0 -g```

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

## CMake Variables

In this topic, I wanted to list out the common use CMake built-in variables, classified based on their scope and purposes just as mentioned in [CMake documentation page](https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html).

### Variables that Provide Information

These variables give information about the CMake environment and the project:

```CMAKE_COMMAND```: Holds the full path to the CMake executable that is currently being run.

```CMAKE_C_COMPILER```: Path to the C compiler.

```CMAKE_CXX_COMPILER```: Path to the C++ compiler.

```CMAKE_SOURCE_DIR```: Top-level directory of the source tree.

```CMAKE_BINARY_DIR```: Top-level directory of the build tree.

```CMAKE_CURRENT_SOURCE_DIR```: Current source directory being processed.

```CMAKE_CURRENT_BINARY_DIR```: Current binary directory being processed.

```CMAKE_CURRENT_LIST_DIR```: Holds the full directory path of the listfile (CMake script) currently being processed.

```CMAKE_CURRENT_LIST_FILE```: Holds the full path to the listfile (CMake script) that is currently being processed.

```CMAKE_FIND_PACKAGE_NAME```: Holds the name of the package currently being searched for by the ```find_package()``` command.

### Variables that Change Behavior

These variables affect how CMake processes and builds the project:

```CMAKE_BUILD_TYPE```: Specifies the build type (e.g., Debug, Release).

```BUILD_SHARED_LIBS```: Tell add_library() to default to SHARED libraries, instead of STATIC libraries, when called with no explicit library type.

```CMAKE_VERBOSE_MAKEFILE```: If ON, makefiles show all commands during build.

```CMAKE_COLOR_DIAGNOSTICS```: Controls whether compiler and linker diagnostics (such as warnings and errors) are displayed with color in the terminal.

```CMAKE_MODULE_PATH```: specifies a list of directories where CMake will search for additional CMake modules and scripts. Refer to [CMake Modules](#cmake-modules) for more details.

### Variables that Describe the System

These variables provide information about the system and environment:

```CMAKE_SYSTEM_NAME```: Name of the operating system.

```CMAKE_HOST_SYSTEM_NAME```: Name of the host operating system.

```CMAKE_SYSTEM_PROCESSOR```: Processor type (e.g., x86_64).

```CMAKE_SYSROOT```: Specifies the sysroot to be used during the build process. A sysroot is a directory that serves as the root filesystem for cross-compilation. It typically contains the header files, libraries, and other resources needed for compiling code for a different target platform than the host.

### Variables that Control the Build

These variables are used to control various build aspects:

```CMAKE_INSTALL_PREFIX```: Installation directory for the project. The default value is typically ```/usr/local``` on Unix-like systems.

```CMAKE_CXX_FLAGS```: Flags for the C++ compiler.

## CMake Modules

### What is a CMake module?

A CMake module is typically a file that contains CMake scipts which can be included and used in CMakeLists.txt files. It stores the encapsulate reusable code such as finding libraries, setting up build configurations, or defining custom commands and macros. Modules in CMake are usually stored in files with ```.cmake``` extension.

### How CMake manage modules?

CMake manages modules through a set of predefined directories where it looks for module files.

A CMake module can be located by using the full path to the module file, or let CMake find the module by itself. The search order could typically be:

- CMake module path specified by the CMAKE_MODULE_PATH variable.
- CMake installation directory
- Current source and binary directories.

### Commonly used prebuilt CMake modules

CMake modules can be categorized into several types based on their functionality and purpose.

**Find modules** are used to locate header files, or libraries that belongs to a package. Each module comes with documentation describing the package it finds and the variables in which it provides results.

For example: FindOpenGL.cmake, FindPython.cmake, FindZLIB.cmake, FindCURL.cmake, FindGTest.cmake, ...

**Utility modules** provide general-purpose helper functions, macros, and commands that can be reused across different projects. Some of them have prefix ```Test``` or ```Check``` testing the system to provide information about target platform and compiler. Some of them try to compile code in order to determine if feature is available...

For example: CheckLibraryExists.cmake, CheckSymbolExists.cmake, GNUInstallDirs.cmake, CMakeParseArguments.cmake, ...

```
cmake --help-module <ModuleName>
```

### How to use prebuilt CMake modules?

To use a prebuilt CMake module, we can use  ```include``` command.

For example:

```
cmake_minimum_required(VERSION 3.10)
project(SampleModule)

include(CheckSymbolExists)
include(CheckCXXSymbolExists)

set(CMAKE_REQUIRED_LIBRARIES "pthread")
set(CMAKE_REQUIRED_INCLUDES "iostream")

check_symbol_exists(fopen "stdio.h" HAVE_FOPEN)
message(STATUS "${HAVE_FOPEN}")

check_symbol_exists(pthread_create "pthread.h" HAVE_PTHREAD_CREATE)
message(STATUS "${HAVE_PTHREAD_CREATE}")

check_cxx_symbol_exists("std::cout" "iostream" HAVE_COUT)
message(STATUS "${HAVE_COUT}")
```

### How to build a custom CMake module?

The example below shows you how to build your own CMake module.

Firstly, create and organize a project structure, create a ```.cmake``` file.

```
project/
├── CMakeLists.txt
├── cmake/
│   └── MyCustomModule.cmake
└── src/
```

Define a custom function or macro in ```.cmake``` file.

```
function(LOGI msg)
    message(STATUS "${msg}")
endfunction()

function(LOGE msg)
    message(FATAL_ERROR "${msg}")
endfunction()
```

Now it is able to use custom module in the current CMake project.

```
cmake_minimum_required(VERSION 3.10)
project(SampleModule)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(MyCustomModule)

LOGI("Information message")
```

Set up the installation to the custom module.

```
cmake_minimum_required(VERSION 3.10)
project(SampleModule)

install(
    FILES ${CMAKE_SOURCE_DIR}/cmake/MyCustomModule.cmake
    DESTINATION share/cmake/custom_modules
)
```
```
worker@7e4a84e41875:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/temp/build$ sudo make install
Install the project...
-- Install configuration: ""
-- Installing: /usr/local/share/cmake/custom_modules/MyCustomModule.cmake
```

Use it in other CMake project.

```
cmake_minimum_required(VERSION 3.10)
project(SampleModule)

list(APPEND CMAKE_MODULE_PATH "/usr/local/share/cmake/custom_modules")

include(MyCustomModule)

LOGI("Information message")
```
```
worker@7e4a84e41875:~/study_workspace/CPP_Build_Toolchain/CMake/SampleProjects/temp/build$ cmake ..
-- Information message
-- Configuring done
-- Generating done
```

## CMake Packages

CMake packages are a way to encapsulate a library or a set of related libraries into a distributable unit. They contain the necessary information to locate and use the library in other CMake projects. This includes paths to header files, libraries, and any required compile options or definitions.

There are 2 primary types of CMake package: ```Config-file Packages``` and ```Find-module Packages```.

### Config-file Packages

```<PackageName>Config.cmake```: This file is provided by the package itself and includes commands that configure the package for use in the importing project. It usually sets up variables, paths, and other necessary configuration.

Config package can include a version file ```<PackageName>ConfigVersion.cmake``` that let users know the specific version of the package.

**Usage:**

When a library is installed, it can place the ```<PackageName>Config.cmake``` file and optional ```<PackageName>ConfigVersion.cmake``` file in the standard location. These files are then used by the ```find_package``` command to locate the library.

The standard location for installing Config packages is typically ```lib/cmake/<PackageName>```.

For example: If a library named ```GnssUtil``` is installed with an installation prefix ```/usr/local```, the config package is typically installed in ```/usr/local/lib/cmake/GnssUtil/```.

The installation path can be customized by using ```CMAKE_INSTALL_PREFIX``` variable.

```
set(CMAKE_INSTALL_PREFIX "/home/ncmv/")
install(TARGETS ExampleProgram DESTINATION bin)
```

or via cmake command argument

```
cmake .. --prefix /home/ncmv
```

### Find-module Packages

```Find<PackageName>.cmake```: This is the CMake script files that are typically written by the user or community to locate and set up third-party libraries that do not provide their own Config package.

Some built-in Find packages available in CMake itself:
- FindBoost.cmake: Finds the Boost libraries.
- FindPython.cmake: Locates Python interpreter, libraries, and includes.
- FindZLIB.cmake: Finds the Zlib compression library.
- FindOpenGL.cmake: Locates OpenGL libraries.
- FindOpenSSL.cmake: Finds OpenSSL libraries.
- FindThreads.cmake: Detects threading libraries.

**Usage:**

CMake locate the CMake scripts ```Find<PackageName>.cmake``` by using command ```find_package```, it find the package at the searching module paths defined by variable ```CMAKE_MODULE_PATH```.

### find_package

The find_package command in CMake is used to locate and configure external libraries and packages.

**Simple form:**

```
find_package(<PackageName> [<version>] [REQUIRED] [COMPONENTS <components>...])
```

```<PackageName>```: The name of the package we want to find. It typically corresponds to a CMake package or an external library.

```<version> (optional)```: Specifies the version of the package we want to find. If not provided, any version will be acceptable.

```REQUIRED```: If this is specified, CMake will generate an error if the package cannot be found.

```COMPONENTS```: Allows us to specify which components of the package we want to find. For example, a library might have separate components for different modules, and we can choose which ones we need.

**Full signature:**

```
find_package(<PackageName> [version] [EXACT] [QUIET]
             [REQUIRED] [[COMPONENTS] [components...]]
             [OPTIONAL_COMPONENTS components...]
             [CONFIG|NO_MODULE]
             [GLOBAL]
             [NO_POLICY_SCOPE]
             [BYPASS_PROVIDER]
             [NAMES name1 [name2 ...]]
             [CONFIGS config1 [config2 ...]]
             [HINTS path1 [path2 ... ]]
             [PATHS path1 [path2 ... ]]
             [REGISTRY_VIEW  (64|32|64_32|32_64|HOST|TARGET|BOTH)]
             [PATH_SUFFIXES suffix1 [suffix2 ...]]
             [NO_DEFAULT_PATH]
             [NO_PACKAGE_ROOT_PATH]
             [NO_CMAKE_PATH]
             [NO_CMAKE_ENVIRONMENT_PATH]
             [NO_SYSTEM_ENVIRONMENT_PATH]
             [NO_CMAKE_PACKAGE_REGISTRY]
             [NO_CMAKE_BUILDS_PATH] # Deprecated; does nothing.
             [NO_CMAKE_SYSTEM_PATH]
             [NO_CMAKE_INSTALL_PREFIX]
             [NO_CMAKE_SYSTEM_PACKAGE_REGISTRY]
             [CMAKE_FIND_ROOT_PATH_BOTH |
              ONLY_CMAKE_FIND_ROOT_PATH |
              NO_CMAKE_FIND_ROOT_PATH])
```

```EXACT```: Ensures that the exact version specified is found. If not specified, newer versions are also acceptable.

```QUIET```: Suppresses the messages about the package search and errors if the package is not found.

```OPTIONAL_COMPONENTS```: Similar to COMPONENTS, but these are not required. If they are not found, the configuration will still succeed.

```CONFIG | NO_MODULE```: If CONFIG is specified, CMake will look for a package configuration file (like ```PackageNameConfig.cmake```). If NO_MODULE is specified, CMake won't search for the package using module mode.

```GLOBAL```: When using the CONFIG option, this makes the package configuration globally available, so it can be used in other parts of the CMake project.

```NO_POLICY_SCOPE```: When searching for the package, prevents CMake from applying any policy scope settings from the found package.

```BYPASS_PROVIDER```: Instructs CMake to bypass any custom providers (like package managers) when searching for the package.

```NAMES```: Allows you to specify alternative names for the package. CMake will try these names in order until it finds a match.

```CONFIGS```: A list of configuration files (e.g., PackageNameConfig.cmake) to search for.

```HINTS```: Additional paths that CMake should search when looking for the package. These paths are searched first before the default search paths.

```PATHS```: Specific paths that CMake should search for the package. These are searched after the HINTS paths.

```REGISTRY_VIEW```: On Windows, this specifies which registry view to use (e.g., 64-bit, 32-bit).

```PATH_SUFFIXES```: Subdirectories to append to each directory that is searched. Useful if your package is located in a specific subdirectory within a known path.

```NO_DEFAULT_PATH```: Prevents CMake from searching in the default paths.

```NO_PACKAGE_ROOT_PATH```: Prevents CMake from searching the root paths for the package.

```NO_CMAKE_PATH```: Disables searching in paths specified by the CMAKE_PREFIX_PATH variable.

```NO_CMAKE_ENVIRONMENT_PATH```: Disables searching in paths specified by environment variables like CMAKE_PREFIX_PATH.

```NO_SYSTEM_ENVIRONMENT_PATH```: Disables searching in system environment paths like PATH or LD_LIBRARY_PATH.

```NO_CMAKE_PACKAGE_REGISTRY```: Prevents CMake from using its internal package registry to find the package.

```NO_CMAKE_BUILDS_PATH (Deprecated)```: This option is deprecated and does nothing in newer versions of CMake.

```NO_CMAKE_SYSTEM_PATH```: Prevents CMake from searching in system paths like /usr/local.

```NO_CMAKE_INSTALL_PREFIX```: Disables searching in the paths where CMake is installed.

```NO_CMAKE_SYSTEM_PACKAGE_REGISTRY```: Prevents CMake from using the system package registry (like pkg-config or vcpkg).

```CMAKE_FIND_ROOT_PATH_BOTH | ONLY_CMAKE_FIND_ROOT_PATH | NO_CMAKE_FIND_ROOT_PATH```: Controls how CMake handles the ```CMAKE_FIND_ROOT_PATH``` during the search. This is particularly useful for cross-compiling.

For example:

```
add_executable(LocationService main.cpp)

# Look for FindGnssParser.cmake
find_package(GnssParser 1.2 REQUIRED)

if(GnssParser_FOUND)
    include_directories(${GnssParser_INCLUDE_DIRS})
    target_link_libraries(LocationService PRIVATE ${GnssParser_LIBRARIES})
endif()
```

### Create And Use Config Packages



### Create And Use Find Packages



## CMake Policies



# Conclusion

CMake is a versatile and powerful tool for managing the build process of software projects. By understanding its basic and advanced features, we can efficiently handle dependencies, organize your project, and troubleshoot common issues.

To truly understand CMake, it's essential to practice and build a sample project on your own. This hands-on experience will help you grasp the concepts better and become more proficient in using CMake for your projects.

[https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/CMake/SampleProjects/03_LocationService](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/CMake/SampleProjects/03_LocationService)

I encourage you to take up the challenge and try building the sample project before seeking the solution.

[https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/blob/master/CMake/SampleProjects/03_LocationService/CMakeLists.txt](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/blob/master/CMake/SampleProjects/03_LocationService/CMakeLists.txt)

----

**References**

[https://cmake.org/cmake/help/latest/index.html](https://cmake.org/cmake/help/latest/index.html)

[https://cmake.org/cmake/help/latest/guide/tutorial/index.html](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)

[https://blog.feabhas.com/2021/07/cmake-part-1-the-dark-arts/](https://blog.feabhas.com/2021/07/cmake-part-1-the-dark-arts/)

[https://blog.feabhas.com/2021/07/cmake-part-2-release-and-debug-builds/](https://blog.feabhas.com/2021/07/cmake-part-2-release-and-debug-builds/)

[https://blog.feabhas.com/2021/08/cmake-part-3-source-file-organisation/?fbclid=IwAR094ep-_EYNix0WLa60D2OlRrDGEAjFn3kK740mw4b98i2GfR9VsUY35is](https://blog.feabhas.com/2021/08/cmake-part-3-source-file-organisation/?fbclid=IwAR094ep-_EYNix0WLa60D2OlRrDGEAjFn3kK740mw4b98i2GfR9VsUY35is)

[https://dev.to/bruxisma/how-to-find-packages-with-cmake-the-basics-ikk](https://dev.to/bruxisma/how-to-find-packages-with-cmake-the-basics-ikk)