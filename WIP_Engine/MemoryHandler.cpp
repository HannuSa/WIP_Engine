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

	InitArrays();
}


void MemoryHandler::DeAllocate()
{
	if (arraysize != 0)
	{
		delete[] vertexArray;		
	}
}

void MemoryHandler::InitArrays()
{
	for (int i = 0; i < arraysize; i++)
	{
		vertexArray[i] = 0.0f;
	}
	
}

size_t MemoryHandler::getVarraySize()
{
	return sizeof(vertexArray)*arraysize;
}