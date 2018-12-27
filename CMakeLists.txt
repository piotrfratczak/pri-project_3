cmake_minimum_required(VERSION 3.13)
project(pri_project_3 C)

set(CMAKE_C_STANDARD 11)

add_executable(pri_project_3 main.c utils.c utils.h stack.c stack.h transmitter.c transmitter.h ui.c ui.h fileIO.c fileIO.h userIO.c userIO.h)