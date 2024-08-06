cmake_minimum_required(VERSION 3.10)

project(HelloWorld VERSION 1.0.0 DESCRIPTION "Print HelloWorld on Console" LANGUAGES C CXX)

message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "Project Version: ${PROJECT_VERSION}")
message(STATUS "Project Description: ${PROJECT_DESCRIPTION}")
message(STATUS "Project Source Dir: ${PROJECT_SOURCE_DIR}")
message(STATUS "Project Binary Dir: ${PROJECT_BINARY_DIR}")

add_executable(HelloWorld main.cpp)