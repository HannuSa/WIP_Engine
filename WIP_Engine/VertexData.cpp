#include "VertexData.h"


VertexData::VertexData()
{
}


VertexData::~VertexData()
{
}

void VertexData::AddVertex(std::vector<GLfloat> _vertex)
{
	for (int i = 0; i < _vertex.size(); i++)
	{
		data.push_back(_vertex.at(i));
	}
}

void VertexData::AddIndex(std::vector<GLuint> _index)
{
	for (int i = 0; i < _index.size(); i++)
	{
		data.push_back(_index.at(i));
	}
}

const std::vector<GLfloat> VertexData::getData()
{
	return data;
}