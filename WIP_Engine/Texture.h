#pragma once

#include <string>
#include <vector>
#include <GL/glew.h>
#include <GL/GL.h>
#include "lodepng.h"

class Texture
{
public:
	Texture();
	~Texture();	
	
	GLuint texture;
	
	void LoadFromFile(std::string _filename);
private:
	std::vector<unsigned char> imageData;
	unsigned int width, height;

	void Initialize();
};