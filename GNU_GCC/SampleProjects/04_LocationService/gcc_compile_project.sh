#!/bin/bash

# Create build directory if it doesn't exist
mkdir -p ./build

# Compile dynamic library NMEA
g++ -c -w -g -std=c++11 -I./core/nmeaparser/include -fPIC ./core/nmeaparser/src/context.cpp -o ./build/context.o
g++ -c -w -g -std=c++11 -I./core/nmeaparser/include -fPIC ./core/nmeaparser/src/generate.cpp -o ./build/generate.o
g++ -c -w -g -std=c++11 -I./core/nmeaparser/include -fPIC ./core/nmeaparser/src/generator.cpp -o ./build/generator.o
g++ -c -w -g -std=c++11 -I./core/nmeaparser/include -fPIC ./core/nmeaparser/src/gmath.cpp -o ./build/gmath.o
g++ -c -w -g -std=c++11 -I./core/nmeaparser/include -fPIC ./core/nmeaparser/src/info.cpp -o ./build/info.o
g++ -c -w -g -std=c++11 -I./core/nmeaparser/include -fPIC ./core/nmeaparser/src/parse.cpp -o ./build/parse.o
g++ -c -w -g -std=c++11 -I./core/nmeaparser/include -fPIC ./core/nmeaparser/src/parser.cpp -o ./build/parser.o
g++ -c -w -g -std=c++11 -I./core/nmeaparser/include -fPIC ./core/nmeaparser/src/sentence.cpp -o ./build/sentence.o
g++ -c -w -g -std=c++11 -I./core/nmeaparser/include -fPIC ./core/nmeaparser/src/time.cpp -o ./build/time.o
g++ -c -w -g -std=c++11 -I./core/nmeaparser/include -fPIC ./core/nmeaparser/src/tok.cpp -o ./build/tok.o
g++ -shared \
    ./build/context.o \
    ./build/generate.o \
    ./build/generator.o \
    ./build/gmath.o \
    ./build/info.o \
    ./build/parse.o \
    ./build/parser.o \
    ./build/sentence.o \
    ./build/time.o \
    ./build/tok.o \
    -o ./build/libnmea.so

# Compile the main program
g++ -c -w -g -std=c++11 -I./core/nmeaparser/include ./service/LocationService.cpp -o ./build/LocationService.o
g++ -c -w -g -std=c++11 -I./core/nmeaparser/include ./main.cpp -o ./build/main.o
g++ -rdynamic \
    -L./build \
    ./build/LocationService.o \
    ./build/main.o \
    -lnmea \
    -o ./build/main

# Clean up the object files
rm -rf ./build/*.o

# Install the shared object to the standard library lookup directories of GNU GCC
sudo cp ./build/libnmea.so /usr/local/lib
sudo ldconfig