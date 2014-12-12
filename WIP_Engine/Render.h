#pragma once

#include <assert.h>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>
#include "ResourceManager.h"
#include "MemoryHandler.h"
#include "Sprite.h"
#include "Window.h"

class Render
{
public:
	Render(float _winHeight, float _winwidth);
	~Render();
	void InitializeShaders(); //Load & initialize vertex & fragment shaders & link the program
	void EnableAttributeArray();
	void EnableUniformSampler();
	void EnableBlending(); //Enable GL_BLEND & set BlendFunc
	void InitializeProjection();
	void CreateBuffers(GLsizeiptr _vertexSize, GLsizeiptr _indexSize, const GLfloat* _vertexData, const GLuint* _indexData); //Create buffers for vertex & index data
	void BeginSpriteBatch();
	void DrawSprite(Sprite &_sprite);
	void EndSpriteBatch();
	void DebugDrawStuff(Texture* _texture);

private: 
	GLuint vertexObject;
	GLuint fragmentObject;
	GLuint shaderProgram;
	GLuint buffers[2];
	GLuint positionIndex, colorIndex, texCoordIndex, uniSampler, projectionLocation;
	GLuint rotationIndex;
	GLint uniSamplerLoc;
	std::vector<Sprite*> spriteBatch;
	MemoryHandler memoryHandler;
	float winHeight;
	float winWidth;
};