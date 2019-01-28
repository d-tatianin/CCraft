#pragma once
#include "objects/Menu.h"
#include "objects/Block.h"
#include "objects/Hud.h"
#include "../logger/logger.h"
#include "Init.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "../InputHandler/InputHandler.h"


namespace CCraft
{
	
	class Renderer
	{
	public:
		bool running = true;
	private:
		Initializer initializer;
		Logger logger;
		GLFWwindow* window;
		GameState gameState;
	public:
		InputHandler input;
		Menu menu;
		GLFWwindow* getWindowID();
		Renderer();
		void render();
	private:
		void shutDown();

	};

}