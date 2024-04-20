#!/bin/bash

if [ $# -eq 0 ]; then
    # No argument provided, compile the C++ program
    g++ \
        -std=c++11 \
        main.cpp \
        -I./../include \
        -L./../build \
        -o main

elif [ "$1" = "clean" ]; then
    # Argument is "clean", perform clean operation
    rm -f main.o main
    echo "Clean operation complete"
else
    echo "Unknown argument"
fi