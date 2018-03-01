cmake_minimum_required(VERSION 3.9)
project(AI_Assignment)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -framework GLUT -framework OpenGL") # compiler version and compiler flags.

add_executable(AI_Assignment main.cpp)
