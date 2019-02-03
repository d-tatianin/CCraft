#include "Game.h"
//tempo
extern int width;
extern int height;

float vertices[] = {
	//back right
	-0.5f, -0.5f, -0.5f, 
	 0.5f, -0.5f, -0.5f, 
	 0.5f,  0.5f, -0.5f, 
	 //back left
	 0.5f,  0.5f, -0.5f, 
	-0.5f,  0.5f, -0.5f, 
	-0.5f, -0.5f, -0.5f, 

	//front right
	-0.5f, -0.5f,  0.5f, 
	 0.5f, -0.5f,  0.5f, 
	 0.5f,  0.5f,  0.5f, 
	 //front left
	 0.5f,  0.5f,  0.5f, 
	-0.5f,  0.5f,  0.5f, 
	-0.5f, -0.5f,  0.5f, 

	//side right
	-0.5f,  0.5f,  0.5f, 
	-0.5f,  0.5f, -0.5f, 
	-0.5f, -0.5f, -0.5f, 
	//side left
	-0.5f, -0.5f, -0.5f, 
	-0.5f, -0.5f,  0.5f, 
	-0.5f,  0.5f,  0.5f, 

	//side right
	 0.5f,  0.5f,  0.5f, 
	 0.5f,  0.5f, -0.5f, 
	 0.5f, -0.5f, -0.5f, 
	 //side left
	 0.5f, -0.5f, -0.5f, 
	 0.5f, -0.5f,  0.5f, 
	 0.5f,  0.5f,  0.5f, 

	 //bottom right
	-0.5f, -0.5f, -0.5f, 
	 0.5f, -0.5f, -0.5f, 
	 0.5f, -0.5f,  0.5f, 
	 //bottom left
	 0.5f, -0.5f,  0.5f, 
	-0.5f, -0.5f,  0.5f, 
	-0.5f, -0.5f, -0.5f, 

	//top right
	-0.5f,  0.5f, -0.5f, 
	 0.5f,  0.5f, -0.5f, 
	 0.5f,  0.5f,  0.5f, 
	 //top left
	 0.5f,  0.5f,  0.5f, 
	-0.5f,  0.5f,  0.5f, 
	-0.5f,  0.5f, -0.5f 
};

namespace CCraft {

	Game::Game()
		: lookAt(1.0f), projection(1.0f), model(1.0f), block_buffer(vertices, sizeof(vertices)), gameShader("res/shaders/game.shader")
	{
		projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
		VertexBufferLayout block_layout;
		block_layout.Push<float>(3);
		block.AddBuffer(block_buffer, block_layout);
	}

	void Game::draw()
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		gameShader.Bind();
		gameShader.SetUniformMat4f("MVP", projection*model*lookAt);
		gameShader.setVec3("color", glm::vec3(0.0f, 1.0f, 0.0f));
		block.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

}