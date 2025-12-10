cmake_minimum_required(VERSION 3.16)
project(lecture08 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(assignment4
        main.cpp
        spellcheck.cpp
)