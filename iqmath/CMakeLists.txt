cmake_minimum_required(VERSION 3.5.0)
project(iqmath VERSION 0.1.0 LANGUAGES C CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 禁用异常
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti -std=c++20")

# 收集源文件
file(GLOB SRC "*.c" "*.cpp" "*.cxx")
# 收集头文件
file(GLOB INC "*.h" "*.hpp")

# 添加库
add_library(iqmath STATIC ${SRC})

# 添加包含路径
include_directories(".")