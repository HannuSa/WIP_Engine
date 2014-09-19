#include "Window.h"


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, w_param, l_param);
	}
}

Window::Window(int _width, int _height, std::string _title)
{
	width = _width;
	height = _height;
	title = _title;

	Initialize();
}


Window::~Window()
{
}

void Window::Initialize()
{
	x = 100;
	y = 100;

	windowClassName = "WndProc";

	classex.cbSize = sizeof(WNDCLASSEX);
	classex.style = CS_OWNDC;
	classex.hInstance = GetModuleHandle(nullptr);
	classex.lpfnWndProc = WndProc;
	classex.lpszClassName = windowClassName.c_str();
	classex.cbClsExtra = 0;
	classex.cbWndExtra = 0;
	classex.hbrBackground = NULL;
	classex.hCursor = NULL;
	classex.hIcon = NULL;
	classex.hIconSm = NULL;
	classex.lpszMenuName = NULL;

	handle = NULL;

	assert(RegisterClassEx(&classex));

	viewAreaRect.top = 0;
	viewAreaRect.left = 0;
	viewAreaRect.bottom = height;
	viewAreaRect.right = width;

	assert(AdjustWindowRect(&viewAreaRect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, false));

	height = viewAreaRect.bottom - viewAreaRect.top;
	width = viewAreaRect.right - viewAreaRect.left;

	handle = CreateWindowEx(WS_EX_CLIENTEDGE, windowClassName.c_str(), title.c_str(), WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		x, y, width, height, NULL, NULL, GetModuleHandle(nullptr), NULL);

	assert(handle != NULL);

	ShowWindow(handle, SW_SHOWNORMAL);
}

bool Window::IsOpen()
{
	while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE) != 0)
	{
		if (message.message == WM_QUIT)
			return false;
		else
			DispatchMessage(&message);
	}
	return true;
}

LPCWSTR convertString(std::string string)
{
	int slength = string.length() + 1;
	int len = MultiByteToWideChar(CP_ACP, 0, string.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len]; 
	MultiByteToWideChar(CP_ACP, 0, string.c_str(), slength, buf, len);
	std::wstring temp(buf);
	delete[] buf;

	return temp.c_str();
}