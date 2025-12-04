#pragma once

#include <glm/glm.hpp>

/**
 * @brief Represents an OpenGL shader program.
 *
 * Stores the OpenGL ID for a compiled shader program.
 */
struct ShaderProgram {
    /// OpenGL shader program ID
    unsigned int ID;
};

/**
 * @brief Holds file paths for shader source code.
 *
 * Includes vertex, fragment, and optionally geometry shader paths.
 */
struct ShaderSources {
    /// Path to the vertex shader file
    const char *vertex;

    /// Path to the fragment shader file
    const char *fragment;

    /// Optional path to the geometry shader file
    const char *geometry = nullptr;
};

/**
 * @brief Activates (binds) a shader program.
 *
 * @param program ShaderProgram to bind.
 */
void use_shader_program(const ShaderProgram &program);

/**
 * @brief Deactivates (unbinds) the currently active shader program.
 */
void unbind_shader_program();

/**
 * @brief Compiles shaders from given source paths into a ShaderProgram.
 *
 * @param sources Paths to vertex, fragment, and optional geometry shaders.
 * @return ShaderProgram object containing the compiled shader program.
 */
ShaderProgram compile_shaders(const ShaderSources &sources);

/**
 * @brief Sets an integer uniform in a shader program.
 *
 * Optionally activates the shader program before setting the value.
 *
 * @param program ShaderProgram to modify.
 * @param name Name of the uniform variable.
 * @param value Integer value to set.
 * @param useShader If true, activates the shader program before setting the uniform (default: false).
 */
void shader_program_set_integer(const ShaderProgram &program, const char *name, int value,
                                bool useShader = false);

/**
 * @brief Sets a 2D vector uniform in a shader program.
 *
 * Optionally activates the shader program before setting the value.
 *
 * @param program ShaderProgram to modify.
 * @param name Name of the uniform variable.
 * @param x X component of the vector.
 * @param y Y component of the vector.
 * @param useShader If true, activates the shader program before setting the uniform (default: false).
 */
void shader_program_set_vector2f(const ShaderProgram &program, const char *name, float x, float y,
                                 bool useShader = false);

/**
 * @brief Sets a 2D vector uniform in a shader program from a glm::vec2.
 *
 * Optionally activates the shader program before setting the value.
 *
 * @param program ShaderProgram to modify.
 * @param name Name of the uniform variable.
 * @param value glm::vec2 value to set.
 * @param useShader If true, activates the shader program before setting the uniform (default: false).
 */
void shader_program_set_vector2f(const ShaderProgram &program, const char *name, const glm::vec2 &value,
                                 bool useShader = false);

/**
 * @brief Sets a 3D vector uniform in a shader program.
 *
 * Optionally activates the shader program before setting the value.
 *
 * @param program ShaderProgram to modify.
 * @param name Name of the uniform variable.
 * @param x X component of the vector.
 * @param y Y component of the vector.
 * @param z Z component of the vector.
 * @param useShader If true, activates the shader program before setting the uniform (default: false).
 */
void shader_program_set_vector3f(const ShaderProgram &program, const char *name, float x, float y, float z,
                                 bool useShader = false);

/**
 * @brief Sets a 3D vector uniform in a shader program from a glm::vec3.
 *
 * Optionally activates the shader program before setting the value.
 *
 * @param program ShaderProgram to modify.
 * @param name Name of the uniform variable.
 * @param value glm::vec3 value to set.
 * @param useShader If true, activates the shader program before setting the uniform (default: false).
 */
void shader_program_set_vector3f(const ShaderProgram &program, const char *name, const glm::vec3 &value,
                                 bool useShader = false);

/**
 * @brief Sets a 4x4 matrix uniform in a shader program.
 *
 * Optionally activates the shader program before setting the value.
 *
 * @param program ShaderProgram to modify.
 * @param name Name of the uniform variable.
 * @param value glm::mat4 value to set.
 * @param useShader If true, activates the shader program before setting the uniform (default: false).
 */
void shader_program_set_matrix4(const ShaderProgram &program, const char *name, const glm::mat4 &value,
                                bool useShader = false);

