## Introduction

In the vision of creating a complete free and open-source software ecosystem, led by Richard Stallman, after the creation of the GNU GCC Compiler in 1987, the GNU Project released GNU Make in 1988.

The GNU GCC Compiler was a great accomplishment as it provided a free and powerful tool to compile code. However, GNU Project realized that building software is not just all about compiling code. Imagine you have a big project that consists of multiple files, like source code files, libraries, and other resources.

![](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/blob/master/GNU_Make/MultipleDependencies.png?raw=true)

Now, building that project means taking all these pieces and putting them together in the right order to create the final executable file.

GNU Make was created with the primary purpose that is to automate the build process by managing the compilation and linking of source files.

With GNU Make, we define a set of rules that describe how to build the project. These rules specify the dependencies between files, and the commands needed to compile them.

In the early days of software development, programmers had to manually compile and link their code every time they made a change. It cost even more time and effort when the source code structure of their project has changed. GNU Make simplifies this process by automatically figuring out which files need to be recompiled based on their dependencies. This approach also reduces the chances of re-linking process when the source code structure has changed.

