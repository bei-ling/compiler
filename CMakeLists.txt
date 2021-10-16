
cmake_minimum_required(VERSION 3.10)
# set (CMAKE_C_COMPILER "/usr/bin/clang-10")
# set (CMAKE_CXX_COMPILER "/usr/bin/clang++-10")

set (CMAKE_C_COMPILER "/usr/bin/gcc")
set (CMAKE_CXX_COMPILER "/usr/bin/g++")

set (PROJECT_NAME "c_compiler")
project (${PROJECT_NAME})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")


set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

# set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/compile")
# include(cotire)

add_subdirectory(src)


add_custom_target(graphviz ALL
    COMMAND ${CMAKE_COMMAND} "--graphviz=foo.dot" .
    COMMAND dot -Tpng foo.dot -o foo.png
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")