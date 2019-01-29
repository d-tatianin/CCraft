#include "InputHandler.h"

namespace CCraft
{

	InputHandler::InputHandler(GLFWwindow* window)
		: logger("INPUT", Logger::INFO), window(window), gameState(GameState::MENU)
	{

	}

	void InputHandler::mouse_callback(double x, double y)
	{
		xCoord = x;
		yCoord = y;

		

		//insane performance hit
		//system("CLS");
		//std::stringstream ss;
		//ss << "Mouse position X:" << x << " Y:" << y;
		//std::string message = ss.str();
		//logger.log(message.c_str(), Logger::INFO);
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

	//fix this garbage
	void InputHandler::checkButtons()
	{
		if (xCoord > 399 && xCoord < 801)
		{
			if (yCoord > 59 && yCoord < 181)
			{
				button1.mouseOvered = true;
				if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
				{
					button1.pressed = true;
					button1.mouseOvered = false;
				}

				else
				{
					button1.mouseOvered = true;
					button1.pressed = false;
				}
			}

			else
			{
				button1.mouseOvered = false;
				button1.pressed = false;
			}
		}
		else
		{
			button1.mouseOvered = false;
			button1.pressed = false;
		}
			
	}

}