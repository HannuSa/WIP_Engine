#pragma once

#include <assert.h>
#include <string>
#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include "ResourceManager.h"
#include "Texture.h"
class Render
{
public:
	Render();
	~Render();
	void InitializeShaders(); //Load & initialize vertex & fragment shaders & link the program
	void EnableAttributeArray();
	void EnableUniformSampler();
	void EnableBlending(); //Enable GL_BLEND & set BlendFunc
	void CreateBuffers(GLsizeiptr _vertexSize, GLsizeiptr _indexSize, const GLfloat* _vertexData, const GLuint* _indexData); //Create buffers for vertex & index data
	void DebugDrawStuff(Texture* _texture);

private: 
	GLuint vertexObject;
	GLuint fragmentObject;
	GLuint shaderProgram;
	GLuint buffers[2];
	GLuint positionIndex, colorIndex, texCoordIndex;
	GLint uniSamplerLoc;
};