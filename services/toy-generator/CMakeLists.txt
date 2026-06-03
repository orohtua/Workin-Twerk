cmake_minimum_required(VERSION 3.10)
project(WatermarkApp)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(watermark watermark.cpp)
target_link_libraries(watermark ${OpenCV_LIBS})
