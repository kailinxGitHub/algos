cmake_minimum_required(VERSION 3.28)
project(Sort C)

set(CMAKE_C_STANDARD 11)

add_executable(Sort main.c
        sorts.c
        sorts.h
)
