#pragma once

#include "glm/fwd.hpp"
#include "shader.h"
#include "texture.h"

#include <glm/glm.hpp>

/**
 * @brief Represents a 2D sprite with position, size, rotation, and color.
 */
struct Sprite {
  /// Position of the sprite in screen/world coordinates
  glm::vec2 position;

  /// Size of the sprite (width, height). Default is (10, 10)
  glm::vec2 size = glm::vec2(10.0F, 10.0F); // NOLINT

  /// Rotation angle of the sprite in degrees. Default is 0
  float rotate = 0.0F;

  /// Color of the sprite as RGB vector. Default is white (1.0, 1.0, 1.0)
  glm::vec3 color = glm::vec3(1.0F);
};

/**
 * @brief Renders 2D sprites using a shader and textures.
 *
 * Handles batching and rendering of Sprite objects with a single
 * quad geometry.
 */
class SpriteRenderer {
public:
  /// Default constructor
  SpriteRenderer() = default;

  /// Destructor
  ~SpriteRenderer() = default;

  /**
   * @brief Sets the shader program used for rendering sprites.
   *
   * @param shader ShaderProgram to use for rendering.
   */
  void SetShader(ShaderProgram &shader);

  /**
   * @brief Draws a sprite with a given texture and sprite parameters.
   *
   * @param texture Texture to use for the sprite.
   * @param sprite Sprite data including position, size, rotation, and color.
   */
  void DrawSprite(Texture &texture, const Sprite &sprite);

  /**
   * @brief Initializes the quad geometry and any required OpenGL buffers.
   *
   * Must be called before drawing sprites.
   */
  void InitRenderData();

  /**
   * @brief Cleans up OpenGL resources used by the sprite renderer.
   *
   * Should be called before program exit.
   */
  void Clean();

private:
  ShaderProgram shader;
  unsigned int quadVAO;
};
;
