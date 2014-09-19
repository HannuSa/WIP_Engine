#pragma once

#include <Windows.h>
#include <assert.h>
#include <string>

class Window
{
public:
	Window(int _width, int _height, std::string _title);
	~Window();
	bool IsOpen();
private:
	std::string windowClassName;
	WNDCLASSEX classex;
	HWND handle;
	RECT viewAreaRect;
	MSG message;
	int x, y, width, height;
	std::string title;

	void Initialize();
};