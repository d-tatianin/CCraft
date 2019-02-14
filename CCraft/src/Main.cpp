#include "renderer/Renderer.h"


int width = -1;
int height = -1;

CCraft::Renderer game;

//Has to be initialized here because multiple classes require access to the shader.
CCraft::Shader gameShader("res/shaders/game.shader");

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	game.input.mouse_callback(xpos, ypos);
}

int main()
{
	glfwSwapInterval(1);
	glfwSetCursorPosCallback(game.getWindowID(), mouse_callback);

	while (game.running)
	{
		game.render();
	}

	//std::cin.get();
	return 0;
}