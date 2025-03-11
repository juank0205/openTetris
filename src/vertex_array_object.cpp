#include "vertex_array_object.h"

#include "vertex_array_object.h"

#include <glad/glad.h>

VAO::VAO() {
  glGenVertexArrays(1, &id);
}

VAO::~VAO() {}

void VAO::bind() {
  glBindVertexArray(id);
}

void VAO::unbind() {
  glBindVertexArray(0);
}

void VAO::enable(int location, int size, int type,
                                     bool normalized, size_t stride,
                                     int offset) {
  glEnableVertexAttribArray(location);
  glVertexAttribPointer(location, size, type, normalized, stride, (void*)offset);
}
