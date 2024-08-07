cmake_minimum_required(VERSION 3.10)
project(SimpleLocationService VERSION 1.0 LANGUAGES C CXX)

file(GLOB subdirlist "${CMAKE_CURRENT_SOURCE_DIR}/core/*")
foreach(subdir ${subdirlist})
    if (IS_DIRECTORY ${subdir} AND EXISTS ${subdir}/CMakeLists.txt)
        message(STATUS "Found CMake target in ${subdir}")
        add_subdirectory(${subdir})
    endif()
endforeach()

add_executable(LocationService main.cpp)

target_sources(LocationService
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/service/LocationService.cpp
)

target_include_directories(LocationService 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/service
)

target_link_libraries(LocationService PRIVATE nmeaparser)