cmake_minimum_required(VERSION 3.5.0)
project(src VERSION 0.1.0 LANGUAGES C CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/iqmath)

set(APP_SRC main.cpp)

add_executable(hello ${APP_SRC})
target_link_libraries(hello iqmath)