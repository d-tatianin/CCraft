#include "Application.h"




int main()
{
	CCraft::Application game;

	while (game.running())
	{
		game.play();
	}

	return 0;
}