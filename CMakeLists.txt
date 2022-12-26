cmake_minimum_required(VERSION 3.20)
project(snake)

#find_package(SDL2 REQUIRED)
#include_directories(snake ${SDL2_INCLUDE_DIRS})
#massage(INFO ${SDL2_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 23)

#find graphic lib
find_package(SFML 2.5.1 COMPONENTS graphics window REQUIRED)
add_executable(snake main.cpp snake_context.h SNAKE.cpp Snake.h Game.cpp Game.h)
#target_link_libraries(snake ${SDL2_LIBRARIES})
target_link_libraries(snake PUBLIC sfml-graphics sfml-window sfml-audio)

set(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

SET(CMAKE_CXX_FLAGS -pthread)