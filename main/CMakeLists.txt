add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib)

set(RES_DIR "${CMAKE_SOURCE_DIR}/res")
set(DEST_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${RES_DIR}" "${DEST_DIR}"
    COMMENT "Copying res folder to the build directory"
)

