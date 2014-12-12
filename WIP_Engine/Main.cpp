#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "Window.h"
#include "Render.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "MemoryHandler.h"
#include "Input.h"
#include "Game_Timer_Random.h"

int main()
{

	Window window(1200, 600, "This is window!");
	Render render(1200, 600);
	
	render.EnableAttributeArray();

	window.SetClearColor(100, 50, 150);

	render.EnableBlending();

	render.InitializeProjection();

	ResourceManager* res = ResourceManager::Create();

	Texture* card;
	card = &res->LoadTextureFromFile("Test.png");
	Texture* bg = &res->LoadTextureFromFile("Background.png");
	Texture bulletTex = res->LoadTextureFromFile("Bullet.png");
	Texture chipTex = res->LoadTextureFromFile("suitsChip.png");

	Sprite Background, Card;
	Background.SetTexture(*bg);
	Background.Scale(1.5);
	Background.SetPosition(-800, -600);
	Card.SetTexture(*card);
	Card.SetPosition(400, 300);

	std::vector<Sprite> bullets, chips;

	int r = 0, c = 0;
	for (int i = 0; i < 12; i++)
	{
		r = i % 4;
		c = i % 3;
		Sprite temp;
		temp.SetTexture(chipTex);
		temp.SetPosition(r*350, c*225);
		chips.push_back(temp);
	}

	window.SetClearColor(100, 50, 150);
	float rotation = 0;
	float cardSpeed = 10.0f, rotationSpeed = 2.0f, bulletSpeed = 15.0f;
	float chipScale = 1.0f;
	bool grow = true;

	float timer = 0;

	while (window.IsOpen())
	{
		timer++;

		if (Input::Hold(Button::W))
		{
			Card.SetPosition(Card.GetX(), Card.GetY()-cardSpeed);
		}
		if (Input::Hold(Button::A))
		{
			Card.SetPosition(Card.GetX()-cardSpeed, Card.GetY());
		}
		if (Input::Hold(Button::S))
		{
			Card.SetPosition(Card.GetX(), Card.GetY()+cardSpeed);
		}
		if (Input::Hold(Button::D))
		{
			Card.SetPosition(Card.GetX()+cardSpeed, Card.GetY());
		}


		if (Input::Hold(Button::UP))
		{
			rotation += rotationSpeed;
		}
		if (Input::Hold(Button::LEFT))
		{
			rotation -= rotationSpeed;
		}
		if (Input::Hold(Button::DOWN))
		{
			rotation -= rotationSpeed;
		}
		if (Input::Hold(Button::RIGHT))
		{
			rotation += rotationSpeed;
		}

		Card.Rotate(rotation);
		Background.Rotate(-rotation);

		if (Input::Press(Button::SPACE))
		{
			Sprite temp;
			temp.SetTexture(bulletTex);
			temp.Rotate(rotation);
			temp.SetPosition((Card.GetX()+(Card.GetWidth()*0.5 - temp.GetWidth()*0.5)), (Card.GetY()+(Card.GetHeight()*0.5 - temp.GetHeight()*0.5)));
			bullets.push_back(temp);
		}

		if (chipScale >= 1.0251f)
			grow = false;
		if (chipScale <= 0.975f)
			grow = true;

		if (grow)
		{
			chipScale += 0.001f;
		}
		else if (!grow)
		{
			chipScale -= 0.001f;
		}
		for (int i = 0; i < chips.size(); i++)
		{
			chips[i].Scale(chipScale);
		}

		for (int i = 0; i < bullets.size(); i++)
		{
			float tempX = bullets[i].GetX(), tempY = bullets[i].GetY();
			float tempRot = glm::radians(bullets[i].GetRotation());
			tempX += bulletSpeed*glm::sin(tempRot);
			tempY -= bulletSpeed*glm::cos(tempRot);
			bullets[i].SetPosition(tempX, tempY);
		}

		window.Clear();
		
		render.DrawSprite(Background);	
		for (int i = 0; i < chips.size(); i++)
		{
			render.DrawSprite(chips[i]);
		}
		render.DrawSprite(Card);
		for (int i = 0; i < bullets.size(); i++)
		{
			render.DrawSprite(bullets[i]);
		}

	

		window.Display();
	}

	return 0;
}