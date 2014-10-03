#pragma once

#include <Windows.h>
#include <assert.h>
#include <string>
#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>


class Window
{
public:
	Window(int _width, int _height, std::string _title);
	~Window();
	bool IsOpen();														//Check that window hasn't received a quit message
	void SetClearColor(int _red, int _green, int _blue);				//Set the window clear color
	void Clear();														//Clear the window with a color
	void Display();														//Swap buffers so the drawn stuff is shown
private:
	std::string windowClassName;
	WNDCLASSEX classex;
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	HWND windowHandle;
	HDC deviceContext;
	HGLRC renderingContext;
	RECT viewAreaRect;
	MSG message;
	int x, y, width, height;
	std::string title;

	void InitializeWindow();											//Register & initialize window
	void InitializeRenderingContext();									//Initialize the openGL renderingcontext
};