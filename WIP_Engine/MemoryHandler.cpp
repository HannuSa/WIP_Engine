#include "MemoryHandler.h"
#include "Debug.h"

MemoryHandler::MemoryHandler()
{
	vertexsize = 0;
	valueNum = 7;
}


MemoryHandler::~MemoryHandler()
{
}

void MemoryHandler::Allocate(unsigned int _vertexsize, unsigned int _indexsize)
{
	vertexArray = new GLfloat[_vertexsize];
	vertexsize = _vertexsize;
	Debug::Dvalue("", vertexsize);

	indexArray = new GLuint[_indexsize];
	indexsize = _indexsize;
	Debug::Dvalue("", indexsize);

	InitArrays();
}

void MemoryHandler::setIndex(GLuint _index[])
{
	for (int i = 0; i < indexsize; i++)
	{
		indexArray[i] = _index[i];
	}
}

void MemoryHandler::setIndex(int _iamount, ...)
{
	std::va_list indexes;

	va_start(indexes, _iamount);

	for (int i = 0; i < indexsize; i++)
	{
		indexArray[i] = va_arg(indexes, GLuint);
	}
	va_end(indexes);
}


void MemoryHandler::DeAllocate()
{
	if (vertexsize != 0)
	{
		delete[] vertexArray;		
	}
	if (indexsize != 0)
	{
		delete[] indexArray;
	}
}

void MemoryHandler::InitArrays()
{
	for (int i = 0; i < vertexsize; i++)
	{
		vertexArray[i] = 1.0f;
	}	
}

void MemoryHandler::setPos(unsigned int _vertex, GLfloat _x, GLfloat _y)
{
	if (_vertex < vertexsize)
	{
		vertexArray[_vertex * valueNum] = _x;
		vertexArray[_vertex * valueNum + 1] = _y;
	}
	Debug::Message(_vertex < vertexsize, "setPos: vertexArray out of pounds");
}

void MemoryHandler::setColor(unsigned int _vertex, GLfloat _x, GLfloat _y, GLfloat _z)
{
	if (_vertex < vertexsize)
	{
		vertexArray[_vertex * valueNum + 2] = _x;
		vertexArray[_vertex * valueNum + 3] = _y;
		vertexArray[_vertex * valueNum + 4] = _z;
	}
	Debug::Message(_vertex < vertexsize, "setColor: vertexArray out of pounds");
}

void MemoryHandler::setTexture(unsigned int _vertex, GLfloat _x, GLfloat _y)
{
	if (_vertex < vertexsize)
	{
		vertexArray[_vertex * valueNum + 5] = _x;
		vertexArray[_vertex * valueNum + 6] = _y;
	}
	Debug::Message(_vertex < vertexsize, "setTexture: vertexArray out of pounds");
}

size_t MemoryHandler::getVertexSize()
{
	return sizeof(vertexArray)*vertexsize;
}

size_t MemoryHandler::getIndexSize()
{
	return sizeof(indexArray)*indexsize;
}