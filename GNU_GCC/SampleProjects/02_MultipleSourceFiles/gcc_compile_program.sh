#!/bin/bash

if [ $# -eq 0 ]; then
    # No argument provided, compile the C++ program
    g++ -o main \
        -std=c++11 \
        -I./opensource/include \
        ./opensource/lib/libsimplecrypto.a \
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