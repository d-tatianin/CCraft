#pragma once
#include "objects/Menu.h"
#include "objects/Block.h"
#include "objects/Hud.h"
#include "../logger/logger.h"
#include "Init.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"



namespace CCraft
{
	enum GameState
	{
		MENU = 0, GAME = 1, PAUSED = 3
	};

	class Renderer
	{
	public:
		bool running = true;
	private:
		Initializer initializer;
		Logger logger;
		int height, width;
		GLFWwindow* window;
		GameState gameState;
		Menu menu;
	public:
		Renderer();
		void render();
	private:
		void shutDown();

	};

}