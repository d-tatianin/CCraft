#pragma once
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
		InputHandler();
		void setWindow(GLFWwindow* window);
		void proccess();
		void mouse_callback(double x, double y);
	};
}