#!/bin/bash

if [ $# -eq 0 ]; then
    g++ -c md5.c tea.c
    
    # Check the operating system
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        # Linux
        g++ -shared -fPIC -o libsimplecrypto.so md5.o tea.o
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        # macOS
        g++ -dynamiclib -o libsimplecrypto.dylib md5.o tea.o
    else
        echo "Unsupported operating system!"
    fi
elif [ "$1" = "install" ]; then
    cp -rf simplecrypto.h ./../include
    cp -rf libsimplecrypto.* ./../lib
elif [ "$1" = "clean" ]; then
    # Argument is "clean", perform clean operation
    rm -f md5.o tea.o libsimplecrypto.*
    echo "Clean operation complete"
else
    echo "Unknown argument"
fi