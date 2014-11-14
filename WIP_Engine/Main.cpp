#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "Window.h"
#include "Render.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "MemoryHandler.h"

static const GLfloat VERTEX_DATA[] =	//add texture coords
{
	//1st vertex
	600, 100,//Positio
	0.75f, 0.0f, 0.0f,//color
	1.0f, 0.0f,//texture

	//2nd vertex
	200, 500,
	0.0f, 0.0f, 0.75f,
	0.0f, 0.0f,

	//3rd vertex
	1000, 500,
	0.0f, 0.0f, 0.0f,
	0.5f, 1.0f
};

static const GLuint INDEX_DATA[] =
{
	0, 1, 2
};

int main()
{

	//MemoryHandler m;
	//m.Allocate(3 * 7, 3);
	//
	////1st vertex
	//m.setPos(0, 600, 100);
	//m.setColor(0, 1.0f, 1.0f, 1.0f);
	//m.setTexture(0, 1.0f, 0.0f);

	////2nd vertex
	//m.setPos(1, 200, 500);
	//m.setColor(1, 1.0f, 1.0f, 1.0f);
	//m.setTexture(1, 0.0f, 0.0f);

	////3rd vertex
	//m.setPos(2, 1000, 500);
	//m.setColor(2, 1.0f, 1.0f, 1.00f);
	//m.setTexture(2, 0.5f, 1.0f);

	////Index array
	//m.indexArray[0] = 0;
	//m.indexArray[1] = 1;
	//m.indexArray[2] = 2;

	Window window(1200, 600, "This is window!");
	Render render;
	
	render.EnableAttributeArray();

	/*render.CreateBuffers(m.getVertexSize(), m.getIndexSize(), m.vertexArray, m.indexArray);*/

	window.SetClearColor(100, 50, 150);

	render.EnableBlending();

	render.InitializeProjection();

	ResourceManager* res = ResourceManager::Create();

	Texture texture;
	texture = res->LoadTextureFromFile("ColoroftheRainbow.png");
	Texture texture2 = res->LoadTextureFromFile("Test.png");

	Sprite test;
	Sprite test2;
	test.SetTexture(texture2);
	test2.SetTexture(texture);
	test.SetPosition(700, 500);
	test2.SetPosition(-(993/2), -(960/2));
	test.SetSize(200, 291);
	test2.Scale(1.0f);
	test.Rotate(30.0f);

	window.SetClearColor(100, 50, 150);
	float x = 100, y = 100;
	float rotation = 0;
	int timer = 0;
	while (window.IsOpen())
	{
		window.Clear();
		//render.BeginSpriteBatch();
		//render.DrawSprite(miuOmaSprite);
		//render.DrawSprite(jonkuToisenSprite);
		//render.EndSpriteBatch();
	/*	render.DebugDrawStuff(&texture);*/
		timer++;
		rotation++;
		test.SetPosition(x, y);
		render.DrawSprite(test);	
		render.DrawSprite(test2);
		test2.Rotate(rotation);
		test.Rotate(rotation);

		window.Display();
	}

	return 0;
}