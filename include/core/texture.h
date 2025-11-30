#pragma once

struct Texture {
  unsigned int ID;
  unsigned int Width, Height;
  int InternalFormat;
  int ImageFormat;
  int WrapS;
  int WrapT;
  int FilterMin;
  int FilterMax;
};

Texture init_texture();
void bind_texture(const Texture &texture);
void generate_texture(Texture &texture, int width, int height, unsigned char *data);
