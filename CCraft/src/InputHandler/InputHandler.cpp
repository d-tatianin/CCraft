#include "InputHandler.h"

namespace CCraft
{

	InputHandler::InputHandler(GLFWwindow* window, Button &button1)
		: button1(button1), logger("INPUT", Logger::INFO), window(window), gameState(GameState::MENU)
	{

	}

	void InputHandler::mouse_callback(double x, double y)
	{
		xCoord = x;
		yCoord = y;
	}

	void InputHandler::proccess()
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			logger.log("ESC press detected", Logger::INFO);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			logger.log("W press detected", Logger::INFO);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			logger.log("S press detected", Logger::INFO);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			logger.log("A press detected", Logger::INFO);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			logger.log("D press detected", Logger::INFO);
		if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
			logger.log("V press detected", Logger::INFO);
	}

	void InputHandler::checkButtons()
	{
		if (button1.recalculatedData[0] <= xCoord && button1.recalculatedData[2] >= xCoord && button1.recalculatedData[1] <= yCoord && button1.recalculatedData[3] >= yCoord)
		{
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
			{
				button1.mousedOver = false;
				button1.pressed = true;
			}
			else
			{
				button1.pressed = false;
				button1.mousedOver = true;
			}
		}
		else
		{
			button1.mousedOver = false;
			button1.pressed = false;
		}

	}

}