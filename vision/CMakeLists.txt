cmake_minimum_required(VERSION 2.8)

project(Vision)

find_package(OpenCV REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SRC1
${PROJECT_SOURCE_DIR}/src/record_video.cpp)

set(SRC2
${PROJECT_SOURCE_DIR}/src/save_video_images.cpp)

set(SRC3
${PROJECT_SOURCE_DIR}/src/record_fisheye.cpp)

set(SRC4
${PROJECT_SOURCE_DIR}/src/record_triple_videos.cpp)

set(SRC5
${PROJECT_SOURCE_DIR}/src/select_video_images.cpp)

set(SRC6
${PROJECT_SOURCE_DIR}/src/calibrate_fisheye.cpp)

set(SRC7
${PROJECT_SOURCE_DIR}/src/undistort_fisheye_viewer.cpp)

set(SRC8
${PROJECT_SOURCE_DIR}/src/undistort_fisheye_image.cpp)

#set(SRC9
#${PROJECT_SOURCE_DIR}/src/fisheye.cpp)

add_executable(recordVideo ${SRC1})
target_link_libraries(recordVideo ${OpenCV_LIBS})

add_executable(saveVideoImages ${SRC2})
target_link_libraries(saveVideoImages ${OpenCV_LIBS})

add_executable(recordFisheye ${SRC3})
target_link_libraries(recordFisheye ${OpenCV_LIBS})

add_executable(recordTripleVideos ${SRC4})
target_link_libraries(recordTripleVideos ${OpenCV_LIBS})

add_executable(selectVideoImages ${SRC5})
target_link_libraries(selectVideoImages ${OpenCV_LIBS})

add_executable(calibrateFisheye ${SRC6})
target_link_libraries(calibrateFisheye ${OpenCV_LIBS})

add_executable(undistortFisheyeViewer ${SRC7})
target_link_libraries(undistortFisheyeViewer ${OpenCV_LIBS})

add_executable(undistortFisheyeImage ${SRC8})
target_link_libraries(undistortFisheyeImage ${OpenCV_LIBS})

#add_executable(testFisheye ${SRC9})
#target_link_libraries(testFisheye ${OpenCV_LIBS})
