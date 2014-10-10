#include "Texture.h"
#include "Debug.h"

Texture::Texture()
{
	Initialize();
}


Texture::~Texture()
{
}


void Texture::Initialize()
{
	glGenTextures(1, &texture);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Texture::LoadFromFile(std::string _filename)
{
	unsigned int error = lodepng::decode(imageData, width, height, _filename);
	Debug::KillMessage(!error, "Failed to load image");

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &imageData[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}