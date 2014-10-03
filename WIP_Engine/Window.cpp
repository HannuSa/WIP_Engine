#include "Window.h"

//Window procedure
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

	InitializeWindow();
	InitializeRenderingContext();
}


Window::~Window()
{
	//Make renderingcontext uncurrent & destroy it
	wglMakeCurrent(deviceContext, NULL);
	wglDeleteContext(renderingContext);
}

void Window::InitializeWindow()
{
	x = 100;
	y = 100;

	windowClassName = "WndProc";

	//Initialize the WNDCLASSEX struct
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

	windowHandle = NULL;

	//Register window
	assert(RegisterClassEx(&classex));

	//Set window size
	viewAreaRect.top = 0;
	viewAreaRect.left = 0;
	viewAreaRect.bottom = height;
	viewAreaRect.right = width;

	assert(AdjustWindowRect(&viewAreaRect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, false));

	height = viewAreaRect.bottom - viewAreaRect.top;
	width = viewAreaRect.right - viewAreaRect.left;

	//Create window
	windowHandle = CreateWindowEx(WS_EX_CLIENTEDGE, windowClassName.c_str(), title.c_str(), WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		x, y, width, height, NULL, NULL, GetModuleHandle(nullptr), NULL);

	assert(windowHandle != NULL);

	//Show window
	ShowWindow(windowHandle, SW_SHOWNORMAL);
}

void Window::InitializeRenderingContext()
{
	//Initialize the PIXELFORMATDESCRIPTOR struct
	pixelFormatDescriptor =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,					//colordepth
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,					//bits for the depthbuffer
		0,
		0,
		NULL,
		0,
		0, 0, 0
	};
	//Get the devicecontext of the window
	deviceContext = GetDC(windowHandle);

	//Choose and set the pixelformat according to the devicecontext
	int pixelFormatIndex = ChoosePixelFormat(deviceContext, &pixelFormatDescriptor);
	assert(pixelFormatIndex != 0);
	SetPixelFormat(deviceContext, pixelFormatIndex, &pixelFormatDescriptor);

	//Create the renderingcontext & make it current
	renderingContext = wglCreateContext(deviceContext);
	assert(renderingContext != NULL);
	wglMakeCurrent(deviceContext, renderingContext);
}

void Window::SetClearColor(int _red, int _green, int _blue)
{
	glClearColor(_red / 255.f, _green / 255.f, _blue / 255.f, 0.f);
}

void Window::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::Display()
{
	SwapBuffers(deviceContext);
}

bool Window::IsOpen()
{
	//Go through all the messages, if there are any
	while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE) != 0)
	{
		//Return false if the window has received a quit message
		if (message.message == WM_QUIT)
			return false;
		else
		//Pass the message to the window procedure
			DispatchMessage(&message);
	}
	return true;
}