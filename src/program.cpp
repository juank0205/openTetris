#include "program.h"

#include <glad/glad.h>
#include <iostream>

Program::Program() {
  id = glCreateProgram();
}

Program::~Program() {}

void Program::attachShader(unsigned int shaderId) {
  glAttachShader(id, shaderId);
}

void Program::linkShaders() {
  glLinkProgram(id);
  getLinkInfo();
} 

void Program::getLinkInfo() {
  int success;
  char log[512];
  glGetProgramiv(id, GL_LINK_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(id, 512, NULL, log);

    std::cout << "ERROR::PROGRAM_LINK: " << log << std::endl;
  }
}

void Program::useProgram() {
  glUseProgram(id);
}
