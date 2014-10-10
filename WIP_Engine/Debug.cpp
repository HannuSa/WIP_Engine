#include "Debug.h"
#include <stdio.h>
#include <Windows.h>

Debug::Debug()
{
}

Debug::~Debug()
{
}

void Debug::Message(bool _test, const std::string &_message)
{
	if (!_test)
	{
		OutputDebugString("\n\n");
		OutputDebugString("Error: ");
		OutputDebugString(_message.c_str());
		OutputDebugString("\n\n");
	}
}

void Debug::KillMessage(bool _test, const std::string &_message)
{
	if (!_test)
	{
		OutputDebugString("\n\n");
		OutputDebugString("Error: ");
		OutputDebugString(_message.c_str());
		OutputDebugString("\n\n");
		abort();
	}
}
std::string Debug::Dvalue(const std::string &_message, const int &_value)
{
	return _message + std::to_string(_value);
}