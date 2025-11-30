#include "sprite_renderer.h"
#include "shader.h"
#include "texture.h"

#include <array>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

void SpriteRenderer::Clean() { glDeleteVertexArrays(1, &this->quadVAO); }

void SpriteRenderer::SetShader(ShaderProgram &shader) { this->shader = shader; }

void SpriteRenderer::DrawSprite(Texture &texture, const Sprite &sprite) {
  use_shader_program(this->shader);
  auto model = glm::mat4(1.0F);
  model = glm::translate(model, glm::vec3(sprite.position, 0.0F));

  model = glm::translate(model, glm::vec3(0.5F * sprite.size.x, // NOLINT
                                          0.5 * sprite.size.y, 0.0F)); // NOLINT
  model = glm::rotate(model, glm::radians(sprite.rotate),
                      glm::vec3(0.0F, 0.0F, 1.0F));
  model =
      glm::translate(model, glm::vec3(-0.5F * sprite.size.x,	// NOLINT
                                      sprite.size.y * -0.5, 0.0F)); // NOLINT

  model = glm::scale(model, glm::vec3(sprite.size, 1.0F));

  shader_program_set_matrix4(this->shader, "model", model);
  shader_program_set_vector3f(this->shader, "spriteColor", sprite.color);
  glActiveTexture(GL_TEXTURE0);
  bind_texture(texture);

  glBindVertexArray(this->quadVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6); // NOLINT
  glBindVertexArray(0);
}

void SpriteRenderer::InitRenderData() {
  unsigned int VBO;
  std::array<float, 24> vertices[] = { // NOLINT
      // NOLINT
      0.0F, 1.0F, 0.0F, 1.0F, //
      1.0F, 0.0F, 1.0F, 0.0F, //
      0.0F, 0.0F, 0.0F, 0.0F, //

      0.0F, 1.0F, 0.0F, 1.0F, //
      1.0F, 1.0F, 1.0F, 1.0F, //
      1.0F, 0.0F, 1.0F, 0.0F  //
  };

  glGenVertexArrays(1, &this->quadVAO); // Create vertex array object
  glGenBuffers(1, &VBO);                // Create buffer object
  glBindBuffer(GL_ARRAY_BUFFER, VBO);   // bind buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices->data()), vertices->data(),
               GL_STATIC_DRAW); // set buffer data

  glBindVertexArray(this->quadVAO); // bind vao
  glEnableVertexAttribArray(0);     // enable
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                        (void *)nullptr); // setup layout
  glBindBuffer(GL_ARRAY_BUFFER, 0);       // unbind both
  glBindVertexArray(0);
}
