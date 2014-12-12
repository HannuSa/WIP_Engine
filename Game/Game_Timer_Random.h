#pragma once

#include <time.h>
#include <Windows.h>

class Game_Timer_Random
{
public:
	Game_Timer_Random(double _fps);
	~Game_Timer_Random();

	//Time
	void Counter();//Set deltatime to 0 and get current time
	double getDeltatime();//Set and return deltatime from the last call of the counter function
	bool SwitchFrame();//Check if deltatime equals less than fps if true sleep and check again
	
	//Random
	void SeedRandom(double _seed1);//Sets a seed for the random function, paramter is just one of the numbers used in the seed
	int getRandom(int min, int max);//Return random value

private:
	clock_t time1, time2;
	double deltatime, fps;
	int seed1, random;

};

