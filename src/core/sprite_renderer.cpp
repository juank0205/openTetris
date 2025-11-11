#include "sprite_renderer.h"
#include "shader.h"
#include "texture.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

SpriteRenderer::SpriteRenderer() {}

SpriteRenderer::~SpriteRenderer() {}

void SpriteRenderer::Clean() { glDeleteVertexArrays(1, &this->quadVAO); }

void SpriteRenderer::SetShader(ShaderProgram &shader) { this->shader = shader; }

void SpriteRenderer::DrawSprite(Texture &texture, glm::vec2 position,
                                glm::vec2 size, float rotate, glm::vec3 color) {
  this->shader.Use();
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(position, 0.0f));

  model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5 * size.y, 0.0f));
  model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5 * size.y, 0.0f));

  model = glm::scale(model, glm::vec3(size, 1.0f));

  this->shader.SetMatrix4f("model", model);
  this->shader.SetVector3f("spriteColor", color);
  glActiveTexture(GL_TEXTURE0);
  texture.Bind();

  glBindVertexArray(this->quadVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

void SpriteRenderer::InitRenderData() {
  unsigned int VBO;
  float vertices[] = {
      0.0f, 1.0f, 0.0f, 1.0f, //
      1.0f, 0.0f, 1.0f, 0.0f, //
      0.0f, 0.0f, 0.0f, 0.0f, //

      0.0f, 1.0f, 0.0f, 1.0f, //
      1.0f, 1.0f, 1.0f, 1.0f, //
      1.0f, 0.0f, 1.0f, 0.0f  //
  };

  glGenVertexArrays(1, &this->quadVAO); // Create vertex array object
  glGenBuffers(1, &VBO);                // Create buffer object
  glBindBuffer(GL_ARRAY_BUFFER, VBO);   // bind buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
               GL_STATIC_DRAW); // set buffer data

  glBindVertexArray(this->quadVAO); // bind vao
  glEnableVertexAttribArray(0);     // enable
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                        (void *)0); // setup layout
  glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind both
  glBindVertexArray(0);
}
