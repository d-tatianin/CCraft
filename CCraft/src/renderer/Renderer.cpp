#include "Renderer.h"

namespace CCraft
{

	Renderer::Renderer()
		: logger("RENDERER", Logger::INFO), window(initializer.window), gameState(GameState::MENU)
	{
	}


	void Renderer::shutDown()
	{
		glfwTerminate();
		logger.log("Successfully terminated.", Logger::INFO);
		logger.log("Press enter to continue...", Logger::INFO);
		running = false;
		std::cin.get();
	}

	void Renderer::render()
	{
		if (glfwWindowShouldClose(window))
			shutDown();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (gameState == GameState::MENU)
			menu.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	GLFWwindow* Renderer::getWindowID()
	{
		return window;
	}
}