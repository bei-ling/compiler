
cmake_minimum_required(VERSION 2.8.12)
set (CMAKE_C_COMPILER "/usr/bin/clang-9")
set (CMAKE_CXX_COMPILER "/usr/bin/clang++-9")


project (c_compiler)


set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -o3 -ftime-trace")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/compile")
include(cotire)

add_subdirectory(src)
