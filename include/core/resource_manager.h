#pragma once

#include "shader.h"
#include "texture.h"

#include <map>
#include <string>

struct ShaderPaths {
  const char *vertex;
  const char *fragment;
  const char *geometry = nullptr; // optional
};

class ResourceManager {
public:
  ShaderProgram &LoadShader(const ShaderPaths &paths, const std::string &name);
  ShaderProgram &GetShader(const std::string &name);
  Texture &LoadTexture(const char *file, bool alpha, const std::string &name);
  Texture &GetTexture(const std::string &name);
  void Clear();

private:
  static ShaderProgram loadShaderFromFile(const ShaderPaths &path);
  static Texture loadTextureFromFile(const char *file, bool alpha);
  std::map<std::string, ShaderProgram> shaders;
  std::map<std::string, Texture> textures;
};
