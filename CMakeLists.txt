cmake_minimum_required(VERSION 3.3)
project(ColorTetris)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories("src/")

set(SOURCE_FILES main.cpp src/Engine/Board.cpp src/Engine/ColorTetris.cpp src/GameController.cpp src/Render.cpp)
add_executable(ColorTetris ${SOURCE_FILES})