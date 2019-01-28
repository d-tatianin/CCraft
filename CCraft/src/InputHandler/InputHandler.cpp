#include "InputHandler.h"

namespace CCraft
{

	InputHandler::InputHandler(GLFWwindow* window)
		: logger("INPUT", Logger::INFO), window(window), gameState(GameState::MENU)
	{

	}

	void InputHandler::mouse_callback(double x, double y)
	{
		if (gameState == GameState::MENU)
			checkButtons(x, y);
		

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

	void InputHandler::checkButtons(double x, double y)
	{
		if (x > 399 && x < 801)
		{
			if (y > 59 && y < 181)
				button1Pressed = true;
			else
				button1Pressed = false;
		}
		else
			button1Pressed = false;
	}

}