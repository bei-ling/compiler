
cmake_minimum_required(VERSION 2.8.12)

project (c_compiler)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/compile")
include(cotire)

add_subdirectory(src)
