#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "Window.h"
#include "Render.h"
#include "ResourceManager.h"

static const GLfloat VERTEX_DATA[] =	//add texture coords
{
	//1st vertex
	0.77f, 0.66f,
	0.75f, 0.0f, 0.75f,

	//2nd vertex
	-0.77f, 0.66f,
	0.0f, 0.75f, 0.75f,

	//3rd vertex
	0.0f, -0.66f,
	1.0f, 1.0f, 1.0f
};

static const GLuint INDEX_DATA[] =
{
	0, 1, 2
};

int main()
{
	Window window(1200, 600, "This is window!");
	Render render;

	window.SetClearColor(100, 50, 150);

	ResourceManager *res = new ResourceManager();

	res->LoadPixelData("Test.png");

	render.EnableAttributeArray();

	render.CreateBuffers(sizeof(VERTEX_DATA), sizeof(INDEX_DATA), VERTEX_DATA, INDEX_DATA);

	while (window.IsOpen())
	{
		window.Clear();
		render.DebugDrawStuff();
		window.Display();
	}

	res->~ResourceManager();

	return 0;
}