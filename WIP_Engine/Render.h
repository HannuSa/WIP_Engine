#pragma once

#include <assert.h>
#include <string>
#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include "TextFileRead.h"
class Render
{
public:
	Render();
	~Render();
	void InitializeShaders();
	void EnableAttributeArray();
	void CreateBuffers(GLsizeiptr _vertexSize, GLsizeiptr _indexSize, const GLfloat* _vertexData, const GLuint* _indexData);
	void DebugDrawStuff();

private: 
	
	GLuint vertexObject;
	GLuint fragmentObject;
	GLuint shaderProgram;
	GLuint buffers[2];
	GLuint positionIndex, colorIndex;
};