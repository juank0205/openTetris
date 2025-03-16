#pragma once

class Texture {
public:
  Texture(const char *filepath);
  ~Texture();

  void bind();
  void unbind();
private:
  unsigned int m_id;
  int m_width;
  int m_height;
  int m_nrChannels;
};
