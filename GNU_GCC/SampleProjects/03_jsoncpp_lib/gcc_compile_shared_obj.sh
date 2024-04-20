#!/bin/bash

g++ -c -w -std=c++11 -fPIC ./src/*.cpp -I./include
g++ -shared json_reader.o json_value.o json_writer.o -o libjsoncpp.so
mv libjsoncpp.* ./build
rm -rf *.o