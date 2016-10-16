cmake_minimum_required(VERSION 2.8)
add_definitions(-std=c++0x)
project(VisionTools)

find_package(OpenCV REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(/home/shaohua/Workspace/Tools/io/system/include)

add_executable(record_video ${SRC} src/record_video.cpp)
target_link_libraries(record_video ${OpenCV_LIBS})

add_executable(record_images ${SRC} src/record_images.cpp)
target_link_libraries(record_images ${OpenCV_LIBS})

add_executable(select_images ${SRC} src/select_images.cpp)
target_link_libraries(select_images ${OpenCV_LIBS})

add_executable(calibrate_fisheye ${SRC} src/calibrate_fisheye.cpp
		/home/shaohua/Workspace/Tools/io/system/src/directory.cpp)
target_link_libraries(calibrate_fisheye ${OpenCV_LIBS})

add_executable(record_fisheye_dist_images ${SRC} src/record_fisheye_dist_images.cpp)
target_link_libraries(record_fisheye_dist_images ${OpenCV_LIBS})

add_executable(record_fisheye_undist_images ${SRC} src/record_fisheye_undist_images.cpp)
target_link_libraries(record_fisheye_undist_images ${OpenCV_LIBS})
