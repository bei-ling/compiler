
cmake_minimum_required(VERSION 3.10)

set (CMAKE_C_COMPILER "/usr/bin/gcc")
set (CMAKE_CXX_COMPILER "/usr/bin/g++")

set (PROJECT_NAME "c_compiler.exe")
project (${PROJECT_NAME})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/target)
add_subdirectory(src)
