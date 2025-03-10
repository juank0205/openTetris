#pragma once

#include <cstddef>

class VBO {

public:
  VBO();
  ~VBO();

  void setData(float *data, size_t size);

private:
  int size;
  unsigned int m_id;

  void bind();
  void unbind();
};
