#pragma once

#include "Texture.h"
#include <glm.hpp>

class Sprite
{
public:
	Sprite();
	~Sprite();

	void SetTexture(Texture _texture);
	void SetPosition(GLfloat _posX, GLfloat _posY);
	void SetSize(GLfloat _width, GLfloat _height);
	void SetTextureRect(glm::vec2 _textureRectPos, GLfloat _textureRectWidth, GLfloat _textureRectHeight);
	int GetTextureID();

private:
	Texture texture;
	glm::vec2 position;
	GLfloat width, height;
	glm::vec2 textureRectPos;
	GLfloat textureRectWidth, textureRectHeight;
};