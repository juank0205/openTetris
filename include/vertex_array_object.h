#pragma once

#include <cstddef>

class VAO {
public:
  VAO();
  ~VAO();

  void enable(int location, int size, int type,
                                     bool normalized, size_t stride,
                                     int offset);
  void bind();
private:
  unsigned int id;

  void unbind();
};
