#include "Renderer.h"

namespace CCraft
{
	Renderer::Renderer()
		: frames(0), logger("RENDERER", Logger::level::INFO), window(initializer.window), gameState(GameState::MENU),
		input(window, parser.buttons, gameState, initializer.vsync), fpsCounter(&Renderer::countFrames, this), menu(parser.buttons),
		game(initializer.drawDistance, initializer.fov, initializer.chThickness, text)
	{
		input.camera.MouseSensitivity = initializer.sensitivity;
		glEnable(GL_DEPTH_TEST);
	}


	void Renderer::shutDown()
	{
		running = false;
		fpsCounter.detach();
		glfwTerminate();
		logger.log("Successfully terminated.", Logger::level::INFO);
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
					glfwSwapInterval(initializer.vsync);
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

			if (input.debugView)
			{
				std::stringstream ss;
				ss << "FPS: " << frameRate;
				text.renderText(ss.str(), (float)width * 0.01f, (float)height - (float)height * 0.05f, 0.5f, FontRenderer::Color::RED);

				ss.str("");

				ss << "X " << (int)input.camera.Position.x << " Y " << (int)input.camera.Position.y << " Z " << (int)input.camera.Position.z;
				text.renderText(ss.str(), (float)width * 0.01f, (float)height - (float)height * 0.1f, 0.5f, FontRenderer::Color::RED);
			}
		}
		
		glfwSwapBuffers(window);
		glfwPollEvents();
		++frames;
	}

	GLFWwindow* Renderer::getWindowID()
	{
		return window;
	}

	void Renderer::countFrames()
	{
		while (running)
		{
			Sleep(1000);
			frameRate = frames;
			frames = 0;
		}
	}
}