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
	bool IsOpen();
	void SetClearColor(int _red, int _green, int _blue, int _alpha);
	void Clear();
	void Display();
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

	void InitializeWindow();
	void InitializeRenderingContext();
};