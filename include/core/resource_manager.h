#pragma once

#include "shader.h"
#include "texture.h"

#include <map>
#include <string>

/**
 * @brief Holds file paths for a shader program.
 *
 * Includes paths to vertex, fragment, and optionally geometry shaders.
 */
struct ShaderPaths {
    /// Path to the vertex shader file
    const char *vertex;

    /// Path to the fragment shader file
    const char *fragment;

    /// Optional path to the geometry shader file
    const char *geometry = nullptr;
};

/**
 * @brief Manages shaders and textures in the application.
 *
 * Provides functionality to load, retrieve, and clear resources.
 * Acts as a centralized store to avoid loading the same shader or
 * texture multiple times.
 */
class ResourceManager {
public:

    /**
     * @brief Loads a shader program from file paths.
     *
     * If a shader with the same name exists, it is replaced.
     *
     * @param paths Paths to vertex, fragment, and optionally geometry shaders.
     * @param name Name to store the shader under.
     * @return Reference to the loaded ShaderProgram.
     */
    ShaderProgram &LoadShader(const ShaderPaths &paths, const std::string &name);

    /**
     * @brief Retrieves a previously loaded shader by name.
     *
     * @param name Name of the shader.
     * @return Reference to the ShaderProgram.
     */
    ShaderProgram &GetShader(const std::string &name);

    /**
     * @brief Loads a texture from a file.
     *
     * @param file Path to the image file.
     * @param alpha Whether the image has an alpha channel.
     * @param name Name to store the texture under.
     * @return Reference to the loaded Texture.
     */
    Texture &LoadTexture(const char *file, bool alpha, const std::string &name);

    /**
     * @brief Retrieves a previously loaded texture by name.
     *
     * @param name Name of the texture.
     * @return Reference to the Texture.
     */
    Texture &GetTexture(const std::string &name);

    /**
     * @brief Clears all loaded shaders and textures from memory.
     *
     * Useful to free GPU resources before closing the application.
     */
    void Clear();

private:

    /**
     * @brief Loads a shader program from files (helper function).
     *
     * @param path Paths to the shader files.
     * @return ShaderProgram object loaded from the files.
     */
    static ShaderProgram loadShaderFromFile(const ShaderPaths &path);

    /**
     * @brief Loads a texture from a file (helper function).
     *
     * @param file Path to the image file.
     * @param alpha Whether the image has an alpha channel.
     * @return Texture object loaded from the file.
     */
    static Texture loadTextureFromFile(const char *file, bool alpha);

    /// Map storing all loaded shaders by name
    std::map<std::string, ShaderProgram> shaders;

    /// Map storing all loaded textures by name
    std::map<std::string, Texture> textures;
};

