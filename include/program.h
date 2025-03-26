#pragma once

#include <glm/glm.hpp>

class Program {
public:
  Program();
  ~Program();

  void useProgram();
  void attachShader(unsigned int shaderId);
  void linkShaders();

  inline unsigned int getId() const {
    return id;
  }

  void set1Int(const char *name, int value);
  void setMatrix4f(const char *name, glm::mat4 &matrix);
private:
  unsigned int id;

  void getLinkInfo();
};
