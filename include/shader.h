#pragma once

#define SHADER_TYPE_VERTEX 1
#define SHADER_TYPE_FRAGMENT 2

#include <string>

class Shader {
public:
  Shader(const std::string &filePath, int shaderType);
  ~Shader();

  inline unsigned int getId() const {
    return id;
  }

private:
  std::string m_src;
  unsigned int id;
  int m_shaderType;
  const char * m_filePath;

  int readSource(const std::string &filePath);
  void compile();
  void checkCompileInfo();
};
