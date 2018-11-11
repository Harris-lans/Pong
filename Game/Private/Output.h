#pragma once

#include <string>
#include "Singleton.h"

class Console : public Singleton<Console>
{
public:
	static void Log(const char* text);
	static void LogString(std::string text);
	// Templating the log function
	template <typename T>
	static void LogType(T text)
	{
		std::string temp(std::to_string(text));
		const char* finalChar = temp.c_str();
		Log(finalChar);
	}
};

Console* Singleton<Console>::existingInstance = nullptr;