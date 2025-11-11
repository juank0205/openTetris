#pragma once

#include "shader.h"
#include "texture.h"

#include <glm/glm.hpp>

class SpriteRenderer {
public:
  SpriteRenderer();
  ~SpriteRenderer();
  void SetShader(ShaderProgram &shader);
  void DrawSprite(Texture &texture, glm::vec2 position,
                  glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
                  glm::vec3 color = glm::vec3(1.0f));
  void InitRenderData();
  void Clean();

private:
  ShaderProgram shader;
  unsigned int quadVAO;
};
