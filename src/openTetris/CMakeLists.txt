file(GLOB SRC_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(${PROJECT_NAME}_game STATIC  ${SRC_FILES})

target_link_libraries(${PROJECT_NAME}_game PUBLIC 
	${PROJECT_NAME}_core 
	glm 
	glfw
)

target_include_directories(${PROJECT_NAME}_game PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/include/core
)

