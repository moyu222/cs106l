cmake_minimum_required(VERSION 3.16)
project(lecture08 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 添加源文件
add_executable(lecture08
        main.cpp
        StudentID.cpp
        IntVector.cpp
)
