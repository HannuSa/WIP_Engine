#pragma once

#include <string>
#include <vector>
#include <GL/glew.h>
#include <GL/GL.h>
#include "lodepng.h"

class ResourceManager;

class Texture
{
public:
	Texture(){}
	Texture(std::vector<unsigned char> _imageData, int _width, int _height);
	~Texture();	
	
	GLuint texture;
	unsigned int width, height;
private:
	std::vector<unsigned char> imageData;

	void Initialize(); //Generate texture & create resource manager
};