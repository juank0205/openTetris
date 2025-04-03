#pragma once
//#include "element_buffer_object.h"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float3.hpp"
#include "program.h"
#include "vertex_array_object.h"
#include "vertex_buffer_object.h"

#include <glm/glm.hpp>

class GameObject {
public:
  GameObject(float *vertices, size_t verticesSize, unsigned int *indices,
             size_t indicesSize, Program &program);
  ~GameObject();

  void draw(float deltaTime);
  void translate(glm::vec3 &vector);

  VAO vao;
  //EBO ebo;
  VBO vbo;
  //Texture texture;
  Program &program;
  glm::mat4 transform;
};
