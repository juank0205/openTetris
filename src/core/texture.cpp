#include "texture.h"

#include <glad/glad.h>

Texture init_texture() {
  Texture texture;
  texture.Width = 0;
  texture.Height = 0;
  texture.InternalFormat = GL_RGB;
  texture.ImageFormat = GL_RGB;
  texture.WrapS = GL_REPEAT;
  texture.WrapT = GL_REPEAT;
  texture.FilterMin = GL_LINEAR;
  texture.FilterMax = GL_LINEAR;
  return texture;
}

void generate_texture(Texture &texture, int width, int height,
                      unsigned char *data) {
  texture.Height = height;
  texture.Width = width;
  glGenTextures(1, &texture.ID);
  glBindTexture(GL_TEXTURE_2D, texture.ID);
  glTexImage2D(GL_TEXTURE_2D, 0, texture.InternalFormat, width, height, 0,
               texture.ImageFormat, GL_UNSIGNED_BYTE, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture.WrapS);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture.WrapT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture.FilterMin);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture.FilterMax);
  glBindTexture(GL_TEXTURE_2D, 0);
  glGetError();
}

void bind_texture(const Texture &texture) {
  glBindTexture(GL_TEXTURE_2D, texture.ID);
}
