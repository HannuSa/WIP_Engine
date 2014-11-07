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

	void Allocate(unsigned int _vertexsize, unsigned int _indexsize);//Allocates the arrays
	void DeAllocate();
	size_t getVertexSize();//Returns the size of of vertexArray
	size_t getIndexSize();//Returns the size of of vertexArray
	
	GLfloat *vertexArray;
	GLuint *indexArray;

	void setPos(unsigned int _vertex, GLfloat _x, GLfloat _y);//Setter for position
	void setColor(unsigned int _vertex, GLfloat _x, GLfloat _y, GLfloat _z);//Setter for color
	void setTexture(unsigned int _vertex, GLfloat _x, GLfloat _y);//Setter for texture position

	private:
	unsigned int vertexsize, indexsize, valueNum; //vertexsize + indexsize = array size, valueNum = values in single vertex, 

	void InitArrays();//Initializes arrays to 1.0f (white color)
};

