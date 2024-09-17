cmake_minimum_required(VERSION 3.5.0)
project(demo1 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_C_COMPILER "C:/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/mingw64/bin/g++.exe")

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 禁用异常
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")

# 禁用 RTTI
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

# 显式指定 C++20 标准
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")


aux_source_directory(. SOURCES)
aux_source_directory(iqmath SOURCES)
file(GLOB HEADERS "iqmath/*.h")


# 将iqmath目录添加到包含路径
include_directories(iqmath)
# target_link_libraries(demo1 iqmath)
# 输出收集到的源文件
message(STATUS "Sources in current directory:")
foreach(source_file ${SOURCES})
    message(STATUS "  - ${source_file}")
endforeach()


# 输出收集到的头文件
message(STATUS "Headers in iqmath directory:")
foreach(header_file ${HEADERS})
    message(STATUS "  - ${header_file}")
endforeach()

add_executable(demo1 ${SOURCES})

