cmake_minimum_required(VERSION 3.6)
project(matrix)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c98")

set(SOURCE_FILES main.c mul_m.c mul_m.h)
add_executable(matrix ${SOURCE_FILES})