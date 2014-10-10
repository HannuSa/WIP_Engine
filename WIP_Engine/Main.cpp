#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "Window.h"
#include "Render.h"
#include "ResourceManager.h"
#include "Texture.h"

static const GLfloat VERTEX_DATA[] =
{
	//1st vertex
	0.77f, 0.66f,
	0.75f, 0.0f, 0.75f,
	1.0f, 0.0f,

	//2nd vertex
	-0.77f, 0.66f,
	0.0f, 0.75f, 0.75f,
	0.0f, 0.0f,

	//3rd vertex
	0.0f, -0.66f,
	1.0f, 1.0f, 1.0f,
	0.5f, 1.0f
};

static const GLuint INDEX_DATA[] =
{
	0, 1, 2
};

int main()
{
	Window window(1200, 600, "This is window!");
	Render render;
	
	render.EnableAttributeArray();

	render.CreateBuffers(sizeof(VERTEX_DATA), sizeof(INDEX_DATA), VERTEX_DATA, INDEX_DATA);

	render.EnableBlending();

	ResourceManager* res = ResourceManager::Create();

	Texture texture;
	texture = res->LoadTextureFromFile("ColoroftheRainbow.png");

	window.SetClearColor(100, 50, 150);

	while (window.IsOpen())
	{
		window.Clear();
		render.DebugDrawStuff(&texture);
		window.Display();
	}

	return 0;
}