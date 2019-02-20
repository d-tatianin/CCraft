#include "InputHandler.h"

namespace CCraft
{

	InputHandler::InputHandler(GLFWwindow* window, std::vector<Button> &buttons, GameState &gameState)
		: logger("INPUT", Logger::level::INFO), window(window), buttons(buttons),
		gameState(gameState), lookAt(1.0f)
	{
		lookAt = camera.GetViewMatrix();
	}

	void InputHandler::mouse_callback(double x, double y)
	{
		xCoord = x;
		yCoord = y;

		if (gameState == GameState::GAME)
		{
			if (firstMouse)
			{
				lastX = x;
				lastY = y;
				firstMouse = false;
			}

			xoffset = x - lastX;
			yoffset = lastY - y;

			lastX = x;
			lastY = y;

			camera.ProcessMouseMovement(xoffset, yoffset);
			lookAt = camera.GetViewMatrix();
		}
		
	}

	void InputHandler::proccess()
	{
		//wireframe mode for debug purposes
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			escPressed = true;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
			lookAt = camera.GetViewMatrix();
		}
			
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
			lookAt = camera.GetViewMatrix();
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
			lookAt = camera.GetViewMatrix();
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
			lookAt = camera.GetViewMatrix();
		}
		if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
			logger.log("V press detected", Logger::level::INFO);
	}

	void InputHandler::checkButtons()
	{
		for (Button &btn : buttons)
		{
			if (btn.recalculatedData[0] <= xCoord && btn.recalculatedData[2] >= xCoord && btn.recalculatedData[1] <= yCoord && btn.recalculatedData[3] >= yCoord)
			{
				if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
				{
					btn.mousedOver = false;
					btn.pressed = true;
				}
				else
				{
					btn.pressed = false;
					btn.mousedOver = true;
				}
			}
			else
			{
				btn.mousedOver = false;
				btn.pressed = false;
			}
		}


	}
	
	void InputHandler::deltaCalculate()
	{
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}
}