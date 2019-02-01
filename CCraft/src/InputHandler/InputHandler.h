#pragma once
#include <Windows.h>
#include <string>
#include <sstream>
#include "../logger/Logger.h"
#include "../renderer/objects/Button.h"
#include "GLFW/glfw3.h"

namespace CCraft
{
	enum GameState
	{
		MENU = 0, GAME = 1, PAUSED = 3
	};

	class InputHandler
	{
	public:
		Button button1;
		Button button2;
		Button button3;
	private:
		Logger logger;
		GLFWwindow* window;
	public:
		GameState gameState;
		bool escPressed = false;
		double xCoord, yCoord;
		
		void proccess();
		void mouse_callback(double x, double y);
		void checkButtons();
	public:
		InputHandler(GLFWwindow* window, Button &button1, Button &button2, Button &button3);
	};
}