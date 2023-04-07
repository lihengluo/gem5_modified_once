cmake_minimum_required(VERSION 3.24)
project(projects)

set(CMAKE_CXX_STANDARD 17)

add_executable(projects main.cpp node.h sha256.h tree.h)
