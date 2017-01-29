cmake_minimum_required(VERSION 2.8.4)

PROJECT(examples)

#Point this to your installation of dlib's cmake
include(/usr/local/Cellar/dlib/19.2/dlib/cmake)

find_package(OpenCV QUIET)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(tracker tracker.cpp)
target_link_libraries(tracker dlib ${OpenCV_LIBS})


