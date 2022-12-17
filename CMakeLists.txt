cmake_minimum_required(VERSION 3.24)
project(DFS)

set(CMAKE_CXX_STANDARD 11)

add_executable(DFS main.cpp bst.h)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")