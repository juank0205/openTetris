#include "resource_manager.h"

#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <stb_image/stb_image.h>

ShaderProgram &ResourceManager::LoadShader(const char *vertexSource,
                                           const char *fragmentSource,
                                           const char *geometrySource,
                                           std::string name) {
  shaders[name] =
      loadShaderFromFile(vertexSource, fragmentSource, geometrySource, name);
  return shaders[name];
}

ShaderProgram &ResourceManager::GetShader(std::string name) {
  return shaders[name];
}

Texture &ResourceManager::LoadTexture(const char *file, bool alpha,
                                      std::string name) {
  textures[name] = loadTextureFromFile(file, alpha);
  return textures[name];
}

Texture &ResourceManager::GetTexture(std::string name) {
  return textures[name];
}

void ResourceManager::Clear() {
  for (auto iter : shaders)
    glDeleteProgram(iter.second.ID);
  for (auto iter : textures)
    glDeleteTextures(1, &iter.second.ID);
}

ShaderProgram ResourceManager::loadShaderFromFile(const char *vertexSource,
                                                  const char *fragmentSource,
                                                  const char *geometrySource,
                                                  std::string name) {
  std::string vertexCode;
  std::string fragmentCode;
  std::string geometryCode;
  try {
    std::ifstream vertexShaderFile(vertexSource);
    std::ifstream fragmentShaderFile(fragmentSource);
    std::stringstream vShaderStream, fShaderStream;

    vShaderStream << vertexShaderFile.rdbuf();
    fShaderStream << fragmentShaderFile.rdbuf();

    vertexShaderFile.close();
    fragmentShaderFile.close();
    vertexCode = vShaderStream.str();

    fragmentCode = fShaderStream.str();

    if (geometrySource != nullptr) {
      std::ifstream geometryShaderFile(geometrySource);
      std::stringstream gShaderStream;
      gShaderStream << geometryShaderFile.rdbuf();
      geometryShaderFile.close();
      geometryCode = gShaderStream.str();
    }
  } catch (std::exception e) {
    std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
  }

  const char *vShaderCode = vertexCode.c_str();
  const char *fShaderCode = fragmentCode.c_str();
  const char *gShaderCode = geometryCode.c_str();

  ShaderProgram shader;
  shader.Compile(vShaderCode, fShaderCode,
                 geometrySource != nullptr ? gShaderCode : nullptr);
  return shader;
}

Texture ResourceManager::loadTextureFromFile(const char *file, bool alpha) {
  Texture texture;
  if (alpha) {
    texture.InternalFormat = GL_RGBA;
    texture.ImageFormat = GL_RGBA;
  }

  int width, height, nrChannels;
  unsigned char *data = stbi_load(file, &width, &height, &nrChannels, 0);
  texture.Generate(width, height, data);
  stbi_image_free(data);
  return texture;
}
