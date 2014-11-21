#include "Input.h"
#include <iostream>


bool Input::pressed[256] = { false };
bool Input::released[256] = { true };

Input::Input()
{
}


Input::~Input()
{
}

bool Input::Hold(Button _key)
{
	if (GetAsyncKeyState((int)_key))
	{
		return true;
	}
	
	return false;
	
}

bool Input::Press(Button _key)
{
	if (GetAsyncKeyState((int)_key) && pressed[(int)_key] != true)
	{
		pressed[(int)_key] = true;
		return true;
	}
	else if (!GetAsyncKeyState((int)_key))
	{
		pressed[(int)_key] = false;
	}
	
	return false;
}

bool Input::Release(Button _key)
{
	if (GetAsyncKeyState((int)_key))
	{
		released[(int)_key] = false;
	}
	else if (!GetAsyncKeyState((int)_key) && released[(int)_key] == false)
	{
		released[(int)_key] = true;
		return true;
	}

	return false;
}

void Input::InitArrays()
{
	for (int i = 0; i < 256; i++)
	{
		pressed[i] = false;
		released[i] = true;
	}
}