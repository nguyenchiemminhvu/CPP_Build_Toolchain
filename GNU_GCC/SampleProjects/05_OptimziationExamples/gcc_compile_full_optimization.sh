#!/bin/bash

if [ $# -eq 0 ]; then
    # No argument provided, compile the C++ program
    g++ -O3 -S main.cpp -o main.s
    objdump -d main.s > full_optimization.cpp
elif [ "$1" = "clean" ]; then
    # Argument is "clean", perform clean operation
    rm -f main.s full_optimization.cpp
    echo "Clean operation complete"
else
    echo "Unknown argument"
fi