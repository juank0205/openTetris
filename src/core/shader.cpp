#include "shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <signal.h>

inline void debugBreak() {
#ifdef _MSC_VER
    __debugbreak();
#elif defined(__GNUC__) || defined(__clang__)
    raise(SIGTRAP);
#else
    std::abort(); // fallback
#endif
}

ShaderProgram &ShaderProgram::Use() {
  glUseProgram(this->ID);
  return *this;
}

void ShaderProgram::Unbind() {
  glUseProgram(0);
}

void ShaderProgram::Compile(const char *vertexSource,
                            const char *fragmentSource,
                            const char *geometrySource) {
  unsigned int sVertex, sFragment, sGeometry;
  sVertex = compileShader(vertexSource, GL_VERTEX_SHADER);
  sFragment = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

  if (geometrySource != nullptr) {
    sGeometry = compileShader(geometrySource, GL_GEOMETRY_SHADER);
    createProgram(sVertex, sFragment, sGeometry);
  } else {
    createProgram(sVertex, sFragment);
  }
}

unsigned int ShaderProgram::compileShader(const char *source,
                                          unsigned int type) {
  unsigned int id = glCreateShader(type);
  glShaderSource(id, 1, &source, NULL);
  glCompileShader(id);
  checkCompileErrors(id, (type == GL_VERTEX_SHADER)     ? "VERTEX"
                         : (type == GL_FRAGMENT_SHADER) ? "FRAGMENT"
                                                        : "GEOMETRY");
  return id;
}

void ShaderProgram::checkCompileErrors(unsigned int object, std::string type) {
  int success;
  char infoLog[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(object, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(object, 1024, NULL, infoLog);
      std::cout
          << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
          << infoLog
          << "\n -- --------------------------------------------------- -- "
          << std::endl;
      debugBreak();
    }
  } else {
    glGetProgramiv(object, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(object, 1024, NULL, infoLog);
      std::cout
          << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
          << infoLog
          << "\n -- --------------------------------------------------- -- "
          << std::endl;
      debugBreak();
    }
  }
}

void ShaderProgram::createProgram(unsigned int vertexShader,
                                  unsigned int fragmentShader,
                                  unsigned int geometryShader) {
  this->ID = glCreateProgram();
  glAttachShader(this->ID, vertexShader);
  glAttachShader(this->ID, fragmentShader);
  glAttachShader(this->ID, geometryShader);
  glLinkProgram(this->ID);
  checkCompileErrors(this->ID, "PROGRAM");
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  glDeleteShader(geometryShader);
}

void ShaderProgram::createProgram(unsigned int vertexShader,
                                  unsigned int fragmentShader) {
  this->ID = glCreateProgram();
  glAttachShader(this->ID, vertexShader);
  glAttachShader(this->ID, fragmentShader);
  glLinkProgram(this->ID);
  checkCompileErrors(this->ID, "PROGRAM");
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void ShaderProgram::SetInteger(const char *name, int value, bool useShader) {
  if (useShader)
    this->Use();
  glUniform1i(glGetUniformLocation(this->ID, name), value);
}

void ShaderProgram::SetVector2f(const char *name, float x, float y,
                                bool useShader) {
  if (useShader)
    this->Use();
  glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}

void ShaderProgram::SetVector2f(const char *name, const glm::vec2 &value,
                                bool useShader) {
  if (useShader)
    this->Use();
  glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}

void ShaderProgram::SetMatrix4f(const char *name, const glm::mat4 &value,
                                bool useShader) {
  if (useShader)
    this->Use();
  glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false,
                     glm::value_ptr(value));
}

void ShaderProgram::SetVector3f(const char *name, const glm::vec3 &value,
                                bool useShader) {
  if (useShader)
    this->Use();
  glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}

void ShaderProgram::SetVector3f(const char *name, float x, float y, float z,
                                bool useShader) {
  if (useShader)
    this->Use();
  glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}
