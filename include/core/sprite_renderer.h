#pragma once

#include "glm/fwd.hpp"
#include "shader.h"
#include "texture.h"

#include <glm/glm.hpp>

struct Sprite {
  glm::vec2 position;
  glm::vec2 size = glm::vec2(10.0F, 10.0F); // NOLINT
  float rotate = 0.0F;
  glm::vec3 color = glm::vec3(1.0F);
};

class SpriteRenderer {
public:
  SpriteRenderer();
  ~SpriteRenderer();
  void SetShader(ShaderProgram &shader);
  void DrawSprite(Texture &texture, const Sprite &sprite);
  void InitRenderData();
  void Clean();

private:
  ShaderProgram shader;
  unsigned int quadVAO;
};
