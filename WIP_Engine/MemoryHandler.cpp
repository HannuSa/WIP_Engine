#include "MemoryHandler.h"
#include "Debug.h"

MemoryHandler::MemoryHandler()
{
	arraysize = 0;
}


MemoryHandler::~MemoryHandler()
{
}

void MemoryHandler::Allocate(unsigned int _arraysize)
{
	vertexArray = new GLfloat[_arraysize];
	arraysize = _arraysize;
	Debug::Dvalue("", arraysize);
}

void MemoryHandler::DeAllocate()
{
	if (arraysize != 0)
	{
		delete[] vertexArray;		
	}
}

size_t MemoryHandler::getArraySize()
{
	return sizeof(vertexArray)*arraysize;
}