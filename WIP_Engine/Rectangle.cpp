#include "Rectangle.h"


wip::Rectangle::Rectangle()
{
	rectPosX = 0;
	rectPosY = 0;
	rectHeight = 0;
	rectWidth = 0;
}

wip::Rectangle::Rectangle(GLfloat _rectX, GLfloat _rectY, GLfloat _width, GLfloat _height)
{
	rectPosX = _rectX;
	rectPosY = _rectY;
	rectWidth = _width;
	rectHeight = _height;
}


wip::Rectangle::~Rectangle()
{
}
