#include "element_buffer_object.h"

#include <glad/glad.h>

EBO::EBO(unsigned int *indices, size_t size) {
  glGenBuffers(1, &id);
  bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
  unbind();
}

EBO::~EBO(){};

void EBO::bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); }

void EBO::unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
