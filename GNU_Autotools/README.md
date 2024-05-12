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

With the help of Autoreconf, the build process is even more simplified. Autoreconf knows how to prepare the necessary scripts and files needed to generate the Makefile correctly.

![GNU Autotools process improved with autoreconf](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/blob/master/GNU_Autotools/GNU_Autotools_process_improved.png?raw=true)

At the end, developers using GNU Autotools only need to care about the manual input files 'configure.ac' and 'Makefile.am'.

## Working With Autotools

The first thing we need before doing some stuff with Autotools is having a compilable source code repository. I prepare a simple one: [GNU_Autotools/SampleProjects/01_HelloWorld](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/GNU_Autotools/SampleProjects/01_HelloWorld)

### Write configure.ac for Autoconf

Write configure.ac file might be quite complex at first sight. But for a simple C++ program like this HelloWorld, there are only a few configurations need to be set.

- **AC_INIT**

- **AM_INIT_AUTOMAKE**

- **AC_PROG_CXX**

- **AC_CONFIG_FILES**

- **AC_OUTPUT**

### Write Makefile.am for Automake

Makefile.am file has the same format and syntax as a Makefile. If you went through the tutorial about [GNU Make](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/GNU_Make) and write a Makefile from scratch by yourself, things will be familiar. Often, we only need to define some variables in Makefile.am to indicate that what files will be built, where they will be intalled.

```
bin_PROGRAMS = helloworld
helloworld_SOURCES = main.cpp
```

### Start Building



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