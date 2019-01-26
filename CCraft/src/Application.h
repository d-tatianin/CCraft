#pragma once
#include <iostream>
#include "logger/logger.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "renderer/Renderer.h"

namespace CCraft
{
	class Application
	{
	private:
		Logger logger;
		Renderer renderer;
	public:
		Application();
		//~Application();
		bool running();
		void play();
	private:
		void handleInput();
	};

}