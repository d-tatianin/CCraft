#pragma once
#include "../objects/Button.h"
#include <vector>

namespace CCraft
{
	class ButtonParser
	{
	public:
		std::vector<Button> buttons; //add a texture object to the button class to be initialized from the ButtonParser
		int amount;
	private:
		const char* PATH;
	public:
		ButtonParser();
		~ButtonParser();
	private:
		void parse(const char* path);
	};
}

