add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_game)

set(RES_DIR "${CMAKE_SOURCE_DIR}/res")
set(DEST_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res")

file(GLOB_RECURSE RES_SHADERS CONFIGURE_DEPENDS "${RES_DIR}/shaders/*")
add_custom_target(copy_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory "${DEST_DIR}/shaders"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${RES_SHADERS} "${DEST_DIR}/shaders"
    DEPENDS ${RES_SHADERS}
    COMMENT "Updating changed shaders"
)

file(GLOB_RECURSE RES_TEXTURES CONFIGURE_DEPENDS "${RES_DIR}/textures/*")
add_custom_target(copy_textures ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory "${DEST_DIR}/textures"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${RES_TEXTURES} "${DEST_DIR}/textures"
    DEPENDS ${RES_FILES}
    COMMENT "Updating changed textures"
)

add_dependencies(${PROJECT_NAME} copy_shaders copy_textures)
