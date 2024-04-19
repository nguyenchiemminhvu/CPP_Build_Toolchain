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

In a real C++ project, it is common practice to split the program source code into multiple files for easier management and maintainability. This approach is known as modular programming.

Let's see another simple C++ sample project which split up the program into multiple files:
[02_MultipleSourceFile](https://github.com/nguyenchiemminhvu/CPP_Build_Automation/tree/master/GNU_GCC/SampleProjects/02_MultipleSourceFiles)

In this example, we split up the C++ program into 4 parts:
- main function defined in main.cpp file
- some simple math calculation defined in the simple_math.cpp file
- some simple algorithms defined in the simple_algo.cpp file
- the predefined library of basic input/output functionalities

The main program includes the header "simple_math.h" and "simple_algo.h" which contain the declaration of user-define functions. The declaration is used to ensure that the types of arguments and return value match up correctly between the function call and the function definition.

To compile these source files with GCC, use the following command:

```
g++ simple_math.cpp simple_algo.cpp main.cpp -o main
```

There is some error logs during the compiling process as below:

```
# g++ simple_math.cpp simple_algo.cpp main.cpp -o main

simple_algo.cpp:43:14: warning: 'auto' type specifier is a C++11 extension [-Wc++11-extensions]
        for (auto num : numbers)
             ^
simple_algo.cpp:43:23: warning: range-based for loop is a C++11 extension [-Wc++11-extensions]
        for (auto num : numbers)
                      ^
2 warnings generated.
main.cpp:21:22: error: non-aggregate type 'std::vector<int>' cannot be initialized with an initializer list
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3, 7};
                     ^         ~~~~~~~~~~~~~~~~~~~~~
1 error generated.
```

It is because we are using a C++11 feature (initializer list). To resolve this error, we need to ensure that we are compiling the source codes with a version of C++ that supports the initializer lists (from C++11 or above). We can do this by specifying a language version flag during the compilation:

```
g++ -std=c++11 simple_math.cpp simple_algo.cpp main.cpp -o main
```

When only a few files are modified, you don't need to recompile the entire program. By compiling individual files, you can save time during the build process.

Here is a full script to compile the C++ program in the example 02_MultipleSourceFiles:

```
#!/bin/bash

if [ $# -eq 0 ]; then
    # No argument provided, compile the C++ program
    g++ -o main \
        -std=c++11 \
        main.cpp \
        simple_math.cpp \
        simple_algo.cpp
elif [ "$1" = "clean" ]; then
    # Argument is "clean", perform clean operation
    rm -f simple_math.o simple_algo.o main.o main
    echo "Clean operation complete"
else
    echo "Unknown argument"
fi
```

### Using more compilation options
#### Adding search paths

A common problem when compiling a C/C++ program with many include file directories is the error:

```
FILE.h: No such file or directory
```

This problem occurs when the header file is not present in the standard include file directories used by GNU GCC.

By default, the compiler searches for header files in the standard include file directories. If the header file is located in a different directory, we need to provide the compiler with the correct path to that directory.

```
g++ -I/path/to/include FILE.cpp -o FILE
```

A similar problem occurs when linking libraries is the error:

```
# ld main.o -o main -lstdc++
ld: library 'stdc++' not found
```

This happens when a library used for linking is not present in the standard library directories used by GNU GCC.

To resolve this issue, we can use the -L flag followed by the directory path when linking your code. Additionally, we can use the -l flag followed by the library name to explicitly specify the library to link against.

```
g++ main.o -o main -L/path/to/lib -lstdc++
```

Taken the same sample source code: [02_MultipleSourceFile](https://github.com/nguyenchiemminhvu/CPP_Build_Automation/tree/master/GNU_GCC/SampleProjects/02_MultipleSourceFiles)

Now, we create a folder name "opensource" that contains the a include folder and a lib folder:

```
vu.nguyenchiemminh@localhost 02_MultipleSourceFiles# pwd
/Users/vu.nguyenchiemminh/StudySpace/CPP_Build_Automation/GNU_GCC/SampleProjects/02_MultipleSourceFiles
vu.nguyenchiemminh@localhost 02_MultipleSourceFiles# tree opensource
opensource
├── include
│   └── simplecrypto.h
└── lib
    └── libsimplecrypto.so
```

Those files are prebuilt opensource library, which can be found in the Github: [https://github.com/fumiama/simple-crypto](https://github.com/fumiama/simple-crypto)

To utilize this simple cryto library, we include the simplescrypto.h header to the main file:

```
#include "simplecrypto.h"

int main()
{
    // C++ source codes of the previous example
    // ...

    // Using opensource prebuilt library
    const char* data = "Hello, world!";
    size_t data_len = strlen(data);
    uint8_t digest[16];

    md5((const uint8_t*)data, data_len, digest);

    printf("MD5 Digest: ");
    for (int i = 0; i < 16; i++)
    {
        printf("%02x", digest[i]);
    }
    printf("\n");
}
```

Now, when compiling this C++ program with the same GCC command before:

```
g++ -std=c++11 simple_math.cpp simple_algo.cpp main.cpp -o main
```

Because the 'simplecryto.h' header file is not present in the standard include directories of GNU GCC, the missing header error pattern appears just as we mentioned above.

```
# g++ -std=c++11 simple_math.cpp simple_algo.cpp main.cpp -o main

main.cpp:10:10: fatal error: 'simplecrypto.h' file not found
#include "simplecrypto.h"
         ^~~~~~~~~~~~~~~~
1 error generated.
```

To get over this situation, try to use -I option during compilation process:

```
g++ -std=c++11 -I./opensource/include simple_math.cpp simple_algo.cpp main.cpp -o main
```

Now, when the GNU GCC tool can find the header file in the additional folder we just provided, the symbols of the external function calls are undefined.

```
# g++ -std=c++11 -I./opensource/include simple_math.cpp simple_algo.cpp main.cpp -o main

Undefined symbols for architecture arm64:
  "md5(unsigned char const*, unsigned long, unsigned char*)", referenced from:
      _main in main-38ac86.o
ld: symbol(s) not found for architecture arm64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
```

Once again, we must specify the path of the symbols that would be linked to the C++ program.

```
g++ \
    -std=c++11 \
    main.cpp \
    simple_math.cpp \
    simple_algo.cpp \
    -I./opensource/include \
    -L./opensource/lib \
    -lsimplecrypto \
    -o main
```

Note that we should never place the absolute paths of header files in #include statements in the source code, as this will prevent from compiling on other systems.

```
#!/bin/bash

if [ $# -eq 0 ]; then
    # No argument provided, compile the C++ program
    g++ \
        -std=c++11 \
        main.cpp \
        simple_math.cpp \
        simple_algo.cpp \
        -I./opensource/include \
        -L./opensource/lib \
        -lsimplecrypto \
        -o main

    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./opensource/lib
elif [ "$1" = "clean" ]; then
    # Argument is "clean", perform clean operation
    rm -f simple_math.o simple_algo.o main.o main
    echo "Clean operation complete"
else
    echo "Unknown argument"
fi
```

#### Adding environment variables

By default, GNU GCC compiler search for the header and library files in the standard directories specified in its configuration. However, we can also configure the search paths for header and library files using environment variable in the shell.

```
export C_INCLUDE_PATH=/path/to/c_headers
export CPLUS_INCLUDE_PATH=/path/to/cpp_headers
export LIBRARY_PATH=/path/to/find_at_link_time_libraries
export LD_LIBRARY_PATH=/path/to/find_at_run_time_libraries
```

These paths specified by environment variables will be searched by GNU GCC Compiler after any directories specified on the command line with option '-I', and before the standard default directories (such as /usr/include or /usr/local/include). The shell command 'export' is required to make the environment variable available to programs outside the shell itself.

Using the same sample source codes [02_MultipleSourceFile](https://github.com/nguyenchiemminhvu/CPP_Build_Automation/tree/master/GNU_GCC/SampleProjects/02_MultipleSourceFiles)

Now, because the additional header and library directories are specified using environment varialbles, we can compile the C++ program without adding search paths into the compilation command line:

```
export CPLUS_INCLUDE_PATH=./opensource/include
export LIBRARY_PATH=./opensource/lib

g++ -std=c++11 main.cpp simple_math.cpp simple_algo.cpp -lsimplecrypto -o main
```

Following the standard Unix convention for search paths, multiple directories can be specified together in an environment variable:

```
DIR1:DIR2:DIR3:...
```

For example:

```
CPLUS_INCLUDE_PATH=./opensource/include:./boost/include:./gnss/include
```

This works the same way using the option '-I' multiple times:

```
g++ -I./opensource/include -I./boost/include -I./gnss/include
```

#### Using preprocessors

There are options to control the C/C++ preprocessor, which is run on each C/C++ source file before actual compilation. The GNU C/C++ preprocessor expands the macros in the source files before they are compiled.

Notes that if we use '-E' option in the compilation command, nothing is done except preprocessing.

```
g++ -E main.cpp -o main.i
```

Keep focusing on the sample source codes: [02_MultipleSourceFile](https://github.com/nguyenchiemminhvu/CPP_Build_Automation/tree/master/GNU_GCC/SampleProjects/02_MultipleSourceFiles)

At this time, we cover the 'opensource' related codes with a macro:

```
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <iostream>
#include <vector>
#include "simple_math.h"
#include "simple_algo.h"

#ifdef USE_SIMPLE_CRYPTO_LIB
#include "simplecrypto.h"
#endif

int main(int argc, char** argv)
{
    // Using utility functions from simple_math library
    int a = 10;
    int b = 5;

    int sum = simple_math::add(a, b);
    int product = simple_math::multiply(a, b);
    double quotient = simple_math::divide(a, b);

    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Product: " << product << std::endl;
    std::cout << "Quotient: " << quotient << std::endl;

    // Using utility functions from simple_algorithm library
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3, 7};

    int max = simple_algorithm::findMax(numbers);
    int min = simple_algorithm::findMin(numbers);
    int sumOfNumbers = simple_algorithm::sum(numbers);
    double average = simple_algorithm::average(numbers);

    std::cout << "Max: " << max << std::endl;
    std::cout << "Min: " << min << std::endl;
    std::cout << "Sum of Numbers: " << sumOfNumbers << std::endl;
    std::cout << "Average: " << average << std::endl;

#ifdef USE_SIMPLE_CRYPTO_LIB
    // Using opensource prebuilt library
    const char* data = "Hello, world!";
    size_t data_len = strlen(data);
    uint8_t digest[16];

    md5((const uint8_t*)data, data_len, digest);

    printf("MD5 Digest: ");
    for (int i = 0; i < 16; i++)
    {
        printf("%02x", digest[i]);
    }
    printf("\n");
#endif

    return 0;
}
```

By default, there is no macro definition of USE_SIMPLE_CRYPTO_LIB. When the macro USE_SIMPLE_CRYPTO_LIB is defined, the preprocessor includes the corresponding code up to the closing '#endif' directives.

There are a few basic GCC options to control preprocessor:

- **-D <name>** predefine *name* as macro, with definition 1.
- **-D <name>=<definition>** The contents of *definition* are tokenized and processed as if they appeared during translation phase three in a '#define' directive.
- **-include file** Process file as if #include "file" appeared as the first line of the primary source file. However, the first directory searched for file is the preprocessor’s working directory instead of the directory containing the main source file. If not found there, it is searched for in the remainder of the #include "..." search chain as normal.

This command below is compiled normally with no USE_SIMPLE_CRYPTO_LIB macro define:

```
g++ -std=c++11 main.cpp simple_math.cpp simple_algo.cpp -o main
```

But, this command below is failed to compile because the macro USE_SIMPLE_CRYPTO_LIB is defined:

```
g++ -std=c++11 -DUSE_SIMPLE_CRYPTO_LIB main.cpp simple_math.cpp simple_algo.cpp -lsimplecrypto -o main
```

To ensure successful compilation with the USE_SIMPLE_CRYPTO_LIB macro defined, we need to specify the header and library directories of the opensource crypto module again.

```
export CPLUS_INCLUDE_PATH=./opensource/include
export LIBRARY_PATH=./opensource/lib
g++ -std=c++11 -DUSE_SIMPLE_CRYPTO_LIB main.cpp simple_math.cpp simple_algo.cpp -lsimplecrypto -o main
```

#### Compiling for debugging

Normally, an executable file after compiling does not contains any references to the original source codes, such as variable names, function names, and line numbers,... Only machine codes are sometimes insufficient for debugging.

In most of all cases, we only need to add the option '-g' to the compilation command, then the compiler includes debugging symbols into the executables. This debugging symbols allow the error to be traced back from a specific machine instruction to the corresponding line in the original source file.

Debug symbols are typically stored in a format called DWARF (Debugging With Attributed Record Formats). Reference: [https://dwarfstd.org/](https://dwarfstd.org/)

- **-g** Produce debugging information in the operating system’s native format (stabs, COFF, XCOFF, or DWARF). GDB can work with this debugging information.
- **-gdwarf -gdwarf-version** Produce debugging information in DWARF format (if that is supported). The value of version may be either 2, 3, 4 or 5; the default version for most targets is 5.

Another benefit of storing debugging symbols to the executable is the ability to examine the cause of crash program from "core dump" file.
When a program suddenly exit by a crash, the operating system may write a core file which contains the in-memory state of the program at the time it crashed, as known as "core dump". Combined with the information produced by '-g' option, developers are able to find the line where the program stopped, and the values of the variables at that point.

Below is a simple program which will produce a core file during run time:

```
// main.cpp
void makeCrash(int* p)
{
    p = nullptr;
    int val = *p;
}

int main(int argc, char** argv)
{
    makeCrash(nullptr);
    return 0;
}
```

Compile and run the program:

```
g++ -g main.cpp -o main
./main
Segmentation fault (core dumped)
```

As we can see, the segmentation fault occurs. By this time it generates a core dump file. This file contains a snapshot of the program's memory at the time of the crash, which we can use for debugging.

```
# ls -l
-rw------- 1 worker worker 253952 Apr 17 18:20 core.main.32168
-rwxrwxr-x 1 worker worker   8208 Apr 17 18:20 main
-rw-rw-r-- 1 worker worker    160 Apr 17 18:20 main.cpp
```

Let's use GDB to analyze the core dump file and find the cause of the segmentation fault.

```
# gdb main core.main.33102

GNU gdb (Ubuntu 8.1.1-0ubuntu1) 8.1.1
Copyright (C) 2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
---Type <return> to continue, or q <return> to quit---
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from main...done.
[New LWP 33102]
Core was generated by `./main'.
Program terminated with signal SIGSEGV, Segmentation fault.
#0  0x0000556530e0060e in makeCrash (p=0x0) at main.cpp:6
6           int val = *p;
(gdb) bt full
#0  0x000056433860060e in makeCrash (p=0x0) at main.cpp:4
        val = 0
#1  0x000056433860062f in main (argc=1, argv=0x7ffea8750d58) at main.cpp:9
No locals.
(gdb) backtrace 
#0  0x000056433860060e in makeCrash (p=0x0) at main.cpp:4
#1  0x000056433860062f in main (argc=1, argv=0x7ffea8750d58) at main.cpp:9
No locals.
```

The backtrace shows us that the segmentation fault occurs in the makeCrash function at line 6 of main.cpp. It seems that there is an attempt to dereference a null pointer.

Some systems are configured not to write core files by default, since the files can be large and rapidly fill up the available disk space on a system. In the GNU Bash shell the command ulimit -c controls the maximum size of core files.

```
ulimit -c unlimited
```

Reading further about GNU GDB debugging here:
[Debugging with GDB](https://ftp.gnu.org/old-gnu/Manuals/gdb/html_node/gdb_toc.html)
[Debugging C++ core file](https://www.cse.unsw.edu.au/~learn/debugging/modules/gdb_coredumps/)
[Load shared object debugging symbols](https://stackoverflow.com/questions/30281766/need-to-load-debugging-symbols-for-shared-library-in-gdb)

#### Compiling with optimization

One feature makes GNU GCC powerfull is the source code optimization. The optimized source codes achieve the same result as the original source codes but with improved performance. This mean the optimizing source codes have smaller size, increased execution speed. GNU GCC offers different optimization levels to achieve this.

- **-O0** The lowest level of optimization, no optimization is applied. Using this option, GCC Compiler produces codes that closely reflects to the original source codes. Each command in the source codes is converted directly to the corresponding machine instructions in the executable file. However, it may result in slower and less efficient performance.
- **-O1 or -O** Enable basic level of optimization: constant folding, common subexpression elimination, and dead code elimination. These flags are enabled at -O0 optimization level:
```
-fauto-inc-dec
-fbranch-count-reg
-fcombine-stack-adjustments
-fcompare-elim
-fcprop-registers
-fdce
-fdefer-pop
-fdelayed-branch
-fdse
-fforward-propagate
-fguess-branch-probability
-fif-conversion
-fif-conversion2
-finline-functions-called-once
-fipa-modref
-fipa-profile
-fipa-pure-const
-fipa-reference
-fipa-reference-addressable
-fmerge-constants
-fmove-loop-invariants
-fmove-loop-stores
-fomit-frame-pointer
-freorder-blocks
-fshrink-wrap
-fshrink-wrap-separate
-fsplit-wide-types
-fssa-backprop
-fssa-phiopt
-ftree-bit-ccp
-ftree-ccp
-ftree-ch
-ftree-coalesce-vars
-ftree-copy-prop
-ftree-dce
-ftree-dominator-opts
-ftree-dse
-ftree-forwprop
-ftree-fre
-ftree-phiprop
-ftree-pta
-ftree-scev-cprop
-ftree-sink
-ftree-slsr
-ftree-sra
-ftree-ter
-funit-at-a-time
```
- **-O2** Enable a higher level of optimization than -O1, including additional optimization strategy like: loop unrolling, function inlining, and instruction scheduling without involving the space-speed tradeoff. The compiler will take longer to compile programs and requires more memory than -O1, but result better run-time performance. These flags are enabled at this optimization level:
```
-falign-functions -falign-jumps
-falign-labels -falign-loops
-fcaller-saves
-fcode-hoisting
-fcrossjumping
-fcse-follow-jumps -fcse-skip-blocks
-fdelete-null-pointer-checks
-fdevirtualize -fdevirtualize-speculatively
-fexpensive-optimizations
-ffinite-loops
-fgcse -fgcse-lm
-fhoist-adjacent-loads
-finline-functions
-finline-small-functions
-findirect-inlining
-fipa-bit-cp -fipa-cp -fipa-icf
-fipa-ra -fipa-sra -fipa-vrp
-fisolate-erroneous-paths-dereference
-flra-remat
-foptimize-sibling-calls
-foptimize-strlen
-fpartial-inlining
-fpeephole2
-freorder-blocks-algorithm=stc
-freorder-blocks-and-partition -freorder-functions
-frerun-cse-after-loop
-fschedule-insns -fschedule-insns2
-fsched-interblock -fsched-spec
-fstore-merging
-fstrict-aliasing
-fthread-jumps
-ftree-builtin-call-dce
-ftree-loop-vectorize
-ftree-pre
-ftree-slp-vectorize
-ftree-switch-conversion -ftree-tail-merge
-ftree-vrp
-fvect-cost-model=very-cheap
```
- **-O3** Enable even more optimizations compared to -O2, including advanced techniques like loop fusion, loop vectorization, and profile-guided optimization. This option produces a significant enhance performance codes at run time, but may also increase compilation time and code size. These flags are enabled at this optimization level:
```
-fgcse-after-reload
-fipa-cp-clone
-floop-interchange
-floop-unroll-and-jam
-fpeel-loops
-fpredictive-commoning
-fsplit-loops
-fsplit-paths
-ftree-loop-distribution
-ftree-partial-pre
-funswitch-loops
-fvect-cost-model=dynamic
-fversion-loops-for-strides
```
- **-Os** This option optimizes for code size rather than performance, suitable for systems constrained by memory or disk space like embedded systems. This option includes all -O2 optimization flags except those that increase code size: ```-falign-functions -falign-jumps -falign-labels -falign-loops -fprefetch-loop-arrays -freorder-blocks-algorithm=stc```

For the details of each optimization flags, refer to the home page of GNU GCC: [https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html)

Let's consider several examples of GNU GCC optimization:

**(1) An empty main function**

```
int main(int argc, char** argv)
{
    return 0;
}
```

Assembly output of no optimization option:

```
vu.nguyenchiemminh@localhost 05_OptimziationExamples % g++ main.cpp -o main
vu.nguyenchiemminh@localhost 05_OptimziationExamples % objdump -d main

main:	file format mach-o arm64

Disassembly of section __TEXT,__text:

0000000100003f88 <_main>:
100003f88: d10043ff    	sub	sp, sp, #16
100003f8c: aa0003e8    	mov	x8, x0
100003f90: 52800000    	mov	w0, #0
100003f94: b9000fff    	str	wzr, [sp, #12]
100003f98: b9000be8    	str	w8, [sp, #8]
100003f9c: f90003e1    	str	x1, [sp]
100003fa0: 910043ff    	add	sp, sp, #16
100003fa4: d65f03c0    	ret
```

Assembly output of '-O3' optimization option:

```
vu.nguyenchiemminh@localhost 05_OptimziationExamples % g++ main.cpp -O3 -o main
vu.nguyenchiemminh@localhost 05_OptimziationExamples % objdump -d main

main:	file format mach-o arm64

Disassembly of section __TEXT,__text:

0000000100003fa0 <_main>:
100003fa0: 52800000    	mov	w0, #0
100003fa4: d65f03c0    	ret
```

We can observe that the assembly code output without optimization includes some additional instructions and stack manipulation compared to the optimized code (-O3 option).

As the source code becomes more complex, it becomes harder to understand the assembly code. In these cases, it's best to rely on the expertise of experts who have researched this area. Let me provide you with more examples of how GNU GCC optimization can help

**(2) Common subexpression elimination**

Common subexpression elimination is a compiler optimization technique that reduces redundant computations by identifying and eliminating repeated computations of the same subexpression within an expression.

```
x = cos(v) * (1 + sin(u / 2)) + sin(w) * (1 - sin(u / 2))
```

Facing the expression of x above, GNU GCC may identify the duplicate sin(u / 2) subexpression and make it a common subexpression:

```
temp = sin(u / 2)
x = cos(v) * (1 + temp) + sin(w) * (1 - temp)
```

**(3) Pre-evaluate constant expression**

```
constexpr double TO_MILLIARCSECONDS = 3600000;
double minLatMs = -90.0 * TO_MILLIARCSECONDS;
double maxLatMs = 90.0 * TO_MILLIARCSECONDS;
```

Because TO_MILLIARCSECONDS is a constant expression, during the compilation, GNU GCC Compiler can evaluate the expression of minLatMs and maxLatMs and replace them with pre-computed value:

```
constexpr double TO_MILLIARCSECONDS = 3600000;
double minLatMs = -324000000.0;
double maxLatMs = 324000000.0;
```

**(4) Loop unrolling**

Loop unrolling is a compilation technique used to improve the performance of loops. It involves replicating and expanding the loop code, effectively reducing the number of loop iterations.

For example, the following loop iterates from 0 to 6, examine the condition "i < 7" 8 times.

```
for (int i = 0; i < 7; i++)
{
    arr[i] = i;
}
```

A more efficient way to write the same code is simply unroll the loop and execute direct assignments:

```
arr[0] = 0;
arr[1] = 1;
arr[2] = 2;
arr[3] = 3;
arr[4] = 4;
arr[5] = 5;
arr[6] = 6;
```

This improvement does not requires any checking condition, and executes at maximum speed. However, loop unrolling usually increases the code size of the executable file.

Another typical loop unroll example:

```
for (int i = 0; i < 100; i++)
{
    delete arr[i];
}
```

The compiler may consider unrolling this loop in this way:

```
for (int i = 0; i < 100; i += 5)
{
    delete arr[i];
    delete arr[i + 1];
    delete arr[i + 2];
    delete arr[i + 3];
    delete arr[i + 4];
}
```

As the result of this modification, the optimized executable file only requires 20 iterations, instead of 100. It reduces 20 percents of the jump and conditional checking.

**(5) Loop unswitching**

```
void doSomething(int flags)
{
    for (int i = 0; i < 1000; i++)
    {
        if (flags == THIRD_PARTY_FEATURE)
        {
            third_party_func();
        }
        else
        {
            internal_func();
        }
    }
}
```

Consider the function doSomething above, without optimization, the program must check the flags condition a thousand times within the loop. But the value of flags is not changed indeed. GNU GCC Compiler could utilize this detail to perform optimization:

```
void doSomething(int flags)
{
    if (flags == THIRD_PARTY_FEATURE)
    {
        for (int i = 0; i < 1000; i++)
        {
            third_party_func();
        }
    }
    else
    {
        for (int i = 0; i < 1000; i++)
        {
            internal_func();
        }
    }
}
```

We don't focus much on the specifics of GNU GCC optimization in this topic. If you want more examples of how GNU GCC optimization works, you can refer to this article for reference:
[https://medium.com/@guannan.shen.ai/compiler-optimizations-46db19221947](https://medium.com/@guannan.shen.ai/compiler-optimizations-46db19221947)

#### Other common use options

- **-std=** Specifies the version of the programming language standard to be used. For example, -std=c++11 specifies the C++11 standard.
- **-Wall** Enables additional warning messages during compilation.
- **-Werror** Treats all warnings as errors.
- **-Wno-unused-parameter** Disables warnings for unused function parameters.
- **-fpermissive** Relaxes some of the strictness of the compiler, allowing certain non-standard or potentially unsafe code constructs to compile without errors. Thus, using -fpermissive allows some nonconforming code to compile.
- **-fstack-protector-all** Enables stack protection mechanisms for all functions, adding extra checks to detect and prevent stack-based buffer overflows.
- **-fPIE** Generates position-independent executables (PIE), which can be loaded at any memory address, enhancing security by making it harder for attackers to exploit certain vulnerabilities.
- **-pie** Produce a dynamically linked position independent executable on targets that support it. Similar to -fPIE, but with additional linker options to ensure that all code and data references are resolved correctly.

```
-fPIC + -fpic = -fpic
-fPIC + -fno-pic = -fno-pic
-fpic/-fPIC + (no option) = (no option)
-fPIC + -fPIE = -fPIE
-fpic + -fPIE = -fpie
-fPIC/-fpic + -fpie = -fpie
```

## Compiling a C/C++ library

### Compiling static library and link to C/C++ program

A static library is an archive of collection of reusable codes, stored in compiled object files. These files contains pre-compiled codes that can be linked directly into the C++ program at compile-time.

![](https://github.com/nguyenchiemminhvu/CPP_Build_Automation/blob/master/GNU_GCC/Executable_With_Static_Lib.png?raw=true)

Remember the example [01_HelloWorld](https://github.com/nguyenchiemminhvu/CPP_Build_Automation/tree/master/GNU_GCC/SampleProjects/01_HelloWorld)? Just right before the linking step, the C/C++ codes of the 'main.cpp' file are compiled to an object file 'main.o'. And before the GNU GCC Compiler can build up a C/C++ executable file, it must understand the definition of all external function calls (or external variables). The assembler tool will leave the address of those external functions undefined, will be filled later in the linking stage.

In that example, the GNU GCC Compiler know where to find the 'operator<<' in standard library directories. However, there could be many other user-define libraries containing useful codes we want to use. And we can also build some static libraries for ourself.

Let's consider another sample source code folder: [https://github.com/nguyenchiemminhvu/CPP_Build_Automation/tree/master/GNU_GCC/SampleProjects/03_jsoncpp_lib](https://github.com/nguyenchiemminhvu/CPP_Build_Automation/tree/master/GNU_GCC/SampleProjects/03_jsoncpp_lib)

This codes I copied from the master branch of [jsoncpp](https://github.com/open-source-parsers/jsoncpp/tree/master) project. This project has MIT license which means free to use, copy, modify, merge, publish, distribute,... Here in this article, we will only use its source code files to make an example of how to compile a static library and link it to a C++ program.

Take a look at the source code structure:

```
vu.nguyenchiemminh@localhost 03_jsoncpp_lib % tree
.
├── build
├── include
│   └── json
│       ├── allocator.h
│       ├── assertions.h
│       ├── config.h
│       ├── forwards.h
│       ├── json.h
│       ├── json_features.h
│       ├── reader.h
│       ├── value.h
│       ├── version.h
│       └── writer.h
└── src
    ├── json_reader.cpp
    ├── json_tool.h
    ├── json_value.cpp
    ├── json_valueiterator.inl
    └── json_writer.cpp
```

All the header files are located in the './include/json' directory. But the json.h header is actually the main header that includes all other headers needed for the JSON Library. In compilation process, we only need to deal with finding json.h header file problem, and it will automatically bring in all the other necessary headers. This approach simplifies the usage of JSON Library because we don't have to worry about manually including each individual header file.

The './src' directory contains the implemenation files for the JSON Library, and that are our target of making object files.

An empty '/build' directory where we can easily locate the output library file.

```
vu.nguyenchiemminh@localhost 03_jsoncpp_lib % pwd
/Users/vu.nguyenchiemminh/StudySpace/CPP_Build_Automation/GNU_GCC/SampleProjects/03_jsoncpp_lib

vu.nguyenchiemminh@localhost 03_jsoncpp_lib % g++ -c -w -std=c++11 ./src/*.cpp ./src/*.inl -I./include

vu.nguyenchiemminh@localhost 03_jsoncpp_lib % ls -la
total 1680
drwxr-xr-x  10 vu.nguyenchiemminh  staff     320 Apr 20 00:22 .
drwxr-xr-x   6 vu.nguyenchiemminh  staff     192 Apr 18 21:01 ..
drwxr-xr-x   2 vu.nguyenchiemminh  staff      64 Apr 19 23:59 build
drwxr-xr-x   3 vu.nguyenchiemminh  staff      96 Apr 20 00:11 include
-rw-r--r--   1 vu.nguyenchiemminh  staff  397264 Apr 20 00:22 json_reader.o
-rw-r--r--   1 vu.nguyenchiemminh  staff  289184 Apr 20 00:22 json_value.o
-rw-r--r--   1 vu.nguyenchiemminh  staff  163600 Apr 20 00:22 json_writer.o
drwxr-xr-x   7 vu.nguyenchiemminh  staff     224 Apr 20 00:11 src
```

```
ar rcs libjsoncpp.a json_reader.o json_value.o json_writer.o
```

```
mv libjsoncpp.a ./build
rm -rf *.o
```

```
g++ -c -w -std=c++11 ./src/*.cpp ./src/*.inl -I./include
ar rcs libjsoncpp.a json_reader.o json_value.o json_writer.o
mv libjsoncpp.a ./build
rm -rf *.o
```

### Compiling shared object (dynamic library) and link to C/C++ program

```
```

## A sample project

