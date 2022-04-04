
file(GLOB INC_FILE ${PROJECT_SOURCE_DIR}/inc/*.h)
 
add_executable(${PROJECT_NAME}
	main.cpp
	${INC_FILE}
)