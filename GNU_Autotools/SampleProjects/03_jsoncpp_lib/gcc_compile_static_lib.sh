g++ -c -I./include src/json_reader.cpp src/json_value.cpp src/json_writer.cpp
ar rcs libjsoncpp.a json_reader.o json_value.o json_writer.o
