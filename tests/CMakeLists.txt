# Testing -------------------------------------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

# Collect all test files
file(GLOB TEST_FILES "*.cpp")

# Create a single test executable with all test files
add_executable(${PROJECT_NAME}_tests ${TEST_FILES})

# Include directories
target_include_directories(${PROJECT_NAME}_tests PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
) 

# Link against the libraries
target_link_libraries(${PROJECT_NAME}_tests 
    ${PROJECT_NAME}_game
    ${PROJECT_NAME}_core
    gtest_main
)

# Discover tests in the executable
gtest_discover_tests(${PROJECT_NAME}_tests
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    DISCOVERY_TIMEOUT 30
)
