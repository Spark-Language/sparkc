cmake_minimum_required(VERSION 3.31)
project(sparkc)

set(CMAKE_CXX_STANDARD 20)

add_executable(sparkc src/main.cpp
        src/tokens/TokenDef.cpp
        include/tokens/TokenDef.h)
