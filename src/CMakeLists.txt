add_library(${PROJECT_NAME}_lib STATIC 
    glad/glad.c
    window_manager.cpp
    input_manager.cpp
)

target_include_directories(${PROJECT_NAME}_lib PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/glfw/include
    ${CMAKE_SOURCE_DIR}/external/glad/include
)

target_link_directories(${PROJECT_NAME}_lib PUBLIC 
    ${CMAKE_SOURCE_DIR}/external/glfw/src
)

target_link_libraries(${PROJECT_NAME}_lib glfw3)
