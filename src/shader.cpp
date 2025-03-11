#include "shader.h"

#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <iterator>

Shader::Shader(const std::string &filePath, int shaderType)
    : m_shaderType(shaderType) {
  readSource(filePath);
  compile();
}

Shader::~Shader() {
  glDeleteShader(id);
}

int Shader::readSource(const std::string &filePath) {
  std::ifstream stream(filePath);
  if (!stream.is_open()) {
    std::cout << "Failed to open file" << std::endl;
    return -1;
  }

  m_src = std::string(std::istreambuf_iterator<char>(stream),
                      std::istreambuf_iterator<char>());

  return 0;
}

void Shader::compile() {
  if (m_shaderType == SHADER_TYPE_VERTEX) {
    id = glCreateShader(GL_VERTEX_SHADER);
  } else {
    id = glCreateShader(GL_FRAGMENT_SHADER);
  }

  const char *srcPtr = m_src.c_str();

  glShaderSource(id, 1, &srcPtr, NULL);
  glCompileShader(id);
  checkCompileInfo(); 
}

void Shader::checkCompileInfo() {
  int success;
  char log[512];
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(id, 512, NULL, log);
    std::cout << "ERROR::SHADER_COMPILATION: " << log << std::endl;
  }
}
