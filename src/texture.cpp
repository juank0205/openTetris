#include "texture.h"
#include "open_gl_calls.h"

#include <iostream>
#include <stb_image.h>

Texture::Texture(const char *filepath) {
  glCall(glGenTextures(1, &m_id));
  bind();

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  unsigned char *data =
      stbi_load(filepath, &m_width, &m_height, &m_nrChannels, 0);
  if (data) {
    glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB,
                        GL_UNSIGNED_BYTE, data));
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);
  unbind();
}

Texture::~Texture() {}

void Texture::bind() { glCall(glBindTexture(GL_TEXTURE_2D, m_id)); }

void Texture::unbind() { glCall(glBindTexture(GL_TEXTURE_2D, 0)); }
