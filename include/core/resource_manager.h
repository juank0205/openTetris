#pragma once

#include "shader.h"
#include "texture.h"

#include <map>
#include <string>

class ResourceManager {
public:
  ResourceManager() {}
  ShaderProgram &LoadShader(const char *vertexSource, const char *fragmentSource,
                           const char *geometrySource, std::string name);
  ShaderProgram &GetShader(std::string name);
  Texture &LoadTexture(const char *file, bool alpha, std::string name);
  Texture &GetTexture(std::string name);
  void Clear();

private:
  ShaderProgram loadShaderFromFile(const char *vertexSource,
                                   const char *fragmentSource,
                                   const char *geometrySource,
                                   std::string name);
  Texture loadTextureFromFile(const char *file, bool alpha);
  std::map<std::string, ShaderProgram> shaders;
  std::map<std::string, Texture> textures;
};
