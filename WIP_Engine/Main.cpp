#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "Window.h"

int main()
{
	Window window(800, 600, "qwerty");

	while (window.IsOpen())
	{

	}

	return 0;
}