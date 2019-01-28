#pragma once
#include <Windows.h>
#include <string>
#include <sstream>
#include "../logger/Logger.h"
#include "GLFW/glfw3.h"

namespace CCraft
{
	enum GameState
	{
		MENU = 0, GAME = 1, PAUSED = 3
	};

	class InputHandler
	{
	private:
		Logger logger;
		GLFWwindow* window;
	public:
		GameState gameState;
		//remove this var
		bool button1Pressed = false;

		InputHandler(GLFWwindow* window);
		void proccess();
		void mouse_callback(double x, double y);
	private:
		void checkButtons(double x, double y);
	};
}