#pragma once

class Texture{
public:
	unsigned int ID;
	unsigned int Width, Height;
	unsigned int InternalFormat;
	unsigned int ImageFormat;
	unsigned int WrapS;
	unsigned int WrapT;
	unsigned int FilterMin;
	unsigned int FilterMax;
	Texture();
	void Generate(unsigned int width, unsigned int height, unsigned char *data);
	void Bind() const;
};
