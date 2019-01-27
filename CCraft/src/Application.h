#pragma once
#include <iostream>
#include "logger/logger.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "renderer/Renderer.h"
#include "InputHandler/InputHandler.h"

namespace CCraft
{
	class Application
	{
	private:
		Logger logger;
		InputHandler input;
	public:
		Renderer renderer;
		Application();
		//~Application();
		bool running();
		void play();
		void setMouseCoords(double x, double y);
	private:
		void handleInput();
	};

}