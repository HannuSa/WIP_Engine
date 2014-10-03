#pragma once

#include "Window.h"
#include "TextFileRead.h"
class Render
{
public:
	Render();
	~Render();
	GLuint SetShaders();

private: 
	
	GLuint vertexObject;
	GLuint fragmentObject;
	GLuint shaderProgram;
};

