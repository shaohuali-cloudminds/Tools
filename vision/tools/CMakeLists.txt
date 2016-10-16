cmake_minimum_required(VERSION 2.8)
add_definitions(-std=c++0x)
project(VisionTools)

find_package(OpenCV REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(record_video ${SRC} src/record_video.cpp)
target_link_libraries(record_video ${OpenCV_LIBS})

add_executable(record_images ${SRC} src/record_images.cpp)
target_link_libraries(record_images ${OpenCV_LIBS})

add_executable(select_images ${SRC} src/select_images.cpp)
target_link_libraries(select_images ${OpenCV_LIBS})
