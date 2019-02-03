#pragma once
#include <Windows.h>
#include <string>
#include <sstream>
#include "../logger/Logger.h"
#include "../renderer/objects/Button.h"
#include "../GameModules/Camera.h"
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
		Camera camera;
		glm::mat4 lookAt;
		float deltaTime;
		float currentFrame = 0.0f;
		float lastFrame = 0.0f;
		float xoffset, yoffset, lastX, lastY;
		bool firstMouse = true;
		bool escPressed = false;
		double xCoord, yCoord;
		void proccess();
		void mouse_callback(double x, double y);
		void checkButtons();
		void deltaCalculate();
	public:
		InputHandler(GLFWwindow* window, Button &button1, Button &button2, Button &button3);
	};
}