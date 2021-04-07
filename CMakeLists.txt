
cmake_minimum_required(VERSION 2.8.12)

project (c_compiler)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-std=c++11)
    message(STATUS "optional:-std=c++11")   
endif(CMAKE_COMPILER_IS_GNUCXX)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -o3 -ftime-report")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/compile")
include(cotire)

add_subdirectory(src)
