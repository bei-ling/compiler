add_executable(c_compiler main.cpp pch.h test1.h test2.h test3.h test4.h)
# issue: https://github.com/sakra/cotire/issues/17

set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (COTIRE_MINIMUM_NUMBER_OF_TARGET_SOURCES 1)
set_target_properties(c_compiler PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "pch.h")

get_target_property(_prefixHeader c_compiler COTIRE_CXX_PREFIX_HEADER)
get_target_property(_precompiledHeader c_compiler COTIRE_CXX_PRECOMPILED_HEADER)
cotire(c_compiler)
if (_prefixHeader)
	message(STATUS "example prefix header: ${_prefixHeader}")
endif()
if (_precompiledHeader)
	message(STATUS "example precompiled header: ${_precompiledHeader}")
endif()
