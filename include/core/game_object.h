#pragma once

#include "glm/ext/vector_float3.hpp"
#include "sprite_renderer.h"
#include "texture.h"
#include <glm/glm.hpp>

class GameObject {
public:
  GameObject();
  GameObject(glm::vec2 pos, Texture &sprite, glm::vec2 size, float rotation,
             glm::vec3 color = glm::vec3(1.0f));

  virtual void Draw(SpriteRenderer &renderer);

  glm::vec2 Position;
  glm::vec2 Size;
  float Rotation;
  glm::vec3 Color;
  Texture Sprite;
};
