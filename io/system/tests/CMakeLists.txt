cmake_minimum_required(VERSION 2.8)
project(system_io)
add_definitions(-std=c++0x)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(test_system_directory ${SRC} src/test_directory.cpp)
