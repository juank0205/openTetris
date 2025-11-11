file(GLOB SRC_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(${PROJECT_NAME}_core STATIC ${SRC_FILES})

target_include_directories(${PROJECT_NAME}_core
	PUBLIC	${CMAKE_SOURCE_DIR}/include/core
			)

target_link_libraries(${PROJECT_NAME}_core PUBLIC
	glfw
	glad
	stb_image
	glm
)
