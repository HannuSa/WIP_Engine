#pragma once
#include <GL\glew.h>

namespace wip
{
	class Rectangle
	{
	public:
		Rectangle();
		Rectangle(GLfloat _rectX, GLfloat _rectY, GLfloat _width, GLfloat _height);
		~Rectangle();
		GLfloat getRectPosX(){ return rectPosX; }
		GLfloat getRectPosY(){ return rectPosY; }
		GLfloat getRectWidth(){ return rectWidth; }
		GLfloat getRectHeight(){ return rectHeight; }

	private:

		GLfloat rectPosX;
		GLfloat rectPosY;
		GLfloat rectWidth;
		GLfloat rectHeight;
	};
}

