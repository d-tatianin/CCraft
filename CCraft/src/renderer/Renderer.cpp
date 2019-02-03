#include "Renderer.h"

namespace CCraft
{
	float button1_data[] = {

	440.0f, 660.0f, -1.0f,
	440.0f, 540.0f, -1.0f,
	840.0f, 660.0f, -1.0f,
	440.0f, 540.0f, -1.0f,
	840.0f, 540.0f, -1.0f,
	840.0f, 660.0f, -1.0f
	};

	float button2_data[] = {

	440.0f, 420.0f, -1.0f,
	440.0f, 300.0f, -1.0f,
	840.0f, 420.0f, -1.0f,
	440.0f, 300.0f, -1.0f,
	840.0f, 300.0f, -1.0f,
	840.0f, 420.0f, -1.0f
	};

	float button3_data[] = {

	440.0f, 180.0f, -1.0f,
	440.0f, 60.0f, -1.0f,
	840.0f, 180.0f, -1.0f,
	440.0f, 60.0f, -1.0f,
	840.0f, 60.0f, -1.0f,
	840.0f, 180.0f, -1.0f
	};

	Renderer::Renderer()
		: logger("RENDERER", Logger::INFO), window(initializer.window), gameState(GameState::MENU), button1(button1_data), button2(button2_data),
		button3(button3_data), input(window, button1, button2, button3), menu(button1, button2, button3), game()//constructor will be added later
	{

	}


	void Renderer::shutDown()
	{
		glfwTerminate();
		logger.log("Successfully terminated.", Logger::INFO);
		logger.log("Press enter to continue...", Logger::INFO);
		running = false;
	}

	void Renderer::render()
	{
		if (glfwWindowShouldClose(window))
			shutDown();
		if (menu.quitPressed)
			shutDown();
		if (menu.playPressed)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			input.gameState = GameState::GAME;
			gameState = GameState::GAME;
			menu.playPressed = false;
		}
		if (input.escPressed)
		{
			input.firstMouse = true;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			gameState = GameState::MENU;
			input.escPressed = false;
			input.gameState = GameState::MENU;
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		input.proccess();

		if (gameState == GameState::MENU)
		{
			input.checkButtons();

			menu.button1.pressed = input.button1.pressed;
			menu.button1.mousedOver = input.button1.mousedOver;
			menu.button2.pressed = input.button2.pressed;
			menu.button2.mousedOver = input.button2.mousedOver;
			menu.button3.pressed = input.button3.pressed;
			menu.button3.mousedOver = input.button3.mousedOver;
				
			menu.draw();
		}
		
		else if (gameState == GameState::GAME)
		{
			input.deltaCalculate();
			game.lookAt = input.lookAt;
			game.draw();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	GLFWwindow* Renderer::getWindowID()
	{
		return window;
	}
}