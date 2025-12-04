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

# Enable testing
enable_testing()

# Static analysis ------------------------------------------
option(ENABLE_CLANG_TIDY "Enable clang-tidy checks during build" OFF)

if(ENABLE_CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-warnings-as-errors=*")
endif()

file(GLOB_RECURSE ALL_SRC_FILES 
    CONFIGURE_DEPENDS
    src/core/*.cpp 
    src/openTetris/*.cpp
    main/*.cpp
)
set(REL_SRC_FILES "")
foreach(src ${ALL_SRC_FILES})
	file(RELATIVE_PATH rel_src ${CMAKE_SOURCE_DIR} ${src})
    list(APPEND REL_SRC_FILES ${rel_src})
endforeach()
add_custom_target(clang-tidy
	COMMAND run-clang-tidy -p ${CMAKE_BINARY_DIR} ${REL_SRC_FILES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running clang-tidy on all sources"
)

# Documentation ----------------------------------------------
find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN  ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target(gen_docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating documentation with Doxygen"
        VERBATIM
    )
else()
    message(STATUS "Doxygen not found, documentation target will not be available")
endif()


add_subdirectory(external)

add_subdirectory(src/core)
add_subdirectory(src/openTetris)
add_subdirectory(main)
add_subdirectory(tests)
