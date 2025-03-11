#pragma once

#include <cstddef>

class VBO {

public:
  VBO(float *data, size_t size);
  VBO();
  ~VBO();

  void bind();
private:
  int size;
  unsigned int m_id;

  void unbind();
};
