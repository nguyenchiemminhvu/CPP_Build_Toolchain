## Introduction

Before exploring Autotools, let's make sure we have a complete understanding of [GNU Make](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/GNU_Make).

In the tutorial about GNU Make above, there are some examples of Makefiles that are not too long or difficult to understand. Writing these Makefiles for small projects doesn't take much effort. However, when it comes to compiling large projects that need to run on different Unix-like systems, it becomes quite a challenge to write a Makefile that can meet these requirements. You might end up with a Makefile that spans thousands of lines and includes many macro definitions (-D) to accommodate various configurations.

```
#ifdef _WIN32
    #define OS_NAME "Windows"
#elif __APPLE__
    #define OS_NAME "Mac OS"
#elif __linux__
    #ifdef __ANDROID__
        #define OS_NAME "Android"
    #else
        #define OS_NAME "Linux"
    #endif
#elif __unix__
    #define OS_NAME "Unix-like"
#else
    #define OS_NAME "Unknown"
#endif

#ifdef __GNUC__
    #define COMPILER_NAME "GCC"
#elif _MSC_VER
    #define COMPILER_NAME "MSVC"
#elif __clang__
    #define COMPILER_NAME "Clang"
#else
    #define COMPILER_NAME "Unknown"
#endif

#ifdef __LP64__
    #define ARCHITECTURE "64-bit"
#else
    #define ARCHITECTURE "32-bit"
#endif
```

This is where GNU Autotools can be really helpful.

The GNU Autotools, also known as the GNU Build System, is a set of handy software packages including Autoconf, Automake, and Libtool used for building software on different types of Unix-like operating systems (POSIX-like).

- Autoconf helps create portable scripts to configure source code packages using templates and an M4 macro package.
- Automake helps create portable GNU standards-compiant Makefiles from template files, supporting all the targets documented by the [GNU Coding Standards](https://www.gnu.org/prep/standards/standards.html).
- Libtool helps create and use shared libraries portably.

Although Autoconf, Automake, and Libtool are three different tools that were developed independently, they can be combined together to form a toolchain. (A toolchain refers to the concept where the output of one tool becomes the input of another tool)

Look at the below diagram to see how these tools work together:

![GNU Autotools process](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/blob/master/GNU_Autotools/GNU_Autotools_process.png?raw=true)

At the end, developers using GNU Autotools only need to care about the manual input files 'configure.ac' and 'Makefile.am'.

## Build HelloWorld project

The first thing we need before doing some stuff with Autotools is having a compilable source code repository. I prepare a simple one: [GNU_Autotools/SampleProjects/01_HelloWorld](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/GNU_Autotools/SampleProjects/01_HelloWorld)

### Write configure.ac for Autoconf

Write 'configure.ac' file might be quite complex at first sight. But for a simple C++ program like this HelloWorld, there are only a few configurations need to be set.

The programming language used for 'configure.ac' file is called Autoconf language. Autoconf is different from other programming languages because it treats code and plain text in the same way.

- **AC_INIT**

- **AM_INIT_AUTOMAKE**

- **AC_PROG_CXX**

- **AC_CONFIG_FILES**

- **AC_OUTPUT**

The configure.ac file must be presented at the project's root directory.

```
AC_INIT([HelloWorld], [1.0], [nguyenchiemminhvu@gmail.com])
AM_INIT_AUTOMAKE
AC_PROG_CXX
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
```

### Write Makefile.am for Automake

Makefile.am file has the same format and syntax as a Makefile. If you went through the tutorial about [GNU Make](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/GNU_Make) and write a Makefile from scratch by yourself, things will be familiar. Often, we only need to define some variables in Makefile.am to indicate that what files will be built, where they will be intalled.

```
bin_PROGRAMS = helloworld
helloworld_SOURCES = main.cpp
```

### Start Building

#### Step By Step

After preparing the 'configure.ac' and 'Makefile.am' files, everything is ready for Autotools build process.

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld$ pwd
/home/ncmv/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld$ ls
configure.ac  main.cpp  Makefile.am
```

By running 'aclocal' command, a file aclocal.m4 is generated.

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld$ aclocal
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld$ ls
aclocal.m4  autom4te.cache  configure.ac  main.cpp  Makefile.am
```

The purpose of 'aclocal' is to consolidate different macro files from Autotool packages and user-specified locations into one file. This file, 'aclocal.m4', contains all the necessary macros that Autoconf needs to configure the project.

![](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/blob/master/GNU_Autotools/aclocal_m4.png?raw=true)

With both input files 'configure.ac' and 'aclocal.m4', Autoconf has enough information about the build environment and project's dependencies to generate a 'configure' script. 

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld$ autoconf 
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld$ ls
aclocal.m4  autom4te.cache  configure  configure.ac  main.cpp  Makefile.am
```

The 'configure' script is important in Autotools because it is responsible for detecting the required libraries, and determine platform-specific details... to setup the necessary variables and options for the generated Makefile. The generated Makefile then adapts to the running platform and operating system.

For the next step, we run ```automake --add-missing``` command to build a 'Makefile.in' file from 'Makefile.am'.

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld$ automake --add-missing 
configure.ac:2: installing './install-sh'
configure.ac:2: installing './missing'
Makefile.am: error: required file './AUTHORS' not found
Makefile.am: error: required file './ChangeLog' not found
Makefile.am: installing './INSTALL'
Makefile.am: error: required file './NEWS' not found
Makefile.am: error: required file './README' not found
Makefile.am: installing './COPYING' using GNU General Public License v3 file
Makefile.am:     Consider adding the COPYING file to the version control system
Makefile.am:     for your code, to avoid questions about which license your project uses
Makefile.am: installing './depcomp'
```

What's wrong with it? The error indicates that there are some required files for the project folder: AUTHORS, ChangeLog, NEWS, and README. This is one of the specific expectations made up the GNU build standard. Not a big deal, let us create these files in the root directory of project folder. We can even left them empty files, but it is a good practice to fill some basic information in the change logs.

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld$ ls
aclocal.m4  AUTHORS  autom4te.cache  ChangeLog  configure  configure.ac  main.cpp  Makefile.am  NEWS  README
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld$ cat AUTHORS 
NCMV <nguyenchiemminhvu@gmail.com>
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld$ cat ChangeLog 
2024-05-12  NCMV  <nguyenchiemminhvu@gmail.com>
    * Initial commit
```

Now, continue at where we failed.

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld$ automake --add-missing 
configure.ac:2: installing './install-sh'
configure.ac:2: installing './missing'
Makefile.am: installing './INSTALL'
Makefile.am: installing './COPYING' using GNU General Public License v3 file
Makefile.am:     Consider adding the COPYING file to the version control system
Makefile.am:     for your code, to avoid questions about which license your project uses
Makefile.am: installing './depcomp'
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld$ ls
aclocal.m4  AUTHORS  autom4te.cache  ChangeLog  configure  configure.ac  COPYING  depcomp  INSTALL  install-sh  main.cpp  Makefile.am  Makefile.in  missing  NEWS  README
```

The '--add-missing' option tells 'automake' to automatically generate all of additional files required. It is useful when we start a new project or if we have recently cleaned up our project directory and accidentally removed some of these auxiliary files.

Now, Makefile.in file is created for the intput of 'configure' script. Just one more step, we gonna have our final Makefile.

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld$ ./configure 
checking for a BSD-compatible install... /usr/bin/install -c
checking whether build environment is sane... yes
checking for a race-free mkdir -p... /usr/bin/mkdir -p
checking for gawk... gawk
checking whether make sets $(MAKE)... yes
checking whether make supports nested variables... yes
checking for g++... g++
checking whether the C++ compiler works... yes
checking for C++ compiler default output file name... a.out
checking for suffix of executables... 
checking whether we are cross compiling... no
checking for suffix of object files... o
checking whether the compiler supports GNU C++... yes
checking whether g++ accepts -g... yes
checking for g++ option to enable C++11 features... none needed
checking whether make supports the include directive... yes (GNU style)
checking dependency style of g++... gcc3
checking that generated files are newer than configure... done
configure: creating ./config.status
config.status: creating Makefile
config.status: executing depfiles commands

ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld$ ls
aclocal.m4  autom4te.cache  config.log     configure     COPYING  INSTALL     main.cpp  Makefile.am  missing  README
AUTHORS     ChangeLog       config.status  configure.ac  depcomp  install-sh  Makefile  Makefile.in  NEWS
```

The 'configure' script tests system features and set the appropriate variables in the generated Makefile. For example, the result above shows us GNU GCC compiler for C++ programming language is available:

```
checking for g++... g++
checking whether the C++ compiler works... yes
```

Then, Autotools can choose the g++ compiler for our C++ program:

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld$ cat Makefile | grep g++
CXX = g++
ac_ct_CXX = g++
```

Or because our C++ program is quite simple, not using any C++11 features. So, configure script tells that:

```
checking for g++ option to enable C++11 features... none needed
```

As a result, the option '-std=c++11' is not found in the generated Makefile.

At last, simply run the 'make' command to build our C++ program.

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld$ make
g++ -DPACKAGE_NAME=\"HelloWorld\" -DPACKAGE_TARNAME=\"helloworld\" -DPACKAGE_VERSION=\"1.0\" -DPACKAGE_STRING=\"HelloWorld\ 1.0\" -DPACKAGE_BUGREPORT=\"nguyenchiemminhvu@gmail.com\" -DPACKAGE_URL=\"\" -DPACKAGE=\"helloworld\" -DVERSION=\"1.0\" -I.     -g -O2 -MT main.o -MD -MP -MF .deps/main.Tpo -c -o main.o main.cpp
mv -f .deps/main.Tpo .deps/main.Po
g++  -g -O2   -o helloworld main.o  

ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld$ ./helloworld 
Hello World
```

#### Simplified with Autoreconf

With the help of Autoreconf, the build process is even more simplified. Autoreconf knows how to prepare the necessary scripts and files needed to generate the Makefile correctly. It performs three important tasks: aclocal, autoconf, and automake.

![GNU Autotools process improved with autoreconf](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/blob/master/GNU_Autotools/GNU_Autotools_process_improved.png?raw=true)

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld$ pwd
/home/ncmv/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld$ ls
AUTHORS  ChangeLog  configure.ac  main.cpp  Makefile.am  NEWS  README
```

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld$ autoreconf -i
configure.ac:2: installing './install-sh'
configure.ac:2: installing './missing'
Makefile.am: installing './INSTALL'
Makefile.am: installing './COPYING' using GNU General Public License v3 file
Makefile.am:     Consider adding the COPYING file to the version control system
Makefile.am:     for your code, to avoid questions about which license your project uses
Makefile.am: installing './depcomp'

ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld$ ls
aclocal.m4  AUTHORS  autom4te.cache  ChangeLog  configure  configure.ac  COPYING  depcomp  INSTALL  install-sh  main.cpp  Makefile.am  Makefile.in  missing  NEWS  README
```

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld$ ./configure 
checking for a BSD-compatible install... /usr/bin/install -c
checking whether build environment is sane... yes
checking for a race-free mkdir -p... /usr/bin/mkdir -p
checking for gawk... gawk
checking whether make sets $(MAKE)... yes
checking whether make supports nested variables... yes
checking for g++... g++
checking whether the C++ compiler works... yes
checking for C++ compiler default output file name... a.out
checking for suffix of executables... 
checking whether we are cross compiling... no
checking for suffix of object files... o
checking whether the compiler supports GNU C++... yes
checking whether g++ accepts -g... yes
checking for g++ option to enable C++11 features... none needed
checking whether make supports the include directive... yes (GNU style)
checking dependency style of g++... gcc3
checking that generated files are newer than configure... done
configure: creating ./config.status
config.status: creating Makefile
config.status: executing depfiles commands

ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld$ ls
aclocal.m4  autom4te.cache  config.log     configure     COPYING  INSTALL     main.cpp  Makefile.am  missing  README
AUTHORS     ChangeLog       config.status  configure.ac  depcomp  install-sh  Makefile  Makefile.in  NEWS
```

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld$ make
g++ -DPACKAGE_NAME=\"HelloWorld\" -DPACKAGE_TARNAME=\"helloworld\" -DPACKAGE_VERSION=\"1.0\" -DPACKAGE_STRING=\"HelloWorld\ 1.0\" -DPACKAGE_BUGREPORT=\"nguyenchiemminhvu@gmail.com\" -DPACKAGE_URL=\"\" -DPACKAGE=\"helloworld\" -DVERSION=\"1.0\" -I.     -g -O2 -MT main.o -MD -MP -MF .deps/main.Tpo -c -o main.o main.cpp
mv -f .deps/main.Tpo .deps/main.Po
g++  -g -O2   -o helloworld main.o  

ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools/SampleProjects/01_HelloWorld$ ./helloworld 
Hello World
```

By using 'autoreconf', we achieve the same result, but less steps to run. It reduces our manual efforts.

## Build a Library

In this section, we would practice to build a library and expect to have a shared object as output.
[GNU_Autotools/SampleProjects/02_jsoncpp_lib](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/GNU_Autotools/SampleProjects/02_jsoncpp_lib)

The preparation steps are the same: a 'configure.ac' file for ```autoconf``` and a 'Makefile.am' file ```automake```.

### Write configure.ac for Autoconf

```
```

### Write Makefile.am for Automake

```
```

### Start Building

```
```

## Learn more about Autotools

### Autoconf

### Automake

### Libtool

## Conclusion

In simple terms, GNU Autotools is a collection of tools that make it easier to build and install software projects. Autoconf helps us configure our project by detecting system features and dependencies. Automake generates the necessary Makefiles to build our project. Libtool helps manage shared libraries for better compatibility.

To truly understand Autotools, it's essential to practice and build a sample project on your own: [GNU_Autotools/SampleProjects/02_LocationService](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/GNU_Autotools/SampleProjects/02_LocationService)

I encourage you to take up the challenge and try building the sample project before seeking the [Solution](). 

**References**

[https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.72/autoconf.html](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.72/autoconf.html)

[https://www.gnu.org/savannah-checkouts/gnu/automake/manual/automake.html](https://www.gnu.org/savannah-checkouts/gnu/automake/manual/automake.html)

[https://www.gnu.org/savannah-checkouts/gnu/libtool/manual/libtool.html](https://www.gnu.org/savannah-checkouts/gnu/libtool/manual/libtool.html)

[https://www.gnu.org/software/automake/faq/autotools-faq.html](https://www.gnu.org/software/automake/faq/autotools-faq.html)

[https://opensource.com/article/19/7/introduction-gnu-autotools](https://opensource.com/article/19/7/introduction-gnu-autotools)

[https://www.star.bnl.gov/~liuzx/autobook.html](https://www.star.bnl.gov/~liuzx/autobook.html)

[http://freesoftwaremagazine.com/articles/brief_introduction_to_gnu_autotools/](http://freesoftwaremagazine.com/articles/brief_introduction_to_gnu_autotools/)