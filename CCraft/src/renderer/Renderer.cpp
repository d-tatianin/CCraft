#include "Renderer.h"

namespace CCraft
{
	Renderer::Renderer()
		: logger("RENDERER", Logger::level::INFO), window(initializer.window), gameState(GameState::MENU),
		input(window, parser.buttons, gameState), menu(parser.buttons), game(initializer.drawDistance, initializer.fov)
	{
		input.camera.MouseSensitivity = initializer.sensitivity;
	}


	void Renderer::shutDown()
	{
		glfwTerminate();
		logger.log("Successfully terminated.", Logger::level::INFO);
		running = false;
	}

	void Renderer::render()
	{
		if (glfwWindowShouldClose(window))
			shutDown();
		for (Button &but : parser.buttons)
		{
			if (but.onClick == Button::Action::PLAY)
			{
				if (but.pressed)
				{
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
					gameState = GameState::GAME;
				}
					
			}
			else if (but.onClick == Button::Action::EXIT)
			{
				if (but.pressed)
					shutDown();
			}
			else if (but.onClick == Button::Action::SETTINGS)
			{
				if (but.pressed)
					logger.log("Settings menu has not yet been implemented.", Logger::level::INFO);
			}
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