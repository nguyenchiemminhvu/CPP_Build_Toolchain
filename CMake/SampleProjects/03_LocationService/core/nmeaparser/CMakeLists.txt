cmake_minimum_required(VERSION 3.10)
project(LibNmea VERSION 1.0 LANGUAGES C CXX)

file(GLOB NMEA_PARSER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(nmeaparser SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/context.cpp)

target_sources(nmeaparser PRIVATE ${NMEA_PARSER_SOURCES})

target_include_directories(nmeaparser
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)