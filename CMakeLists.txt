cmake_minimum_required(VERSION 4.2)
project(typed_rows)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(typed_rows
        Line.cpp
        Line.h
        TextStorage.cpp
        TextStorage.h
        CipherManager.cpp
        CipherManager.h
        main.cpp
)
