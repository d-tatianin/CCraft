#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "../logger/Logger.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace CCraft
{
	class Initializer
	{
	private:
		Logger logger;
		int height, width;
		GLFWwindow* window;
	public:
		Initializer();
	private:
		void parseConfig(const std::string& configPath);
		void initWindow();
		void initOpenGL();
		void launch();
		friend class Renderer;
	};
}