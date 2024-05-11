## Introduction

Before exploring Autotools, let's make sure we have a complete understanding of [GNU Make](https://github.com/nguyenchiemminhvu/CPP_Build_Toolchain/tree/master/GNU_Make).

The GNU Autotools, also known as the GNU Build System, is a set of handy software packages including Autoconf, Automake, and Libtool used for building software on different types of Unix-like operating systems (POSIX).

- Autoconf helps create portable scripts to configure source code packages using templates and an M4 macro package.
- Automake helps create portable GNU standards-compiant Makefiles from template files, supporting all the targets documented by the [GNU Coding Standards](https://www.gnu.org/prep/standards/standards.html).
- Libtool helps create and use shared libraries portably.

### Autoconf



```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools$ autoconf --version
autoconf (GNU Autoconf) 2.71
Copyright (C) 2021 Free Software Foundation, Inc.
License GPLv3+/Autoconf: GNU GPL version 3 or later
<https://gnu.org/licenses/gpl.html>, <https://gnu.org/licenses/exceptions.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.

Written by David J. MacKenzie and Akim Demaille.
```

### Automake



```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools$ automake --version
automake (GNU automake) 1.16.5
Copyright (C) 2021 Free Software Foundation, Inc.
License GPLv2+: GNU GPL version 2 or later <https://gnu.org/licenses/gpl-2.0.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.

Written by Tom Tromey <tromey@redhat.com>
       and Alexandre Duret-Lutz <adl@gnu.org>.
```

### Libtool



```
ncmv@localhost:~/study_workspace/CPP_Build_Toolchain/GNU_Autotools$ libtool --version
libtool (GNU libtool) 2.4.6
Written by Gordon Matzigkeit, 1996

Copyright (C) 2014 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

## Practice With Autotools



### Setup Configuration



### Makefile Generation



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