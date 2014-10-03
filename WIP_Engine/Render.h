#pragma once

#include "Window.h"
#include "TextFileRead.h"
class Render
{
public:
	Render();
	~Render();
	void InitializeShaders();

private: 
	
	GLuint vertexObject;
	GLuint fragmentObject;
	GLuint shaderProgram;
};