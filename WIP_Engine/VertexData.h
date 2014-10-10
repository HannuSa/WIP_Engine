#pragma once
#include <vector>
#include <gl\glew.h>

class VertexData
{
public:
	VertexData();
	~VertexData();

	void AddVertex(std::vector<GLfloat> _vertex);
	void AddIndex(std::vector<GLuint> _index);

	const std::vector<GLfloat> getData();
	std::vector<GLuint> getIndex();

	const std::vector<GLuint> index;
	const std::vector<GLfloat> data;

	


};

