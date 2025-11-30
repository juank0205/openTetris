#include "resource_manager.h"
#include "shader.h"
#include "texture.h"

#include <exception>
#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <stb_image/stb_image.h>
#include <string>

ShaderProgram &ResourceManager::LoadShader(const ShaderPaths &paths,
                                           const std::string &name) {
  shaders[name] = loadShaderFromFile(paths);
  return shaders[name];
}

ShaderProgram &ResourceManager::GetShader(const std::string &name) {
  return shaders[name];
}

Texture &ResourceManager::LoadTexture(const char *file, bool alpha,
                                      const std::string &name) {
  textures[name] = loadTextureFromFile(file, alpha);
  return textures[name];
}

Texture &ResourceManager::GetTexture(const std::string &name) {
  return textures[name];
}

void ResourceManager::Clear() {
  for (auto &iter : shaders) {
    glDeleteProgram(iter.second.ID);
  }
  for (auto &iter : textures) {
    glDeleteTextures(1, &iter.second.ID);
  }
}

ShaderProgram ResourceManager::loadShaderFromFile(const ShaderPaths &path) {
  std::string vertexCode;
  std::string fragmentCode;
  std::string geometryCode;
  try {
    std::ifstream vertexShaderFile(path.vertex);
    std::ifstream fragmentShaderFile(path.fragment);
    std::stringstream vShaderStream;
    std::stringstream fShaderStream;

    vShaderStream << vertexShaderFile.rdbuf();
    fShaderStream << fragmentShaderFile.rdbuf();

    vertexShaderFile.close();
    fragmentShaderFile.close();
    vertexCode = vShaderStream.str();

    fragmentCode = fShaderStream.str();

    if (path.geometry != nullptr) {
      std::ifstream geometryShaderFile(path.geometry);
      std::stringstream gShaderStream;
      gShaderStream << geometryShaderFile.rdbuf();
      geometryShaderFile.close();
      geometryCode = gShaderStream.str();
    }
  } catch (std::exception &e) {
    std::cout << "ERROR::SHADER: Failed to read shader files" << '\n';
  }

  const char *vShaderCode = vertexCode.c_str();
  const char *fShaderCode = fragmentCode.c_str();
  const char *gShaderCode = geometryCode.c_str();

  ShaderProgram shader = compile_shaders(
      {.vertex = vShaderCode,
       .fragment = fShaderCode,
       .geometry = path.geometry != nullptr ? gShaderCode : nullptr});
  return shader;
}

Texture ResourceManager::loadTextureFromFile(const char *file, bool alpha) {
  Texture texture = init_texture();
  if (alpha) {
    texture.InternalFormat = GL_RGBA;
    texture.ImageFormat = GL_RGBA;
  }

  stbi_set_flip_vertically_on_load(GL_TRUE);
  int width;
  int height;
  int nrChannels;
  unsigned char *data =
      stbi_load(file, &width, &height, &nrChannels, alpha ? 4 : 3);

  generate_texture(texture, width, height, data);
  
  stbi_image_free(data);
  return texture;
}
