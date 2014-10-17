#pragma once
#include "GL\glew.h"

struct Vertex
{
	GLfloat pos[2];
	GLfloat color[3];
	GLfloat textpos[2];
};

class MemoryHandler
{
public:
	MemoryHandler();
	~MemoryHandler();

	void Allocate(unsigned int _arraysize);
	void DeAllocate();
	size_t getArraySize();

//private:
	GLfloat *vertexArray;
	unsigned int arraysize;
};

