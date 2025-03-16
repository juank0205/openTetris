#include "vertex_array_object.h"
#include "open_gl_calls.h"

VAO::VAO() { glCall(glGenVertexArrays(1, &id)); }

VAO::~VAO() {}

void VAO::bind() { glCall(glBindVertexArray(id)); }

void VAO::unbind() { glCall(glBindVertexArray(0)); }

void VAO::enable(int location, int size, int type, bool normalized,
                 size_t stride, int offset) {
  glCall(glEnableVertexAttribArray(location));
  glCall(glVertexAttribPointer(location, size, type, normalized, stride,
                               (void *)offset));
}
