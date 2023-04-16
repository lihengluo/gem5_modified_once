cmake_minimum_required(VERSION 3.16)

project(merkle_tree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Werror")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#找到目录下所有.cc文件，放到SOURCES变量中
file(GLOB_RECURSE SOURCES "*.cpp")
#file(GLOB_RECURSE HEADERS "*.h")

#添加头文件目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cpp)

#添加库
#要不要shared有区别吗
add_library(${PROJECT_NAME}  ${SOURCES})
