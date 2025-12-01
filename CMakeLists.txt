cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME "OpenTetris")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(FETCHCONTENT_QUIET OFF)

set(OSBITS 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(OSBITS 64)
endif()
set(FULL_OUTPUT_DIR
				"${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}${OSBITS}/${CMAKE_BUILD_TYPE}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FULL_OUTPUT_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FULL_OUTPUT_DIR}/libs")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FULL_OUTPUT_DIR}")

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")

	add_compile_definitions(DEBUG)
endif()

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
	cmake_policy(SET CMP0141 NEW)
	set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

include(FetchContent)
FetchContent_Declare(
	glfw
	GIT_REPOSITORY https://github.com/glfw/glfw
	GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
	glm
	GIT_REPOSITORY https://github.com/g-truc/glm
	GIT_TAG 1.0.2
)
FetchContent_MakeAvailable(glm)

# GLAD
add_subdirectory(external/glad)

# STB_IMAGE
add_subdirectory(external/stb_image)

# Static analysis
set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-warnings-as-errors=*")
file(GLOB_RECURSE ALL_SRC_FILES src/*.cpp)
add_custom_target(clang_tidy
    COMMAND clang-tidy -p ${CMAKE_BINARY_DIR} ${ALL_SRC_FILES}
    COMMENT "Running clang-tidy on all sources"
)

# add_subdirectory(src)
add_subdirectory(src/core)
add_subdirectory(src/openTetris)
add_subdirectory(main)
