cmake_minimum_required(VERSION 3.13)
project(untitled)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(untitled main.cpp Pokemon.cpp Pokemon.h move.cpp move.h Battle.cpp Battle.h)