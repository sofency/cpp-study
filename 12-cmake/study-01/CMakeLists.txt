cmake_minimum_required(VERSION 3.20)
project(study-01)

# 设置C++最低版本
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# 找到所有的cpp文件
file(GLOB SRC_LIST ${PROJECT_SOURCE_DIR}/src/*.cpp)

# 设置命令生成位置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)


# 可以执行文件 Main是最终生成的文件 main.cpp是main函数所在的位置
add_executable(Main main.cpp ${SRC_LIST})

target_include_directories(Main PUBLIC "${PROJECT_SOURCE_DIR}/include")


