
cmake_minimum_required(VERSION 3.10)
set (CMAKE_C_COMPILER "/usr/bin/clang-9")
set (CMAKE_CXX_COMPILER "/usr/bin/clang++-9")

set (PROJECT_NAME "c_compiler")
project (${PROJECT_NAME})

set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")


set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -O1 -ftime-trace")

# set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/compile")
# include(cotire)

add_subdirectory(src)