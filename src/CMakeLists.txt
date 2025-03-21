add_library(${PROJECT_NAME}_lib STATIC 
    open_gl_calls.cpp
    window_manager.cpp
    input_manager.cpp
    program.cpp
    renderer.cpp
    shader.cpp
    vertex_array_object.cpp
    vertex_buffer_object.cpp
    element_buffer_object.cpp
    texture.cpp
)

# target_include_directories(${PROJECT_NAME}_lib PRIVATE 
#     ${CMAKE_SOURCE_DIR}/include
#     ${CMAKE_SOURCE_DIR}/external/glfw/include
#     ${CMAKE_SOURCE_DIR}/external/glad/include
#     ${CMAKE_SOURCE_DIR}/external/stb_image/include
# )

target_link_libraries(${PROJECT_NAME}_lib PUBLIC glfw3 glad stb_image)

target_include_directories(${PROJECT_NAME}_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

# if(UNIX)
#     target_link_directories(${PROJECT_NAME}_lib PUBLIC 
# 	${CMAKE_SOURCE_DIR}/external/glfw/linux/src
#     )
#     target_link_libraries(${PROJECT_NAME}_lib PRIVATE glfw3 glad)
# elseif(WIN32)
#     target_link_directories(${PROJECT_NAME}_lib PUBLIC 
# 	${CMAKE_SOURCE_DIR}/external/glfw/windows
#     )
#     target_link_libraries(${PROJECT_NAME}_lib glfw3 glad)
#
#     add_custom_command(TARGET ${PROJECT_NAME}_lib POST_BUILD
#         COMMAND ${CMAKE_COMMAND} -E copy_if_different
#         ${CMAKE_SOURCE_DIR}/external/glfw/windows/glfw3.dll
#         $<TARGET_FILE_DIR:${PROJECT_NAME}_lib>
#     )
# endif()

