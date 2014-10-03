#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "Window.h"
#include "ResourceManager.h"

int main()
{
	Window window(1200, 600, "This is window!");

	window.SetClearColor(100, 50, 150);

	ResourceManager *res = new ResourceManager();

	res->LoadPixelData("Test.png");

	while (window.IsOpen())
	{
		window.Clear();
		window.Display();
	}

	res->~ResourceManager();

	return 0;
}