#pragma once

/**
 * @brief Represents an OpenGL texture with its parameters.
 *
 * Stores the texture ID and configuration information needed
 * for binding and generating textures in OpenGL.
 */
struct Texture {
    /// OpenGL texture ID
    unsigned int ID;

    /// Width of the texture in pixels
    unsigned int Width;

    /// Height of the texture in pixels
    unsigned int Height;

    /// Internal format used by OpenGL (e.g., GL_RGBA)
    int InternalFormat;

    /// Format of the image data (e.g., GL_RGBA)
    int ImageFormat;

    /// Wrapping mode on the S axis (e.g., GL_REPEAT)
    int WrapS;

    /// Wrapping mode on the T axis (e.g., GL_REPEAT)
    int WrapT;

    /// Minifying filter (e.g., GL_LINEAR)
    int FilterMin;

    /// Magnifying filter (e.g., GL_LINEAR)
    int FilterMax;
};

/**
 * @brief Initializes a default texture.
 *
 * Creates a Texture struct with default parameters.
 *
 * @return Texture A new Texture object with default settings.
 */
Texture init_texture();

/**
 * @brief Binds a texture to the current OpenGL context.
 *
 * @param texture The texture to bind.
 */
void bind_texture(const Texture &texture);

/**
 * @brief Generates a texture with given pixel data.
 *
 * Uploads the data to the GPU and sets width, height, and format.
 *
 * @param texture The texture to initialize and upload data to.
 * @param width Width of the texture in pixels.
 * @param height Height of the texture in pixels.
 * @param data Pointer to the image data (RGBA, 8-bit per channel).
 */
void generate_texture(Texture &texture, int width, int height, unsigned char *data);

