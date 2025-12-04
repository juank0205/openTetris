include(FetchContent)
# GLFW ----------------------------------------------------
FetchContent_Declare(
	glfw
	GIT_REPOSITORY https://github.com/glfw/glfw
	GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

# GLM -----------------------------------------------------
FetchContent_Declare(
	glm
	GIT_REPOSITORY https://github.com/g-truc/glm
	GIT_TAG 1.0.2
)
FetchContent_MakeAvailable(glm)

# SPDLOG  --------------------------------------------------
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.16.0 
)
FetchContent_MakeAvailable(spdlog)

# GLAD  ----------------------------------------------------
add_subdirectory(glad)

# STB_IMAGE ------------------------------------------------
add_subdirectory(stb_image)