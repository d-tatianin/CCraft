#include "renderer/Renderer.h"


int width = -1;
int height = -1;

CCraft::Renderer game;
CCraft::Shader gameShader("res/shaders/game.shader");

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	game.input.mouse_callback(xpos, ypos);
}

int main()
{

	glfwSetCursorPosCallback(game.getWindowID(), mouse_callback);

	while (game.running)
	{
		game.render();
	}

	//std::cin.get();
	return 0;
}