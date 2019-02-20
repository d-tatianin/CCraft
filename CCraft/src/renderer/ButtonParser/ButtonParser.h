#pragma once
#include "../objects/Button.h"
#include "../../logger/Logger.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>

namespace CCraft
{
	class ButtonParser
	{
	public:
		std::vector<Button> buttons; 
		int amount;
	private:
		Logger logger;
	public:
		ButtonParser();
	private:
		void parse(const char* path);
		void addTexCoords(float* data);
	};
}

