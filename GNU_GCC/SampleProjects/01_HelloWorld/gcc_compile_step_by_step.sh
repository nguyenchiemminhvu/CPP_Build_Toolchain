#!/bin/bash

if [ $# -eq 0 ]; then
    # No argument provided, compile the C++ program
    g++ -E main.cpp -o main.i
    g++ -S main.i -o main.s
    g++ -c main.s -o main.o
    g++ main.o -o main
elif [ "$1" = "clean" ]; then
    # Argument is "clean", perform clean operation
    rm -f main.i main.s main.o main
    echo "Clean operation complete"
else
    echo "Unknown argument"
fi