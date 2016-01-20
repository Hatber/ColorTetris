cmake_minimum_required(VERSION 3.3)
project(ColorTetris)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(PATH_TO_LIBTCOD /home/andrew/lib/libtcod)
set(LIBTCOD_HEADERS ${PATH_TO_LIBTCOD}/headers)
set(LIBTCOD_LIBRARY ${PATH_TO_LIBTCOD}/)

include_directories(${LIBTCOD_HEADERS})
link_directories(${LIBTCOD_LIBRARY})

include_directories("src/")

set(SOURCE_FILES main.cpp src/Engine/ColorTetris.cpp src/GameController.cpp src/Render.cpp
        src/GameBot/RandomBot.cpp src/GameBot/BruteForceBot.cpp)
add_executable(ColorTetris ${SOURCE_FILES})

target_link_libraries(ColorTetris -ltcodxx -ltcod)

execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/res/tileSet.png ${CMAKE_BINARY_DIR}/terminal.png
)