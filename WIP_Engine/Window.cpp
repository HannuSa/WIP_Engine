#include "Window.h""
#include <assert.h>

LRESULT CALLBACK WndProc(HWND _hwnd, UINT _msg, WPARAM _w_param, LPARAM _l_param)
{
	switch (_msg)
	{
	case WM_CLOSE:
		DestroyWindow(_hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(_hwnd, _msg, _w_param, _l_param);
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

/*Register and initialize windows window*/
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

	//Register window
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

/*Test if window wash opened succesfully*/
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