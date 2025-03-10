#include "vertex_buffer_object.h"

#include <glad/glad.h>

VBO::VBO() { glGenBuffers(1, &m_id); }

void VBO::bind() { glBindBuffer(GL_ARRAY_BUFFER, m_id); }

void VBO::unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void VBO::setData(float *data, size_t size) {
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
