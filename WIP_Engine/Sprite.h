#pragma once

#include "Texture.h"
#include "Rectangle.h"
#include <glm.hpp>

class Sprite
{
public:
	Sprite();
	~Sprite();

	void SetTexture(Texture &_texture);
	void SetPosition(GLfloat _posX, GLfloat _posY);
	void SetSize(GLfloat _width, GLfloat _height);
	void SetRectangle(wip::Rectangle &_rect);
	void Scale(GLfloat _scale);
	void Rotate(GLfloat _rotation);
	void SetTextureRect(glm::vec2 _textureRectPos, GLfloat _textureRectWidth, GLfloat _textureRectHeight);
	int GetTextureID();
	glm::vec2 GetPos(){ return position; }
	GLfloat GetX(){ return position.x; }
	GLfloat GetY(){ return position.y; }
	GLfloat GetHeight(){ return height; }
	GLfloat GetWidth(){ return width; }
	GLfloat GetRotation(){ return rotation; }
	GLfloat GetRectWidth(){ return textureRectWidth; }
	GLfloat GetRectHeight(){ return textureRectHeight; }
	Texture* GetTexture(){ return &texture; }
	glm::vec2 textureRectPos1;
	glm::vec2 textureRectPos2;
	glm::vec2 textureRectPos3;
	glm::vec2 textureRectPos4;
	bool hasRectangle;

private:

	Texture texture;
	wip::Rectangle spriteRect;
	glm::vec2 position;
	GLfloat width, height, rotation;
	GLfloat textureRectWidth, textureRectHeight;
	
	

};