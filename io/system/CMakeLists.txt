cmake_minimum_required(VERSION 2.8)
project(system_io)
add_definitions(-std=c++0x)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SRC
${PROJECT_SOURCE_DIR}/src/directory.cpp)

add_subdirectory(${PROJECT_SOURCE_DIR}/tests)
