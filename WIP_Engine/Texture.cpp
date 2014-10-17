#include "Texture.h"
#include "Debug.h"

Texture::Texture(std::vector<unsigned char> _imageData, int _width, int _height, int _id)
{
	imageData = _imageData;
	width = _width;
	height = _height;
	id = _id;

	Initialize();
}

Texture::~Texture()
{
}


void Texture::Initialize()
{
	glGenTextures(1, &texture);
	
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &imageData[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}