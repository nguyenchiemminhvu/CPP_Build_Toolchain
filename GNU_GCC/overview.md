## Introduction

The GNU Compiler Collection, also known as GCC, is a collection of compilers for various programming languages, including C, C++, Objective-C, Fortran, Ada, Go, and D. The GNU Compiler Collection (GCC) was first released in 1987 as part of the GNU Project, which was initiated by Richard Stallman in 1983. The goal of the GNU Project was to create a free Unix-like operating system composed entirely of free software.

C++ was created by Bjarne Stroustrup in 1979 as an extension of the C programming language. The first commercial implementation of C++ was released in 1985. Before the creation of GCC, C++ programs were typically compiled using proprietary compilers provided by hardware vendors or software companies, which made it challenging for developers to write and distribute C++ programs across different systems.

The GNU Compiler Collection (GCC) and the GNU Toolchain are indeed highly portable and have been made available on a wide range of operating platforms. While the GNU Project initially aimed to develop the GNU Hurd kernel as part of its operating system, the widespread adoption of the Linux kernel led to the integration of many GNU components, including GCC, the GNU C Library, and core utilities, into Linux-based operating systems.

GCC is a portable compiler, runs on most of platforms available today, produces output for many types of processors (x86_64, ARM, aarch64...).

GNU GCC is distributed under GNU GPL license (GNU General Public License), which means free to use, modify.

GNU GCC is a key component of "GNU Toolchain", a collection of programming tools produced by the GNU Project. The GNU Toolchain includes:

- GNU Compiler Collection (GCC): A compiler suite that supports many languages, such as C/C++ and Objective-C/C++.
- GNU Make: An automation tool for compiling and building applications.
- GNU Binutils: A suite of binary utility tools, including linker and assembler.
- GNU Autotools: A build system including Autoconf, Autoheader, Automake, and Libtool.- 
- GNU C Library (glibc): The C library for the GNU system and most Linux systems.
- GNU Debugger (GDB): A powerful debugger for C, C++, and other languages.

The latest version of GCC is 13.2, released on July 27, 2023. The GCC project also provides regular updates and news about its development and events related to the project. The main site for GCC is http://gcc.gnu.org/.

- GCC version 1 (1987): Initial release with support for the C programming language.
- GCC version 2 (1992): Added support for the C++ programming language.
- GCC version 3 (2001): Incorporated ECGS (Experimental GNU Compiler System) with improved optimization.
- GCC version 4 (2005): Introduced better C++ support and the Graphite framework for loop optimizations.
- GCC version 5 (2015): Improved C++11 and C++14 support, along with initial C++17 support.
- GCC Version 6 (2016): Enhanced C++14 and C++17 support, added C11 support, and various optimizations.
- GCC Version 7 (2017): Continued C++17 support, introduced C++2a support, new optimizations, and improved diagnostics.
- ...

## Compiling a C/C++ program

Compilation is a multi-stage process involving several tools, including the GNU Compiler itself (through the gcc or g++ frontends), the GNU Assembler as, and the GNU Linker ld. The complete set of tools used in the compilation process is referred to as a toolchain.

![](https://raw.githubusercontent.com/nguyenchiemminhvu/CPP_Build_Automation/master/GNU_GCC/GCC_CompilationProcess.png)

The sequence of commands executed by a single invocation of GCC consists of the following
stages:
- preprocessing (to expand macros)
- compilation (from source code to assembly language)
- assembly (from assembly language to machine code)
- linking (to create the final executable)

Let's say we have a sample C++ program source code: [https://github.com/nguyenchiemminhvu/CPP_Build_Automation/tree/master/GNU_GCC/SampleProjects/01_HelloWorld](https://github.com/nguyenchiemminhvu/CPP_Build_Automation/tree/master/GNU_GCC/SampleProjects/01_HelloWorld)

Firstly, check the version of GCC installed on your system by running the following command in your terminal:

```
worker@vu3nguyen-iconicc:~$ gcc --version
gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
```

More details by using -v option:

```
worker@vu3nguyen-iconicc:~$ gcc -v
Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-linux-gnu/7/lto-wrapper
OFFLOAD_TARGET_NAMES=nvptx-none
OFFLOAD_TARGET_DEFAULT=1
Target: x86_64-linux-gnu
Configured with: ../src/configure -v --with-pkgversion='Ubuntu 7.5.0-3ubuntu1~18.04' --with-bugurl=file:///usr/share/doc/gcc-7/README.Bugs --enable-languages=c,ada,c++,go,brig,d,fortran,objc,obj-c++ --prefix=/usr --with-gcc-major-version-only --program-suffix=-7 --program-prefix=x86_64-linux-gnu- --enable-shared --enable-linker-build-id --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --libdir=/usr/lib --enable-nls --enable-bootstrap --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --with-default-libstdcxx-abi=new --enable-gnu-unique-object --disable-vtable-verify --enable-libmpx --enable-plugin --enable-default-pie --with-system-zlib --with-target-system-zlib --enable-objc-gc=auto --enable-multiarch --disable-werror --with-arch-32=i686 --with-abi=m64 --with-multilib-list=m32,m64,mx32 --enable-multilib --with-tune=generic --enable-offload-targets=nvptx-none --without-cuda-driver --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu
Thread model: posix
gcc version 7.5.0 (Ubuntu 7.5.0-3ubuntu1~18.04)
```

To perform the preprocessor stage, execute the following GCC command:

```
g++ -E main.cpp -o main.i
```

The result is main.i file output which contains the source code with all macros expanded.

The next stage of the process is the actual compilation of preprocessed source code to assembly language.

```
g++ -S main.i -o main.s
```

The resulting assembly language is stored in the main.s file. Here is how assembly language for an ARM64 processor looks like:

![Assembly Output](https://raw.githubusercontent.com/nguyenchiemminhvu/CPP_Build_Automation/master/GNU_GCC/AssemblyOutput.png)

In the next stage, the assembler tool is used to convert assembly language into machine code and generate object files. When there are calls to external functions in the assembly source file, the assembler tool leaves the address of the external functions undefined, will be filled later in the linking stage.

```
as main.s -o main.o
```

The resulting file main.o contains the machine instructions for the compiled C/C++ program, with undefined reference to the external function calls.

```
ld main.o -L/usr/lib -lstdc++ -o main
# or
g++ main.o -o main
```

When using ld command, it knows nothing about C++ or any other programming language. So we must specify the path and library name for it. While it is easier to use GNU GCC linking because it know where the libraries are located in the current system.

```
#!/bin/bash

if [ $# -eq 0 ]; then
    # No argument provided, compile the C++ program
    g++ -E main.cpp -o main.i
    g++ -S main.i -o main.s
    as main.s -o main.o
    #ld main.o -L/usr/lib -lstdc++ -o main
    g++ main.o -o main
elif [ "$1" = "clean" ]; then
    # Argument is "clean", perform clean operation
    rm -f main.i main.s main.o main
    echo "Clean operation complete"
else
    echo "Unknown argument"
fi
```

The bash script above demonstrate the whole compilation process to create the executable file from a C++ source file.

In real life practice, we often rely on the g++ compiler tool to handle the compilation process for us. The g++ compiler is a powerful tool that can simplify the steps involved in compiling and linking C++ programs. When using g++ as a command-line tool, we can compile and link our C++ programs with a single command. For example, instead of going through the individual steps mentioned in the script, we can achieve the same result with a single command:

```
g++ main.cpp -o main
```

This command compiles the main.cpp file and links it to create the final executable main. By default, g++ performs the preprocessing, compilation, assembly, and linking steps for us. It also automatically links the necessary standard C++ libraries.

### Compiling multiple source files

### Using more compilation options
#### Adding search paths

#### Adding environment variables

#### Using preprocessors

#### Compiling for debugging

## Compiling a C/C++ library

### Compiling static library and link to C/C++ program

### Compiling shared object (dynamic library) and link to C/C++ program

## A sample project

