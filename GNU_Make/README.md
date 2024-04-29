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
target : prerequisites ...
    recipe
	...
	...
```

- The target is the file or component that you want to build. It can be an executable, an object file, or any other type of output we desire.
- Prerequisites are the files or components that the target depends on. If any of the prerequisites are newer than the target, Make will execute the commands to update the target.
- A recipe usually contains more than one command, either on the same line or on each line. Commands of a recipe are the actions that need to be performed in order to build the target. They are are typically shell commands, and are indented by a tab character, not spaces.

### Hello Makefile

For example, let's take a look at a simple HelloWorld program:

[https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/GNU_Make/SampleProjects/01_HelloWorld](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/GNU_Make/SampleProjects/01_HelloWorld)

And with the content of Makefile below, GNU Make has enough information to compile the main executable file:

```
main: main.o
	g++ main.o -o main

main.o: main.cpp
	g++ -c -Wall -g -std=c++11 main.cpp
```

In this Makefile, the final target we expect is 'main', which is the output executable file. It depends on the prerequisite 'main.o', which is an object file generated from the source file 'main.cpp'. Let's see the make result:

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make/SampleProjects/01_HelloWorld$ make
g++ -c -Wall -g -std=c++11 main.cpp
g++ main.o -o main

ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make/SampleProjects/01_HelloWorld$ ls
main  main.cpp  main.o  Makefile

ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make/SampleProjects/01_HelloWorld$ ./main 
Hello World
```

Any time the main.cpp file is updated, GNU Make will execute this command ```g++ -c -Wall -g -std=c++11 main.cpp``` to update the main executable file. Running make command once again, the result below indicates that the target file 'main' is already up to date and does not need to be rebuilt.

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make/SampleProjects/01_HelloWorld$ make
make: 'main' is up to date.
```

**One question here, what if there is no prerequisite is supplied to the target?**

It means that the target of that rule does not depend on any other files or rules. This can be useful when we have a target that needs to be updated unconditionally, regardless of the state of any other files.

```
main: main.o
	g++ main.o -o main

main.o: main.cpp
	g++ -c -Wall -g -std=c++11 main.cpp

dump:
	@echo "Object files in the current directory:"; ls -1 *.o
```

In this case, dump target has no prerequisite. Whenever we run ```make dump``` command (to achieve only dump target), the commands associated with this rule will be executed.

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make/SampleProjects/01_HelloWorld$ make
g++ -c -Wall -g -std=c++11 main.cpp
g++ main.o -o main

ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make/SampleProjects/01_HelloWorld$ make dump
Object files in the current directory:
main.o
```

As long as the file 'dump' does not exist in the current make directory, the command for dump target will be executed. If the file 'dump' does exist, the commands associated with 'dump' target is no longer executed.

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make/SampleProjects/01_HelloWorld$ touch dump
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make/SampleProjects/01_HelloWorld$ ls
dump  main.cpp  Makefile
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make/SampleProjects/01_HelloWorld$ make dump
make: 'dump' is up to date.
```

So, the dump target and the existence of the "dump" file are directly linked. Typically, targets are used to represent files that need to be built. We usually expect that the commands associated with a target will create a file with the same name as the target, either by compiling source code or performing some other action.

However, it is not mandatory for a target to create a file with the same name. Targets can also be used to execute certain actions or perform tasks without generating files. In the case of 'dump' target, its purpose is to display the object files created in the build process, rather than creating a 'dump' file.

**How can GNU Make determine a source file has changed to recompile the associated target?**

GNU Make determines if a source file has changed by comparing its timestamp with the timestamp of the target file. If the source file's timestamp is more recent than the target file's timestamp, Make knows that the source file has been modified and triggers the recompilation of the associated target.

### clean target

The 'clean' target is a common convention in Makefiles. It is used to remove any files generated during the build process. The purpose of the 'clean' target is to ensure a clean and consistent state of the project.

The 'clean' target does not have any prerequisites, and it does not depend on any other targets. Its recipe consists of commands to delete files or directories that are generated during build process.

```
main: main.o
	g++ main.o -o main

main.o: main.cpp
	g++ -c -Wall -g -std=c++11 main.cpp

dump:
	@echo "Object files in the current directory:"; ls -1 *.o

clean:
	@rm -rf *.o main
```

Adding clean target to the [GNU_Make/SampleProjects/01_HelloWorld](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/GNU_Make/SampleProjects/01_HelloWorld) sample above, let's see how Make really does:

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make/SampleProjects/01_HelloWorld$ ls
main.cpp  Makefile

ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make/SampleProjects/01_HelloWorld$ make
g++ -c -Wall -g -std=c++11 main.cpp
g++ main.o -o main
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make/SampleProjects/01_HelloWorld$ ls
main  main.cpp  main.o  Makefile

ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make/SampleProjects/01_HelloWorld$ make clean
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make/SampleProjects/01_HelloWorld$ ls
main.cpp  Makefile
```

Including a clean target to the Makefile is a good practice we should remember.

### Write a Makefile to compile multiple source files

Using all the GNU Make knowledge from the previous sections is enough the write a simple Makefile to compile this small C++ project:

[https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/GNU_Make/SampleProjects/02_MultipleSourceFiles](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/GNU_Make/SampleProjects/02_MultipleSourceFiles)

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make/SampleProjects/02_MultipleSourceFiles$ tree
.
├── main.cpp
├── Makefile
├── simple_algo.cpp
├── simple_algo.h
├── simple_math.cpp
└── simple_math.h
```

In this example, we split up the C++ program into 4 parts:

- main function defined in main.cpp file
- some simple math calculation defined in the simple_math.cpp file
- some simple algorithms defined in the simple_algo.cpp file
- the predefined library of basic input/output functionalities

This Makefile below is a set of instructions for building an executable file called 'main'. It specifies that 'main' depends on three object files: 'main.o', 'simple_algo.o', and 'simple_math.o'.

```
main : main.o simple_algo.o simple_math.o
	g++ main.o simple_algo.o simple_math.o -o main

main.o : main.cpp
	g++ -c -std=c++11 main.cpp

simple_algo.o : simple_algo.cpp
	g++ -c -std=c++11 simple_algo.cpp

simple_math.o : simple_math.cpp
	g++ -c -std=c++11 simple_math.cpp

clean :
	@rm -f simple_math.o simple_algo.o main.o main
```

Each object file has its own rule, specifying how to compile the corresponding source file ('main.cpp', 'simple_algo.cpp', 'simple_math.cpp').

There is also a 'clean' rule, which removes the object files and the 'main' executable when executed.

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make/SampleProjects/02_MultipleSourceFiles$ make
g++ -c -std=c++11 main.cpp
g++ -c -std=c++11 simple_algo.cpp
g++ -c -std=c++11 simple_math.cpp
g++ main.o simple_algo.o simple_math.o -o main

ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make/SampleProjects/02_MultipleSourceFiles$ ./main 
Sum: 15
Product: 50
Quotient: 2
Max: 9
Min: 1
Sum of Numbers: 35
Average: 5

ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make/SampleProjects/02_MultipleSourceFiles$ make clean
```

### How Make processes a Makefile?

By default, Make starts with the first target, it is called "default target".

In the simple example of the previous section, the default target is 'main'. The default goal is to update the executable program called 'main'; therefore, we put that rule at first.

But before Make can fulfill the rule for 'main' target, it must process the rules that 'main' target depends on, which are the object files. Each object file 'main.o', 'simple_algo.o', and 'simple_math.o' are processed according to its own rule. These rules say to update each of object file by compiling its source files.

It is not mandatory to put the default target on top of other targets in the Makefile, but it is a common convention and a good practice to do so. When run ```make``` without specifying a target, Make will build the default target.

### Variables



## Conclusion

After exploring the GNU Make tool, It is clear that GNU Make is a powerful tool for automating the process of building software projects. With GNU Make, managing large projects with multiple files becomes more efficient and less time-consuming.

To truly grasp the concepts behind GNU Make and how it is used in C/C++ programming, it is crucial to gain practical experience with sample projects:

[GNU_Make/SampleProjects/03_jsoncpp_lib](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/GNU_Make/SampleProjects/03_jsoncpp_lib)

[GNU_Make/SampleProjects/04_LocationService](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/GNU_Make/SampleProjects/04_LocationService)

Try to create your Makefiles first, before looking for a solution:

[GNU_Make/SampleProjects/03_jsoncpp_lib/Makefile](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/blob/master/GNU_Make/SampleProjects/03_jsoncpp_lib/Makefile)

[GNU_Make/SampleProjects/04_LocationService/Makefile](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/blob/master/GNU_Make/SampleProjects/04_LocationService/Makefile)

----
**References:**

https://www.gnu.org/software/make/manual/make.html

https://makefiletutorial.com/

https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile

https://blog.jgc.org/2013/02/updated-list-of-my-gnu-make-articles.html
