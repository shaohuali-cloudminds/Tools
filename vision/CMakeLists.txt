cmake_minimum_required(VERSION 2.8)
add_definitions(-std=c++0x)
project(VisionTools)

find_package(OpenCV REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SRC
${PROJECT_SOURCE_DIR}/src/fisheye.cpp
${PROJECT_SOURCE_DIR}/src/camera.cpp)

add_subdirectory(${PROJECT_SOURCE_DIR}/tools)
add_subdirectory(${PROJECT_SOURCE_DIR}/tests)
