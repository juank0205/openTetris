#include "game_object.h"
#include "open_gl_calls.h"
#include "GLFW/glfw3.h"
#include "program.h"
#include "glm/gtc/matrix_transform.hpp"

GameObject::GameObject(float *vertices, size_t verticesSize,
                       unsigned int *indices, size_t indicesSize,
                       const char *filePath, int textureType, Program &program)
    : vbo(vertices, verticesSize), ebo(indices, indicesSize), texture(filePath, textureType), program(program), transform(glm::mat4(1.0f)) {
  transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
}

GameObject::~GameObject() {}

void GameObject::draw() {
  program.useProgram();
  transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
  program.setMatrix4f("transform", transform);
  vao.bind();
  glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
}


