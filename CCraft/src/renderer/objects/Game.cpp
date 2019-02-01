#include "Game.h"

namespace CCraft {

	Game::Game()
	{
	}

	void Game::draw()
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

}