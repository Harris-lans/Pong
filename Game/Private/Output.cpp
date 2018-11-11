#include <Windows.h>
#include <iostream>
#include <string>
#include "Output.h"

void Console::Log(const char* text)
{
	OutputDebugString(text);
}

void Console::LogString(std::string text)
{
	Console::Log(text.c_str());
}
