#!/bin/bash

if [ $# -eq 0 ]; then
    # No argument provided, compile the C++ program
    cd ./opensource/simplecrypto
    source gcc_compile_shared_obj.sh
    source gcc_compile_shared_obj.sh install
    source gcc_compile_shared_obj.sh clean
    cd ./../../

    g++ -o main \
        -std=c++11 \
        -I./opensource/include \
        -L./opensource/lib \
        -lsimplecrypto \
        simple_math.cpp \
        simple_algo.cpp \
        main.cpp
elif [ "$1" = "clean" ]; then
    # Argument is "clean", perform clean operation
    rm -f simple_math.o simple_algo.o main.o main
    echo "Clean operation complete"
else
    echo "Unknown argument"
fi