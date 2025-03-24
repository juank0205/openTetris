#include "game_object.h"
#include "open_gl_calls.h"
#include "program.h"
#include <iostream>

GameObject::GameObject(float *vertices, size_t verticesSize,
                       unsigned int *indices, size_t indicesSize,
                       const char *filePath, int textureType, Program &program)
    : vbo(vertices, verticesSize), ebo(indices, indicesSize), texture(filePath, textureType), program(program) {}

GameObject::~GameObject() {}

void GameObject::draw() {
  program.useProgram();
  vao.bind();
  glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
}


