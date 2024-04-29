## Introduction

### What is GNU Make and why is it useful?

In the vision of creating a complete free and open-source software ecosystem, led by Richard Stallman, after the creation of the GNU GCC Compiler in 1987, the GNU Project released GNU Make in 1988.

The GNU GCC Compiler was a great accomplishment as it provided a free and powerful tool to compile code. However, the GNU GCC alone may have some limitations.

Imagine you have a big project that consists of multiple files, like source code files, libraries, and other resources.

![](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/blob/master/GNU_Make/MultipleDependencies.png?raw=true)

Now, building that project means taking all these pieces and putting them together in the right order to create the final executable file. For a large project with  thousand source code files, it becomes difficult to maintain the build process.

In the early days of software development, programmers had to manually compile and link their code every time they made a change. It cost even more time and effort when the source code structure of their project has changed.

This is where GNU Make steps in. GNU Make was created with the primary purpose that is to automate the process of building software by managing dependencies and executing the necessary commands to compile and link the various components.

With GNU Make, we can define a set of rules that describe how to build the project. These rules specify the dependencies between files, and the commands needed to compile them. When the source codes have changed, GNU Make is smart enough to figure out which files need to be recompiled based on their dependencies.

GNU Make can be used for building projects in various programming languages, not just limited to C/C++, whenever you need a series of instructions to run depending on what files have changed. To demonstrate this, let's take a look at a simple Makefile that is not related to C/C++ programming:

A Makefile for a project writen in Python programming language:
[https://github.com/TezRomacH/python-package-template/blob/master/Makefile](https://github.com/TezRomacH/python-package-template/blob/master/Makefile)

A Make file for a project writen in Go programming language:
[https://github.com/thockin/go-build-template/blob/master/Makefile](https://github.com/thockin/go-build-template/blob/master/Makefile)

However, in this series of CPP build toolchain tutorials, we only concentrate on using the toolchain to compile C/C++ programs.

We first need to install GNU Make. If you have Linux OS installed on your PC, try the following shell commands:

```
sudo apt update
sudo apt install make
```

After the installation is complete, we can verify that GNU Make is installed by running the following command:

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain$ make --version
GNU Make 4.3
Built for x86_64-pc-linux-gnu
Copyright (C) 1988-2020 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
```

The latest stable version is 4.3, released January 19, 2020.
Explore and download different releases of Make here: https://ftp.gnu.org/gnu/make/

Using GNU Make is quite simple. When you run the command "make", it looks for a file called "Makefile" in the current directory, it reads the instructions from the makefile and carries out the necessary steps to build your project.

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain$ pwd
/home/ncmv/study_workspace/CPP_Build_Toolchain

ncmv@localhost:~/study_workspace/CPP_Build_Toolchain$ cat Makefile 
hello:
    echo "Hello GNU Make"

ncmv@localhost:~/study_workspace/CPP_Build_Toolchain$ make
echo "Hello GNU Make"
Hello GNU Make
```

Now, all we need to know is the syntax or other details for writing the content of a Makefile.

### Makefile syntax

In a Makefile, we define a set of rules that specify how to build different parts of your project. Each rule consists of a target, prerequisites, and commands. Here's the basic structure:

```
target: prerequisites
    commands
```

- The target is the file or component that you want to build. It can be an executable, an object file, or any other type of output we desire.
- Prerequisites are the files or components that the target depends on. If any of the prerequisites are newer than the target, Make will execute the commands to update the target.
- Commands are the actions that need to be performed in order to build the target. They are are typically shell commands, and are indented by a tab character, not spaces.

[https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/GNU_Make/SampleProjects/01_HelloWorld](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/GNU_Make/SampleProjects/01_HelloWorld)

```
main: main.o
	g++ main.o -o main

main.o: main.cpp
	g++ -c -Wall -g -std=c++11 main.cpp
```

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make/SampleProjects/01_HelloWorld$ make
g++ -c -Wall -g -std=c++11 main.cpp
g++ main.o -o main

ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make/SampleProjects/01_HelloWorld$ ls
main  main.cpp  main.o  Makefile

ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make/SampleProjects/01_HelloWorld$ ./main 
Hello World
```

## Writing Makefiles

### Syntax and structure of a Makefile

### Variables: defining and using them

### Rules: creating rules and specifying dependencies

### Phony targets: when and how to use them

## Advanced Makefile Features

### Pattern rules: automating build processes.

### Conditional statements: controlling the flow of execution

### Functions: using built-in functions for advanced operations

### Including other Makefiles: organizing your build system

## Makefile demos

### Simple Compilation

Target: To demonstrate a basic Makefile for compiling a C program with multiple source files.

### Dependency Management

Target: To show how Make handles dependencies by creating a Makefile for a project with multiple source files and headers.

### Build Optimization

Target: To show some techniques for optimizing build processes, such as parallel execution and incremental builds.

## Conclusion


References:
https://www.gnu.org/software/make/manual/make.html
https://makefiletutorial.com/
https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile
https://blog.jgc.org/2013/02/updated-list-of-my-gnu-make-articles.html
