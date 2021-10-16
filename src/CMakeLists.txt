
file(GLOB INC_FILE ${PROJECT_SOURCE_DIR}/inc/*.h)
 
add_executable(${PROJECT_NAME}
	main.cpp
	test.cpp
	${INC_FILE}
)

# cotire
# issue: https://github.com/sakra/cotire/issues/17
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set (COTIRE_MINIMUM_NUMBER_OF_TARGET_SOURCES 1)
# set_target_properties(c_compiler PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "pch.h")

# get_target_property(_prefixHeader c_compiler COTIRE_CXX_PREFIX_HEADER)
# get_target_property(_precompiledHeader c_compiler COTIRE_CXX_PRECOMPILED_HEADER)
# cotire(c_compiler)
# if (_prefixHeader)
# 	message(STATUS "example prefix header: ${_prefixHeader}")
# endif()
# if (_precompiledHeader)
# 	message(STATUS "example precompiled header: ${_precompiledHeader}")
# endif()
