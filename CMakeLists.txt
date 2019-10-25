cmake_minimum_required(VERSION 3.15)
project(tp_hw_2 C)

set(CMAKE_C_STANDARD 99)

add_executable(tp_hw_2 main.c static_lib/static_lib.c static_lib/static_lib.h dynamic_lib/dynamic_lib.cpp dynamic_lib/dynamic_lib.h)