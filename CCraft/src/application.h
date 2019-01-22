#pragma once
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace CCraft
{
	class Application
	{
	private:
		int width = 1280;
		int height = 720;
		GLFWwindow* window;

	public:
		Application();
		~Application();
		bool running();
		void play();
	private:
		void launch();
		void parseConfig(const char* configPath);
		void initWindow();
		void initOpenGL();
		void handleInput();
		void shutDown();
	};

}