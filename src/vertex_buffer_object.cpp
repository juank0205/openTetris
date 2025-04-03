#include "vertex_buffer_object.h"
#include "open_gl_calls.h"

VBO::VBO(float *data, size_t size) : m_size(size) {
  glCall(glGenBuffers(1, &m_id));
  bind();
  glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
  unbind();
}

VBO::VBO() {}

VBO::~VBO() {}

void VBO::bind() { glCall(glBindBuffer(GL_ARRAY_BUFFER, m_id)); }

void VBO::unbind() { glCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); }
