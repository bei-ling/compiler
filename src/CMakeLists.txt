

# function(UNITY_BUILD output_file input_src)
# 	file(WRITE ${CMAKE_BINARY_DIR}/${output_file} "//  ${output_file}\n")
# 	foreach(filename ${input_src})
# 		file(APPEND ${CMAKE_BINARY_DIR}/${output_file} "#include \"${filename}\"\n")
# 	endforeach()
# 	message("Generate unity build file: ${CMAKE_BINARY_DIR}/${output_file}")
# endfunction(UNITY_BUILD)


# # 使用范例
# set(MODULE_SRC
# 	${CMAKE_CURRENT_SOURCE_DIR}/test.cpp
# )
# UNITY_BUILD(module_unity_build.cpp "${MODULE_SRC}")

file(GLOB INC_FILE ${PROJECT_SOURCE_DIR}/inc/*.h)
# message(STATUS ${INC_FILE})
# message(STATUS ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)
# message(STATUS ${INC_FILE})

add_executable(${PROJECT_NAME}
	main.cpp
	test.cpp
	# ${CMAKE_BINARY_DIR}/module_unity_build.cpp
	${INC_FILE}
)

# aux_source_directory(inc CURR_INC)
# add_executable(${PROJECT_NAME} main.cpp test.cpp ${CURR_INC})
# issue: https://github.com/sakra/cotire/issues/17

set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")

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
