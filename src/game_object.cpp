#include "game_object.h"
#include "glm/ext/matrix_transform.hpp"
#include "open_gl_calls.h"
#include "program.h"

GameObject::GameObject(float *vertices, size_t verticesSize,
                       unsigned int *indices, size_t indicesSize,
                       Program &program)
    : vbo(vertices, verticesSize),
      /*ebo(indices, indicesSize), texture(filePath, textureType), */
      program(program), m_position(glm::vec3(0.0f)),
      m_rotation(glm::vec3(0.0f)) {}

GameObject::~GameObject() {}

void GameObject::draw() {
  program.useProgram();
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, m_position);
  model = glm::rotate(model, m_rotation.x, glm::vec3(1, 0, 0));
  model = glm::rotate(model, m_rotation.y, glm::vec3(0, 1, 0));
  model = glm::rotate(model, m_rotation.z, glm::vec3(0, 0, 1));
  program.setMatrix4f("model", model);
  vao.bind();
  glCall(glDrawArrays(GL_TRIANGLES, 0, 36));
}

void GameObject::translate(glm::vec3 &vector) { m_position += vector; }

void GameObject::rotate(glm::vec3 &eulerAngles) { m_rotation += eulerAngles; }

void GameObject::update(float deltaTime) {
  glm::vec3 euler = glm::vec3(1.0f, 0, 1.0f) * deltaTime;
  rotate(euler);
}
