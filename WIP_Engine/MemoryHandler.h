#pragma once
#include "GL\glew.h"

/*struct Vertex
{
	GLfloat pos[2];
	GLfloat color[3];
	GLfloat textpos[2];
};*/

class MemoryHandler
{
public:
	MemoryHandler();
	~MemoryHandler();

	void Allocate(unsigned int _arraysize);//Allocates the arrays
	void DeAllocate();
	size_t getVarraySize();//Returns the size of of vertexArray

	void InitArrays();//Initializes arrays to 1.0f (white color)

//private:
	GLfloat *vertexArray;
	unsigned int arraysize;
};

