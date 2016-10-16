cmake_minimum_required(VERSION 2.8)
add_definitions(-std=c++0x)
project(VisionTools)

find_package(OpenCV REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(test_camera ${SRC} src/test_camera.cpp)
target_link_libraries(test_camera ${OpenCV_LIBS})

add_executable(test_fisheye ${SRC} src/test_fisheye.cpp)
target_link_libraries(test_fisheye ${OpenCV_LIBS})
