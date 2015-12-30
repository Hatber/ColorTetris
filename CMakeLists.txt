cmake_minimum_required(VERSION 3.3)
project(ColorTetris)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp src/Board.cpp src/Board.h src/ColorTetris.cpp src/ColorTetris.h src/Figure.h src/GameController.cpp src/GameController.h src/Render.cpp src/Render.h)
add_executable(ColorTetris ${SOURCE_FILES})