#include "vertex_buffer_object.h"

#include <glad/glad.h>

VBO::VBO(float *data, size_t size) {
  glGenBuffers(1, &m_id);
  bind();
  glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);
  unbind();
}

VBO::VBO() {}

VBO::~VBO() {}

void VBO::bind() { glBindBuffer(GL_ARRAY_BUFFER, m_id); }

void VBO::unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
