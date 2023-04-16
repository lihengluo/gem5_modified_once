cmake_minimum_required(VERSION 3.23)
project(llh_merkle_tree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Werror")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#设置输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

#添加头文件目录
include_directories("${PROJECT_SOURCE_DIR}/src")
#添加子目录（含有CMakeLists.txt）
add_subdirectory(src)
#添加可执行文件
add_executable(${PROJECT_NAME} main.cpp)
#添加链接库
target_link_libraries(${PROJECT_NAME} merkle_tree)
#输出信息
message(${PROJECT_SOURCE_DIR})

#install

#test
