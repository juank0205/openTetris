#pragma once

#define PNG 0
#define JPG 1

class Texture {
public:
  Texture(const char *filepath, int type);
  ~Texture();

  void bind();
  void unbind();
  void activate(int unit);
private:
  unsigned int m_id;
  int m_width;
  int m_height;
  int m_nrChannels;
};
