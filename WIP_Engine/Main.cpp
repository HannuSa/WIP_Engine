#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "Window.h"

int main()
{
	Window window(1200, 600, "This is window!");

	window.SetClearColor(100, 50, 150);

	while (window.IsOpen())
	{
		window.Clear();
		window.Display();
	}

	return 0;
}