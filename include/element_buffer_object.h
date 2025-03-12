#pragma once

#include <cstddef>

class EBO {
public:
  EBO(unsigned int *indices, size_t size);
  ~EBO();

  void bind();

private:
  unsigned int id;

  void unbind();
};

