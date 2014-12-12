#include "Sprite.h"

#include <gtc/matrix_transform.hpp>

Sprite::Sprite()
{
	position = glm::vec2(0, 0);
	rotation = 0;
	height = 0;
	width = 0;
	hasRectangle = false;

}


Sprite::~Sprite()
{
}

void Sprite::SetTexture(Texture &_texture)
{
	texture = _texture;
	height = _texture.height;
	width = _texture.width;
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

void Sprite::SetRectangle(wip::Rectangle &_rect)
{
		//1st position
	textureRectPos1.x = _rect.getRectPosX() / texture.width;
	textureRectPos1.y = (_rect.getRectPosY() + _rect.getRectHeight()) / texture.height;
		//2nd position
	textureRectPos2.x = (_rect.getRectPosX() + _rect.getRectWidth()) / texture.width;
	textureRectPos2.y = (_rect.getRectPosY() + _rect.getRectHeight()) / texture.height;
		//3rd position
	textureRectPos3.x = (_rect.getRectPosX() + _rect.getRectWidth()) / texture.width;
	textureRectPos3.y = _rect.getRectPosY() / texture.height;
		//4th position
	textureRectPos4.x = _rect.getRectPosX() / texture.width;
	textureRectPos4.y = _rect.getRectPosY() / texture.height;
	hasRectangle = true;
}

void Sprite::Scale(float _scale)
{
	width = width * _scale;
	height = height * _scale;
}

void Sprite::Rotate(float _rotation)
{
	rotation = _rotation;
}

int Sprite::GetTextureID()
{
	return texture.id;
}