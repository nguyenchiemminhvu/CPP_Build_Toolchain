## Introduction

In the vision of creating a complete free and open-source software ecosystem, led by Richard Stallman, after the creation of the GNU GCC Compiler in 1987, the GNU Project released GNU Make in 1988.

The GNU GCC Compiler was a great accomplishment as it provided a free and powerful tool to compile code. However, the GNU GCC alone may have some limitations.

Imagine you have a big project that consists of multiple files, like source code files, libraries, and other resources.

![](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/blob/master/GNU_Make/MultipleDependencies.png?raw=true)

Now, building that project means taking all these pieces and putting them together in the right order to create the final executable file.

In the early days of software development, programmers had to manually compile and link their code every time they made a change. It cost even more time and effort when the source code structure of their project has changed.

This is where GNU Make steps in. GNU Make was created with the primary purpose that is to automate the process of building software by managing dependencies and executing the necessary commands to compile and link the various components.

With GNU Make, we can define a set of rules that describe how to build the project. These rules specify the dependencies between files, and the commands needed to compile them. When the source codes have changed, GNU Make is smart enough to figure out which files need to be recompiled based on their dependencies.