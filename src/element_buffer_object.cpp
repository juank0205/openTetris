#include "element_buffer_object.h"
#include "open_gl_calls.h"

EBO::EBO(unsigned int *indices, size_t size) {
  glCall(glGenBuffers(1, &id));
  bind();
  glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW));
  unbind();
}

EBO::~EBO(){};

void EBO::bind() { glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id)); }

void EBO::unbind() { glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); }
