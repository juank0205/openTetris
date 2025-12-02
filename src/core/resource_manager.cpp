#include "resource_manager.h"
#include "logger.h"
#include "shader.h"
#include "texture.h"

#include <fstream>
#include <glad/glad.h>
#include <sstream>
#include <stb_image/stb_image.h>
#include <string>

ShaderProgram &ResourceManager::LoadShader(const ShaderPaths &paths,
                                           const std::string &name) {
  shaders[name] = loadShaderFromFile(paths);
  LOG_INFO("Loaded shader: {}", name);
  return shaders[name];
}

ShaderProgram &ResourceManager::GetShader(const std::string &name) {
  return shaders[name];
}

Texture &ResourceManager::LoadTexture(const char *file, bool alpha,
                                      const std::string &name) {
  textures[name] = loadTextureFromFile(file, alpha);
  LOG_INFO("Loaded texture: {}", name);
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

  // Load vertex shader
  std::ifstream vertexShaderFile(path.vertex);
  if (!vertexShaderFile.is_open()) {
    LOG_ERROR("| ERROR: SHADER: Failed to open vertex shader: {}", path.vertex);
    return {}; // return default-constructed ShaderProgram
  }
  std::stringstream vShaderStream;
  vShaderStream << vertexShaderFile.rdbuf();
  vertexCode = vShaderStream.str();
  vertexShaderFile.close();

  // Load fragment shader
  std::ifstream fragmentShaderFile(path.fragment);
  if (!fragmentShaderFile.is_open()) {
    LOG_ERROR("| ERROR: SHADER: Failed to open fragment shader: {}",
              path.fragment);
    return {};
  }
  std::stringstream fShaderStream;
  fShaderStream << fragmentShaderFile.rdbuf();
  fragmentCode = fShaderStream.str();
  fragmentShaderFile.close();

  // Load geometry shader if provided
  if (path.geometry != nullptr) {
    std::ifstream geometryShaderFile(path.geometry);
    if (!geometryShaderFile.is_open()) {
      LOG_ERROR("| ERROR: SHADER: Failed to open geometry shader: {}",
                path.geometry);
      return {};
    }
    std::stringstream gShaderStream;
    gShaderStream << geometryShaderFile.rdbuf();
    geometryCode = gShaderStream.str();
    geometryShaderFile.close();
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

  if (data == nullptr) {
    LOG_WARN("Failed to load texture from file: {}", file);
    return texture;
  }
  generate_texture(texture, width, height, data);

  stbi_image_free(data);
  return texture;
}
