#pragma once
#include <iostream>
#include "logger.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace CCraft
{
	class Application
	{
	private:
		int width = -1;
		int height = -1;
		GLFWwindow* window;
		Logger logger;

	public:
		Application();
		~Application();
		bool running();
		void play();
	private:
		void launch();
		void parseConfig(const std::string& configPath);
		void initWindow();
		void initOpenGL();
		void handleInput();
		void shutDown();
	};

}