#pragma once
#include <Windows.h>

enum class Button
{
	L_CTRL = 0xA2, L_ALT = 0xA4, L_SHIFT = 0xA0, R_CTRL = 0xA3, R_ALT = 0xA5, R_SHIFT = 0xA1,
	SPACE = 0x20, ENTER = 0x0D, ESC = 0x1B, BACKSPASE = 0x08, CAPSLOCK = 0x14, 
	LEFT = 0x25, UP = 0x26, RIGHT = 0x27, DOWN = 0x28,
	ZERO = 0x30, ONE, TWO, TREE, FOUR, FIFE, SIX, SEVEN, EIGHT, NINE, //Don't modify the order of enum numbers
	A = 0x41, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, //Don't modify the order of enum letters
	PLUS = 0xBB, MINUS = 0xBD
};

class Input
{
public:
	static bool Hold(Button _key); //Returns true once per loop the key is held
	static bool Press(Button _key); //Returns true once per key press
	static bool Release(Button _key); //Returns true once upon releasing the key

	static void InitArrays();//Init pressed and released arrays to their default values, (probably not needed, but just in case...)

private:
	Input();
	~Input();

	static bool pressed[256], released[256];
	
};

