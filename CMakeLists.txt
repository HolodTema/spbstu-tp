cmake_minimum_required(VERSION 3.25)
project(t2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(t2 main.cpp
        DataStruct.cpp
        DataStruct.h
        StreamGuard.h)
