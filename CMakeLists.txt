cmake_minimum_required(VERSION 3.31)
project(sparkc)

set(CMAKE_CXX_STANDARD 20)

add_executable(sparkc src/main.cpp
        src/tokens/TokenType.cpp
        include/tokens/TokenType.h
        src/tokens/TokenCategory.cpp
        include/tokens/TokenCategory.h)
