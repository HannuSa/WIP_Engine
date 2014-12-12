#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "Window.h"
#include "Render.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "MemoryHandler.h"

//Game
#include "Game_Timer_Random.h"


int main()
{

	Window window(1000, 800, "This is window!");
	Render render;
	
	//Initialize graphics stuff
	render.EnableAttributeArray();
	render.EnableBlending();
	render.InitializeProjection();

	window.SetClearColor(100, 50, 150);

	ResourceManager* res = ResourceManager::Create();
	Texture* texture = &res->LoadTextureFromFile("Test.png");

	Sprite test;
	test.SetTexture(*texture);
	test.SetPosition(0, 0);
	test.SetSize(100, 100);

	window.SetClearColor(100, 50, 150);

	//Game
	Game_Timer_Random T_R(60.0f);
	T_R.SeedRandom(2);

	//Test
	float x = 0;

	while (window.IsOpen())
	{
		T_R.Counter();//Start game timer
		window.Clear();
		
		x++;
		test.SetPosition(x, 0);
		render.DrawSprite(test);	

		window.Display();

		//Set FPS
		T_R.SwitchFrame();

	}

	return 0;
}