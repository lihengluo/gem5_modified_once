cmake_minimum_required(VERSION 3.24)
project(llh)

set(CMAKE_CXX_STANDARD 17)

add_executable(llh main.cpp
        node.h sha256.h tree.h node.cpp tree.cpp forest.h forest.cpp test.h MMT_root.h)
