cmake_minimum_required(VERSION 3.10)

project(ASCII_artist)

set(OpenCV_DIR D:/Libs/opencv/build)
# Add your own path to <your_path>/opencv/build

find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})