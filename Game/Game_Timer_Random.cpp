#include "Game_Timer_Random.h"
#include <stdlib.h>

Game_Timer_Random::Game_Timer_Random(double _fps)
{
	fps = _fps;
	deltatime = 0;
	seed1 = 1;
}


Game_Timer_Random::~Game_Timer_Random()
{
}

void Game_Timer_Random::Counter()
{
	time1 = clock();
	deltatime = 0;
}

double Game_Timer_Random::getDeltatime()
{
	time2 = clock();

	deltatime = time2-time1;
	return deltatime;
}

bool Game_Timer_Random::SwitchFrame()
{
	for (;;)
	{
		if (getDeltatime() <= fps)
			Sleep(5);
		else
			break;
	}
	return true;
}

void Game_Timer_Random::SeedRandom(double _seed1)
{
	time_t temp;
	time(&temp);

	srand(_seed1*temp);
	seed1 = rand() % 100 + 1;
}

int Game_Timer_Random::getRandom(int min, int max)
{
	time_t temp;
	time(&temp);

	srand(seed1 + temp + getDeltatime());
	random = rand() % max + min;
	
	return random;
}