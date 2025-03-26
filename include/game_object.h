#pragma once

#include "element_buffer_object.h"
#include "glm/ext/matrix_float4x4.hpp"
#include "program.h"
#include "texture.h"
#include "vertex_array_object.h"
#include "vertex_buffer_object.h"

#include <glm/glm.hpp>

class GameObject {
public:
  GameObject(float *vertices, size_t verticesSize, unsigned int *indices,
             size_t indicesSize, const char *filePath, int textureType, Program &program);
  ~GameObject();

  void draw();

  VAO vao;
  EBO ebo;
  VBO vbo;
  Texture texture;
  Program program;
  glm::mat4 transform;
};
