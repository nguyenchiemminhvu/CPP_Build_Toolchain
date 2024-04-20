#!/bin/bash

g++ -c -w -std=c++11 ./src/*.cpp -I./include
ar rcs libjsoncpp.a json_reader.o json_value.o json_writer.o
mv libjsoncpp.a ./build
ranlib ./build/libjsoncpp.a
rm -rf *.o