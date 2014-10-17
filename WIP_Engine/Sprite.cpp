#include "Sprite.h"

#include <gtc/matrix_transform.hpp>

Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}

void Sprite::SetTexture(Texture _texture)
{
	texture = _texture;
}

void Sprite::SetPosition(GLfloat _posX, GLfloat _posY)
{
	position = glm::vec2(_posX, _posY);
}

void Sprite::SetSize(GLfloat _width, GLfloat _height)
{
	width = _width;
	height = _height;
}

void Sprite::SetTextureRect(glm::vec2 _textureRectPos, GLfloat _textureRectWidth, GLfloat _textureRectHeight)
{
	textureRectPos = _textureRectPos;
	textureRectWidth = _textureRectWidth;
	textureRectHeight = _textureRectHeight;
}

int Sprite::GetTextureID()
{
	return texture.id;
}