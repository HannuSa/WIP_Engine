#pragma once

#include <string>
#include <exception>


class Debug
{
public:

	static void Message(bool _test, const std::string &_message);//Writes a error message on debug string
	static void KillMessage(bool _test, const std::string &_message);//Stops the program from working on error and writes the suplied message
	static std::string Dvalue(const std::string &_message, const int &_value);//Used to send text and int values to messages

	/*	Try catch syntax for program code that sould not crash the program upon error.
	try
	{
		throw errorCode
	}
	catch
	{		
		Attempt to fix the error.	
	}
	*/
private:
	Debug();
	~Debug();
};
