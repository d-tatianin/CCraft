#pragma once
#include <Windows.h>
#include <string>
#include <sstream>
#include "../logger/Logger.h"
#include "GLFW/glfw3.h"

namespace CCraft
{
	class InputHandler
	{
	private:
		Logger logger;
		GLFWwindow* window;
	public:
		//remove this var
		bool button1Pressed = false;

		InputHandler();
		void setWindow(GLFWwindow* window);
		void proccess();
		void mouse_callback(double x, double y);
	};
}