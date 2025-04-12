#include "program.h"
#include "open_gl_calls.h"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Program::Program() { id = glCreateProgram(); }

Program::~Program() {}

void Program::attachShader(unsigned int shaderId) {
  glCall(glAttachShader(id, shaderId));
}

void Program::linkShaders() {
  glCall(glLinkProgram(id));
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

void Program::useProgram() { glCall(glUseProgram(id)); }

void Program::set1Int(const char *name, int value) {
  glCall(glUniform1i(glGetUniformLocation(id, name), value));
}

void Program::setMatrix4f(const char *name, glm::mat4 &matrix) {
  glCall(glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE,
                            glm::value_ptr(matrix)));
}

void Program::setVec3f(const char *name, glm::vec3 &vec) {
  glCall(glGetUniformLocation(id, name));
  glCall(glUniform3fv(glGetUniformLocation(id, name), 1, glm::value_ptr(vec)));
}
