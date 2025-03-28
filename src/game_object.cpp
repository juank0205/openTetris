#include "game_object.h"
#include "open_gl_calls.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/trigonometric.hpp"
#include "program.h"


GameObject::GameObject(float *vertices, size_t verticesSize,
                       unsigned int *indices, size_t indicesSize,
                       const char *filePath, int textureType, Program &program)
    : vbo(vertices, verticesSize),
      /*ebo(indices, indicesSize),*/ texture(filePath, textureType),
      program(program), transform(glm::mat4(1.0f)) {}

GameObject::~GameObject() {}

void GameObject::draw(float deltaTime) {
  program.useProgram();
  transform = glm::rotate(transform, glm::radians(50.0f) * deltaTime,
                          glm::vec3(0.5f, 1.0f, 0.0f));
  program.setMatrix4f("model", transform);
  vao.bind();
  glCall(glDrawArrays(GL_TRIANGLES, 0, 36));
}

void GameObject::translate(glm::vec3 &vector) {
  transform = glm::translate(transform, vector);
}
