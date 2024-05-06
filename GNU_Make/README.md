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

### Makefile Syntax

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

## Basic Makefile Concepts

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

### The clean target

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

### The all target

The ```all``` target is typically used to specify the default target that should be built when you execute the make command without any arguments. The target ```all``` is not a built-in target in Makefile, but a convention that many developers follow.

```
all : target1 target2 target3

target1 : prerequisite_1
	recipe_1

target2 : prerequisite_2
	recipe_2

target3 : prerequisite_3
	recipe_3
```

Here, the **target1**, **target2** and **target3** represent the actual targets we want to build when executing ```make``` or ```make all``` command.

### Phony targets

Usually, when we define a target in Makefile, GNU Make expects that target to be a file existing after executing the recipe. Sometimes, we have targets that don't correspond to any files. These targets are called **PHONY targets**.

To declare a target as phony, here is the syntax:

```
.PHONY : target_1 target_2 ...
```

For example:

```
clean :
	rm -rf *.o main

.PHONY: clean
```

By doing this, we tells GNU Make that the 'clean' target is not an actual file expected to exist after running the clean commands. Therefore, even a file named 'clean' is created, Make still executes the 'clean' recipe. 

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

By default, Make starts with the first target, it is called "default target".

In the simple example of the previous section, the default target is 'main'. The default goal is to update the executable program called 'main'; therefore, we put that rule at first.

But before Make can fulfill the rule for 'main' target, it must process the rules that 'main' target depends on, which are the object files. Each object file 'main.o', 'simple_algo.o', and 'simple_math.o' are processed according to its own rule. These rules say to update each of object file by compiling its source files.

It is not mandatory to put the default target on top of other targets in the Makefile, but it is a common convention and a good practice to do so. When run ```make``` without specifying a target, Make will build the default target.

### Splitting Recipe Lines

GNU Make has no limit on the length of the recipe. But for better readability, GNU Make allows us to break long lines in Makefile into multiple lines. We can do this by putting backslash (\) character in the middle of the command/statement, then Make will treat the next line of the command as a continuation of the previous line.

```
main : main.o simple_algo.o simple_math.o
	g++ main.o \
		simple_algo.o \
		simple_math.o \
		-o main

main.o : main.cpp
	g++ \
		-c \
		-g \
		-Wall \
		-std=c++11 \
		main.cpp

simple_algo.o : simple_algo.cpp
	g++ \
		-c \
		-g \
		-Wall \
		-std=c++11 \
		simple_algo.cpp

simple_math.o : simple_math.cpp
	g++ \
		-c \
		-g \
		-Wall \
		-std=c++11 \
		simple_math.cpp

clean :
	@rm -f \
		simple_math.o \
		simple_algo.o \
		main.o \
		main
```

It's important to note that when using this feature, the backslash character must be the last character on the line, and there shouldn't be any trailing spaces after it.

### Include Other Makefile

When working in a large project or complex build systems, It is often necessary to split the Makefile into multiple smaller, more manageable pieces. By using ```include``` directive in Makefile, we can bring in the contents of another Makefile and incorporate it into the current one. This feature is useful when we have some common rules or variables that we wish to reuse across multiple Makefiles.

```
include path/to/another/Makefile
```

**What Make will do when encountering an include directive?**

When ```make``` processes an ```include``` directive, it temporarily stops reading the current file and starts reading the files that are listed in the include directive, one by one. Once it finishes reading all the included files, it goes back to reading the original file where the ```include``` directive was found.

In case the another Makefile is not found, an error is generated. If we want Make to ignore a Makefile which does not exist (with no error message), use the ```-include``` directive instead. Make will simply continue processing the rest of Makefile without including the missing Makefile.

```
-include path/to/another/Makefile
```

Here is an example to demonstrate the include feature of Make:

```
# ./common/common_cpp.mk
CXXFLAGS += -std=c++11 -Wall -Werror
```

```
# ./common/security_enhancement.mk
CXXFLAGS += -fstack-protector-strong -Wformat -Wformat-security
```

```
-include ./common/common_cpp.mk
-include ./common/security_enhancement.mk

all : main

main : main.cpp
	g++ $(CXXFLAGS) main.cpp -o main
```

### Recursive Use of Make

**Recursive Use of Make** feature definition is simple:
>Recursive use of ```make``` means using ```make``` as a command in a Makefile.

This feature is particularly useful when we have a complex project with multiple directories and subdirectories, each containing their own set of rules and dependencies.

For example, supposed we have a sub-directory named 'subdir' which has its own Makefile, we would like to access this 'subdir' and execute its Makefile, it can be done this way:

```
subdir :
	cd subdir && $(MAKE)
```

It is equivalent to the below way if we use Recursive Make feature:

```
subdir : 
	$(MAKE) -C subdir
```

**Why we use $(MAKE) instead of calling ```make``` command?**

When you use $(MAKE) variable in a target recipe, it expands to the appropriate command for invoking make. (Learn about [Variable](#variables) in the next section). If the ```make``` binary file name was /bin/make, then the recipe executed is ‘cd subdir && /bin/make’.

In the example below, we supposed to have a program that depends on 3 prerequisites: libcurl.so, libsqlite.so and libqt.so. Those libraries are located in the corresponding sub-directories and having their own Makefile.

```
all: main

main: main.cpp lib_curl lib_sqlite lib_qt
	g++ -rdynamic \
		-L./lib_curl/build \
		-L./lib_sqlite/build \
		-L./lib_qt/build \
		main.cpp \
		-lcurl \
		-lsqlite \
		-lqt \
		-o main

lib_curl:
	$(MAKE) -C lib_curl

lib_sqlite:
	$(MAKE) -C lib_sqlite

lib_qt:
	$(MAKE) -C lib_qt

.PHONY: all lib_curl lib_sqlite lib_qt
```

### Variables

In the sample Makefile of the [previous section](#splitting-recipe-lines), we can observe several duplication like object files declaration, GCC Compilation flags,... Such duplication is error-prone. When a new object file is added into the project, we might add it to one list and forget another one. Instead of repeating the compiler command and flags in each target rule, we can use the variables.

Variables are like containers that hold information or values. This way, we only need to specify the value once, and it can be easily substituted wherever needed. 

Variable names are case-sensitive. So, 'foo', 'FOO', and 'Foo' would indeed be treated as separate variables.

There is two common used assignment syntax in Makefile:

#### Simply Expanded Variable Assignment

```
var_name := values
```

When using Simply Expanded Variable Assignment ```:=``` to assign values to a variable in Makefile, it means the right-hand side of the assignment is expanded immediately, and the resulting values are stored in the variable. Using Simply Expanded Variable Assignment when we want to guarantee that the variable is expanded only once.

Therefore, 

```
x := foo
y := $(x) bar
x := later
```

is equivalent to

```
y := foo bar
x := later
```

Using Simply Expanded variables generally make complicated Makefile more predictable because they work like variables in most programming languages.

#### Recursively Expanded Variable Assignment

```
var_name = values
```

When using Recursively Expanded Variable Assignment ```=``` to assign values to a variable in Makefile, it means the right-hand side of the assignment is not expanded immediately. Instead, it is stored as it is, and the expansion happens whenever the variable is referenced.

This way is useful when we want the variable to be dynamically evaluated or when the value of the variable depends on other variables that might change during the Makefile execution.

One advantage of using Recursively Expanded Variable is that it allows us to combine multiple values or options into a single variable.

```
CXXFLAGS = $(INCLUDE_DIRS) -Wall -Werror -g
INCLUDE_DIRS = -Ipath/to/libA/include -Ipath/to/libB/include
```

However, there is a major disadvantage. 

We cannot directly append something to the end of a flavor variable. For instance, if we try to define

```
CXXFLAGS = $(CXXFLAGS) -O
```

It will cause an infinite loop in the variable expansion process. Actually, Make is smart enough to detect this and report an error.

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make/SampleProjects/02_MultipleSourceFiles$ make
Makefile:7: *** Recursive variable 'CXXFLAGS' references itself (eventually).  Stop.
```

GNU Make allows us to append more text to variables just like ```+=``` operator apply on ```std::string``` in C++ programming language.

```
var_name += values
```

In this example below, we have a variable named 'CPP_FILES' contains the source code files to be compiled, starting with only 'main.cpp'. But we append more CPP files to the list by using ```+=``` operator.

```
CPP_FILES = ./service/main.cpp
CPP_FILES += \
	./service/source_a.cpp \
	./service/source_b.cpp
```

It works the same way with:

```
CPP_FILES = ./service/main.cpp
CPP_FILES = $(CPP_FILES) \
	./service/source_a.cpp \
	./service/source_b.cpp
```

It is important to note that when a variable is set using a command argument, any subsequent assignments to that variable in the Makefile are usually ignored. But sometimes, we might want to set the variable in the Makefile itself, regardless of whether it was set with a command argument. We can do this with ```override``` directive:

```
# redefine
override var_name = values

# append more text
override var_name += values
```

After finish using a variable and if we want to clear its value, usually assign it to an empty string is sufficient. Expanding the variable of empty string has no meaning. But, to make it more flavor in our Makefile, it is preferred to use ```undefine``` directive:

```
undefine var_name
```

In case the variable is set by a command line, we can use ```override``` together with ```undefine```

```
override undefine CPP_FILES
```

Let's try to use variable to simplify the Makefile of [previous section](#write-a-makefile-to-compile-multiple-source-files):

```
CXX := g++
CXXFLAGS = -g -Wall -std=c++11
OBJECTS = main.o simple_algo.o simple_math.o

main : $(OBJECTS)
	$(CXX) $(OBJECTS) -o main

main.o : main.cpp
	$(CXX) -c $(CXXFLAGS) main.cpp

simple_algo.o : simple_algo.cpp
	$(CXX) -c $(CXXFLAGS) simple_algo.cpp

simple_math.o : simple_math.cpp
	$(CXX) -c $(CXXFLAGS) simple_math.cpp

clean :
	@rm -f main $(OBJECTS)
```

By using variables, we not only make our Makefile more readable and concise, but also ensure consistency.

#### Variable References

The syntax ```$(var)``` or ```${var}``` is used to reference a variable. Make would substitute the variable reference by its values evaluated by that time.

Variable references can be used in any context: targets, prerequisites, recipes, most directives, and new variable values.

Like MACRO substitution in C/C++ programming language, Make substitutes the variable references just the same way, a strict textual substitution. So, the rule below:

```
foo = c
prog.o : prog.$(foo)
	$(foo)$(foo) -$(foo) prog.$(foo)
```

can be used to compile prog.c source file.

#### Environment Variables

One question here:

**Can GNU Make reference the Variables from Environment?**

According to GNU documentation:

> Variables in ```make``` can come from the environment in which ```make``` is run. Every environment variable that make sees when it starts up is transformed into a ```make``` variable with the same name and value. However, an explicit assignment in the makefile, or with a command argument, overrides the environment.

For example:

```
# In shell environment
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make$ export MY_USER_NAME=$(whoami)
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make$ echo $MY_USER_NAME
ncmv

# In Makefile
my_target : 
	@echo $(MY_USER_NAME)

# Make execution
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make$ make
ncmv
```

Remember that when using environment variables, they should be exported in the shell before invoking GNU Make.

#### Automatic Variables

Automatic variables are predefined variables that hold specific values based on the context of the rule being executed. Their values are generated by Make, rather than having to be set explicitly.

- $@ - Represents the target file name.
- $< - Represents the name of the first prerequisite.
- $^ - Represents the names of all the prerequisites, with duplicates removed.
- $? - Represents the names of all prerequisites that are newer than the target (require to be rebuilt).

Suppose we have a Makefile as below:

```
libs : a.so b.so c.so
	echo "Target name: ", $@
	echo "First prerequisite: ", $<
	echo "Set of prerequisites: ", $^
	echo "To-be-rebuilt prerequisites: ", $?

a.so : 
	touch a.so

b.so : 
	touch b.so

c.so : 
	touch c.so

clean : 
	rm -rf *.so

.PHONY : libs clean
```

Check the output of this sample Makefile for clarification:

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make$ make
echo "Target name: ", libs
Target name: , libs
echo "First prerequisite: ", a.so
First prerequisite: , a.so
echo "Set of prerequisites: ", a.so b.so c.so
Set of prerequisites: , a.so b.so c.so
echo "To-be-rebuilt prerequisites: ", a.so b.so c.so
To-be-rebuilt prerequisites: , a.so b.so c.so
```

These automatic variables make our Makefile rules more flexible and easier to manage by letting us refer to the correct file names and prerequisites dynamically. For example:

```
program : main.o simple_math.o simple_algo.o
	g++ $^ -o $@

main.o : main.cpp utils.h
	g++ -c $<

simple_math.o : simple_math.cpp
	g++ -c $^

simple_algo.o : simple_algo.cpp
	g++ -c $^
```

## Advanced Makefile Concepts

### Wildcards

In a Makefile, wildcards are special characters used to represent a pattern of string or filenames. They are particularly useful for tasks like file manipulation. 

The two most commonly used wildcards in Makefiles are ```*``` (asterisk) and ```%``` (percent sign).

You already saw the use of ```*``` wildcards in the previous sections, remember that? It is often used in the target 'clean'.

```
clean:
	rm -rf *.o
```

The asterisk wildcards matches any sequence of characters (including none) within a filename. For example, ```*.cpp``` matches any CPP file in the directory.

The wildcards are automatically expanded by Make when they are being used in targets and prerequisites. In the recipes, the wildcards are handled by the Shell. In other contexts, wildcards expansion only work with the ```wildcard``` function. (See more details about [Functions](#functions) in later topic)

The example below shows that using wildcards in prerequisites are quite useful.

```
dump: *.h
    echo "dump target manages all the header files: $^"
```

Now, try to use wildcards expansion in variable declaration:

```
OBJS = *.o

program : $(OBJS)
	echo "All object files: $^"

*.o : 
	@touch a.o b.o c.o
```

And it does not work. We expect all the object files output on console, but the actual result shows just the exact string '*.o', the wildcards is not expanded.

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make$ make
touch a.o b.o c.o
echo "All object files: *.o"
All object files: *.o
```

As I mention above, it is suggested using ```wildcard``` function in this context.

```
OBJS = $(wildcard *.o)

program : $(OBJS)
	echo "All object files: $^"

*.o : 
	@touch a.o b.o c.o
```

And here it is:

```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Make$ make
echo "All object files: a.o b.o c.o"
All object files: a.o b.o c.o
```

See more details about [The wildcard Function](#the-wildcard-function).

The wildcard ```%``` is known as a pattern rule wildcard. It is particularly used as a placeholder for matching multiple characters within a target or prerequisite.

```
%.o : %.cpp
	g++ -c $< -o $@
```

In this rule, when Make needs to build a '.o' file, it will search for a corresponding '.cpp' file based on the pattern. Here, the wildcards ```%``` could represent any string of characters. Therefore, if there are CPP files like 'foo.cpp', 'bar.cpp', 'baz.cpp', ... in the current directory, this rule will match all of them. When Make needs to build 'foo.o', it will look for the 'foo.cpp' file, same for other '.o' files. The above pattern after expanding by Make is equivalent to:

```
foo.o : foo.cpp
	g++ -c foo.cpp -o foo.o

bar.o : bar.cpp
	g++ -c bar.cpp -o bar.o

baz.o : baz.cpp
	g++ -c baz.cpp -o baz.o
```

Each file matching with the placeholder pattern will be substituted in the same rule, they all have a common build recipe.

This wildcard character is useful for creating generic rules that can be applied to multiple targets or dependencies with similar patterns. (See [Static Pattern rules](#static-pattern-rules) and [Pattern rules](#pattern-rules))

**What is the difference between ```*``` and ```%``` wildcards again?**

The ```*``` (asterisk) is a Shell wildcard character, not specific to Makefile. This means that the wildcard ```*``` is typically used when invoking shell commands within Makefile recipe. For other context, it requires to use ```wildcard``` function to expand the match result.

The ```%``` is particularly used as placeholders in the targets or prerequisites to create Pattern rules.

### Implicit rules

Implicit rules make things complex and confusing, but we need to know them because they are standards in Makefile.

Implicit rules are predefined rules that helps to write shorter Makefiles, we don't need to specify all the details but Make will understand them implicitly. To allow Make to apply an implicit rule to build a target, all we need is to refrain from supplying the details of the recipe. By that, Make will automatically determine the most suitable way to update the target.

For example, in C compilation, files with the .c extension are typically compiled into object files with the .o extension. Consider the following Makefile:

```
program : foo.o bar.o
	gcc $(CFLAGS) foo.o bar.o $(LDFLAGS) -o program
```

In this Makefile, we mention foo.o as a prerequisite but don't provide a specific rule for it. Make will automatically look for a proper implicit rule to update it. What implicit rule could be?

Here, Make might say: "If I have a file named foo.c, I can build a foo.o object file." And then looking for the file foo.c in the current directory. If foo.c file exists, a basic and common recipe to compile .c file is applied.

```
gcc -c $(CFLAGS) foo.c -o foo.o
```

Of course, when we write a Makefile using Implicit rules, we must known which implicit rule we want Make to use, and known exactly it will choose the correct one. Let me provide a catalogue of built-in implicit rules in the next section.

#### Built-in Implicit Rules

Here are a few common built-in implicit rules that can save you time and effort in writing Makefile:

**Compiling C programs**

A <filename>.o object file is made automatically from a <filename>.c source file, with a rule as below:

```
<filename>.o : <filename>.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $^ -o $@
```

**Compiling C++ programs**

A <filename>.o object file is made automatically from a <filename>.cpp source file, with a rule as below:

```
<filename>.o : <filename>.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $^ -o $@
```

**Linking a single object file**

A <filename> is made automatically from <filename>.o by executing the recipe:

```
<filename> : <filename>.o
	$(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@
```

This rule can be applied for a single program made up by a single source file. But it is possible to be applied for the program made up by multiple object files, if one of them matches the executable file. For example:

```
<filename> : foo.o bar.o
```

When all <filename>.c, foo.c and bar.c files exist, Make will execute a recipe like:

```
$(CC) -c $(CPPFLAGS) $(CFLAGS) foo.c -o foo.o
$(CC) -c $(CPPFLAGS) $(CFLAGS) bar.c -o bar.o
$(CC) -c $(CPPFLAGS) $(CFLAGS) <filename>.c -o <filename>.o
$(CC) $(LDFLAGS) foo.o bar.o <filename>.o $(LOADLIBES) $(LDLIBS) -o <filename>
rm -f foo.o
rm -f bar.o
rm -f <filename>.o
```

Note that these rules are available in the POSIX-based operating systems. We may have different implicit rules in other operating systems like Windows, OS/2,... These rules are already there and are automatically used by Make for targets that don't have a recipe or prerequisites that are not targeted by any rule, unless they are explicitly overridden or disabled in the Makefile.

We can override the built-in implicit rules by defining a new pattern rule (see [Pattern Rules](#pattern-rules)) with the same target and prerequisites, but different recipe. This will replace the default implicit rules with the new pattern rules.

Alternatively, we can disable a default implicit rule by defining a pattern rule with the same target and prerequisites, but no recipe. For example:

```
%.o : %.cpp
```

The above pattern rule would disable the implicit rule that performs C++ compilation.

By using ```-r``` or ```--no-builtin-rules``` option, all the predefined implicit rules are cancelled. This means that Make won't search implicit rules for the targets that don't have a recipe or prerequisites that have no target anymore. Instead, we have to define our own rules or fully and explicitly define targets and recipes for all component of the program.

```
make -r
#or
make --no-builtin-rules
```

Or add the option in Makefile:

```
MAKEFLAGS += -r
#or
MAKEFLAGS += --no-builtin-rules
```

#### Variables used by Implicit Rules

There are some variables appear in the built-in implicit rules. We can modify their values in the Makefile or arguments to ```make``` command to alter how the built-in implicit rules work without redefining the rules themselves.

Here are a few common built-in variables for C/C++ compilation:

**CC** - Program for compiling C programs; default ‘cc’.

**CXX** - Program for compiling C++ programs; default ‘g++’.

**CFLAGS** - Extra flags to give to the C compiler. For example:

```
CFLAGS := -Wall -Wextra -O2
```

**CXXFLAGS** - Extra flags to give to the C++ compiler. For example:

```
CXXFLAGS := -Wall -Wextra -O2
```

**CPPFLAGS** - Extra flags to give to the C preprocessor. For example:

```
CPPFLAGS := -I./include -DENABLE_DEBUGGING
```

**LDFLAGS** - Extra flags to give to compilers when they are supposed to invoke the linker. For example:

```
LDFLAGS := -L./lib -lmylib
```

To override an implicit variable, we can simply assign a new value to it in our Makefile. This new value will be used instead of the default value provided by Make. For example, if we want to change the default compiler, we can do:

```
CC = gcc
```

On the other hand, to disable an implicit variable, we can simply leave it empty or unset it in our Makefile. This tells Make not to use the default value for that variable. For example, if we want to disable the default linker flags, we can do:

```
LDFLAGS =
```

This will disable the default linker flags provided by Make.

#### Practice Implicit Rules

Knowing this, we can now create a Makefile to build a C++ program without explicitly telling Make how to do the compilation. Check the below sample Makefile which is applied for the sample project: [GNU_Make/SampleProjects/02_MultipleSourceFiles](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/GNU_Make/SampleProjects/02_MultipleSourceFiles)

```
CXXFLAGS = -g -Wall -std=c++11 -O2
OBJECTS = main.o simple_algo.o simple_math.o

main: $(OBJECTS)
	$(CXX) $^ -o $@

clean:
	@rm -f main $(OBJECTS)

.PHONY: clean
```

Shorter than before, right?

### Pattern rules

In Makefile, a pattern rule defines how to build a target that matches a certain pattern. It contains the wildcard character ```%``` in the target for matching any non-empty substring. For other parts of a pattern rule, it looks the same with a normal rule. For example:

```
%.o : %.cpp
	$(CXX) -c $^ -o $@
```

This rule states that any file ending with '.o' extension can be built from a corresponding file ending with '.cpp' extension, like a 'foo.o' object file is depending on a 'foo.cpp' source code file, a 'bar.o' object file is depending on a 'bar.cpp' source code file, and they are both built by the same recipe.

```
SRC_DIR = ./src
BUILD_DIR = ./build

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

OBJECT_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

program : $(OBJECT_FILES)

all : program

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $^ -o $@

clean :
	rm -rf $(BUILD_DIR)

.PHONY : all clean
```

This Makefile tells us that it looks for all the source files in './src' directory. These source files will be compiled into their corresponding object files and stored in the ./build directory. We will how the pattern substitution function (patsubst) works later in the [Functions](#functions) section.

So, Pattern rules use a single target and a single prerequisite containing the wildcard ```%``` for applying the build recipe on each file that matches with the pattern.

### Static Pattern rules

GNU Make gives a confusing explanation about Static Pattern Rules concept.

>Static pattern rules are rules which specify multiple targets and construct the prerequisite names for each target based on the target name. They are more general than ordinary rules with multiple targets because the targets do not have to have identical prerequisites. Their prerequisites must be analogous, but not necessarily identical.

Let us think about it a simple way: Static Pattern Rules are another way to write less Makefile content, by defining a pattern for building multiple targets using a common recipe.

Wait. Sound like the description of [Pattern Rules](#pattern-rules) we just read from the above section?

Almost the same, because the Static Pattern Rules extend the concept of Pattern Rules. Look at the syntax:

```
targets ... : target-pattern : prerequisite-patterns ...
	recipe
```

Here, targets is a list of target files, target-pattern is the pattern that matches the targets, and prerequisite-patterns are the patterns that match the prerequisite files. And the recipe is the set of commands or action to be done on each target.

For example, suppose we have the source files 'foo.cpp', 'bar.cpp', and 'baz.cpp' in the current directory. We can use a static pattern rule to build all of them by using a common recipe as below:

```
OBJECT_FILES = foo.o bar.o baz.o

$(OBJECT_FILES) : %.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
```

If we remove the 'targets' part in Static Pattern Rules, it becomes the Pattern Rules which defines the common build recipe for all the target files matched the pattern. But in Static Pattern Rules, we specify a list of target files that will use a specific pattern rule. With this feature, we can define more pattern rules for different target files.

### Conditional

#### Conditional Variable Assignment

We have studied 2 basic types of variable assignment before: [Simply Expanded Variable Assignment](#simply-expanded-variable-assignment) and [Recursively Expanded Variable Assignment](#recursively-expanded-variable-assignment)

The Conditional variable assignment allows you to set a default value for a variable but only if it is not already defined. Here is the syntax:

```
variable ?= value
```

This assignment states that if the variable is not yet defined, value will be assigned to variable.

```
variable = existing_value
variable ?= new_value
```

In this case, since the variable variable is already defined with the value existing_value, the conditional assignment ```variable ?= new_value``` does not overwrite the existing value. The variable variable will retain its original value of existing_value.

#### Conditional statements

Conditional directives in Makefile allows us to define the sections of code that are executed based on certain conditions.

Here are the syntax of conditional statements used in Makefile:

```
conditional-directive
	commands if true
endif

conditional-directive
	commands if true
else
	commands if false
endif

conditional-directive-one
	commands if true
else conditional-directive-two
	commands if true
else conditional-directive-three
	commands if true
else
	commands if all false
endif
```

There can be many ```else``` clause as necessary.

There are four different directives that test different conditions.

**ifeq** Check if two values after expanding all variables are equal.

```
ifeq (arg1, arg2)
ifeq 'arg1' 'arg2'
ifeq "arg1" "arg2"
ifeq "arg1" 'arg2'
ifeq 'arg1' "arg2"
```

For example:

```
DEBUG := 1

ifeq ($(DEBUG), 1)
	CFLAGS := -g -Wall
else
	CFLAGS := -O2
endif
```

**ifneq** Check if two values after expanding all variables are not equal.

```
ifneq (arg1, arg2)
ifneq 'arg1' 'arg2'
ifneq "arg1" "arg2"
ifneq "arg1" 'arg2'
ifneq 'arg1' "arg2"
```

For example:

```
ifneq ($(TARGET), myprogram)
    $(error Invalid target specified)
endif
```

**ifdef** Check if a variable has been defined.

```
ifdef DEBUG
    CFLAGS += -g -DDEBUG_MODE
endif
```

**ifndef** Check if a variable has not been defined.

```
ifndef OS
    OS := $(shell uname)
endif
```

### Functions

#### Function call syntax

#### Functions for String Substitution

#### The wildcard Function

Even when Make automatically deals with wildcards at several places in Makefile, it is suggested that always wrap them in the ```wildcard``` function.

```
$(wildcard <string_contains_wildcards>)
```

We can use wildcard function for wildcards expansion anywhere in a Makefile. If no existing file name matches a pattern, ```wildcard``` function returns an empty result.

Some of the common use case of wildcards:

```
# Capture all .cpp files
CXXFILES := $(wildcard *.cpp)

# Convert .cpp filenames to .o filenames
OBJS := $(patsubst %.cpp,%.o,$(CXXFILES))

# Compiler options
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++11

# Target executable
TARGET := my_program

# Rule to build the target executable
$(TARGET): $(OBJS)
    $(CXX) $(CXXFLAGS) $^ -o $@

# Rule to compile each .cpp file into a .o file
%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

# Phony target to clean up generated files
.PHONY: clean
clean:
    rm -f $(OBJS) $(TARGET)
```

#### The foreach Function

#### The eval Function

#### The call Function

## Conclusion

After exploring the GNU Make tool, It is clear that GNU Make is a powerful tool for automating the process of building software projects. With GNU Make, managing large projects with multiple files becomes more efficient and less time-consuming.

To truly grasp the concepts behind GNU Make and how it is used in C/C++ programming, it is crucial to gain practical experience with a sample project:

[GNU_Make/SampleProjects/03_LocationService](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/GNU_Make/SampleProjects/03_LocationService)

Consider compiling the jsoncpp and nmeaparser libraries as shared objects, and link them to the main binary. Try to create your Makefiles first, before looking for a [Solution](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/blob/master/GNU_Make/SampleProjects/03_LocationService/Makefile).

----
**References:**

https://www.gnu.org/software/make/manual/make.html

https://makefiletutorial.com/

https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile

https://blog.jgc.org/2013/02/updated-list-of-my-gnu-make-articles.html
