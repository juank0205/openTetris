#pragma once
//#include "element_buffer_object.h"
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

  void draw();
  void translate(glm::vec3 &vector);
  void rotate(glm::vec3 &eulerAngles);
  void update(float deltaTime);

  VAO vao;
  //EBO ebo;
  VBO vbo;
  //Texture texture;
  Program &program;
  glm::vec3 m_position;
  glm::vec3 m_rotation;
};
