#include "InputHandler.h"

namespace CCraft
{

	InputHandler::InputHandler(GLFWwindow* window, Button &button1, Button &button2, Button &button3)
		: button1(button1), button2(button2), button3(button3), logger("INPUT", Logger::INFO), window(window), gameState(GameState::MENU), lookAt(1.0f)
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

		if (button2.recalculatedData[0] <= xCoord && button2.recalculatedData[2] >= xCoord && button2.recalculatedData[1] <= yCoord && button2.recalculatedData[3] >= yCoord)
		{
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
			{
				button2.mousedOver = false;
				button2.pressed = true;
			}
			else
			{
				button2.pressed = false;
				button2.mousedOver = true;
			}
		}
		else
		{
			button2.mousedOver = false;
			button2.pressed = false;
		}

		if (button3.recalculatedData[0] <= xCoord && button3.recalculatedData[2] >= xCoord && button3.recalculatedData[1] <= yCoord && button3.recalculatedData[3] >= yCoord)
		{
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
			{
				button3.mousedOver = false;
				button3.pressed = true;
			}
			else
			{
				button3.pressed = false;
				button3.mousedOver = true;
			}
		}
		else
		{
			button3.mousedOver = false;
			button3.pressed = false;
		}


	}
	
	void InputHandler::deltaCalculate()
	{
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}
}