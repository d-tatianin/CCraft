#include "InputHandler.h"

namespace CCraft
{

	InputHandler::InputHandler(GLFWwindow* window, std::vector<Button> &buttons, GameState &gameState, int vsync)
		: logger("INPUT", Logger::level::INFO), window(window), buttons(buttons),
		gameState(gameState), lookAt(1.0f), vsync(vsync)
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

		if ((glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) && escQ)
		{
			if (gameState == GameState::GAME)
			{
				firstMouse = true;
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				gameState = GameState::MENU;
				glfwSwapInterval(1);
			}
			else if (gameState == GameState::MENU)
			{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				gameState = GameState::GAME;
				glfwSwapInterval(vsync);
			}
			escQ = false;
		}
		else if ((glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE))
		{
			escQ = true;
		}

		if ((glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS) && f1Q)
		{
			debugView ? debugView = false : debugView = true;

			f1Q = false;
		}
		else if ((glfwGetKey(window, GLFW_KEY_F1) == GLFW_RELEASE))
		{
			f1Q = true;
		}

		if ((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) && (gameState == GameState::GAME))
		{
			camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
			lookAt = camera.GetViewMatrix();
		}
			
		if ((glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) && (gameState == GameState::GAME))
		{
			camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
			lookAt = camera.GetViewMatrix();
		}
		if ((glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) && (gameState == GameState::GAME))
		{
			camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
			lookAt = camera.GetViewMatrix();
		}
		if ((glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) && (gameState == GameState::GAME))
		{
			camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
			lookAt = camera.GetViewMatrix();
		}
		if ((glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) && (gameState == GameState::GAME))
		{
			camera.ProcessKeyboard(Camera_Movement::UP, deltaTime);
			lookAt = camera.GetViewMatrix();
		}
		if ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) && (gameState == GameState::GAME))
		{
			camera.ProcessKeyboard(Camera_Movement::DOWN, deltaTime);
			lookAt = camera.GetViewMatrix();
		}

		if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) && m1Q)
		{
			m1Q = false;
			block.placeBlock(camera.Position, camera.Front);
		}
		else if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE))
		{
			m1Q = true;
		}
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