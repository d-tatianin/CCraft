#pragma once
#include "objects/Menu.h"
#include "objects/Hud.h"
#include "../logger/logger.h"
#include "Init.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "../InputHandler/InputHandler.h"
#include "objects/Button.h"
#include "objects/Game.h"
#include "ButtonParser/ButtonParser.h"
#include <thread>

namespace CCraft
{
	
	class Renderer
	{
	public:
		bool running = true;
	private:
		unsigned int frames;
		std::thread fpsCounter;
		Initializer initializer;
		Logger logger;
		GLFWwindow* window;
		GameState gameState;
		ButtonParser parser;
	public:
		InputHandler input;
		Menu menu;
		Game game;
	public:
		GLFWwindow* getWindowID();
		Renderer();
		void render();
	private:
		void countFrames();
		void shutDown();

	};

}