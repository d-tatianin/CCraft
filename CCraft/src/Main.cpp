#include "Application.h"

int width = -1;
int height = -1;

CCraft::Application game;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	game.setMouseCoords(xpos, ypos);
}

int main()
{

	glfwSetCursorPosCallback(game.renderer.getWindowID(), mouse_callback);

	while (game.running())
	{
		game.play();
	}

	return 0;
}