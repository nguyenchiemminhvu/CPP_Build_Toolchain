cmake_minimum_required(VERSION 3.10)
project(Utility VERSION 1.0 DESCRIPTION "Simple utility features" LANGUAGES C CXX)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/opensource)

add_executable(utility main.cpp)

target_sources(
    utility
    PRIVATE
        simple_algo.cpp
        simple_math.cpp
)

target_include_directories(
    utility
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/opensource/jsoncpp/include
)

target_link_libraries(utility PRIVATE jsoncpp)