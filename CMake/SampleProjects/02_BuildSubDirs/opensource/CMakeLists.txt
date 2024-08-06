cmake_minimum_required(VERSION 3.10)
project(JSONCPP VERSION 1.0 DESCRIPTION "jsoncpp opensource library" LANGUAGES C CXX)

set(JSONCPP_SOURCES SHARED
    jsoncpp/src/json_reader.cpp
    jsoncpp/src/json_value.cpp
    jsoncpp/src/json_writer.cpp
)

add_library(jsoncpp ${JSONCPP_SOURCES})

target_include_directories(jsoncpp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/jsoncpp/include)