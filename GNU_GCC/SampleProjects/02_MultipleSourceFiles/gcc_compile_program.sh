#!/bin/bash

if [ $# -eq 0 ]; then
    # No argument provided, compile the C++ program
    cd ./opensource/simplecrypto
    source gcc_compile_shared_obj.sh
    source gcc_compile_shared_obj.sh install
    source gcc_compile_shared_obj.sh clean
    cd ./../../

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
