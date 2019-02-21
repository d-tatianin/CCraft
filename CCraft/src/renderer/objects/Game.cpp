#include "Game.h"

extern int width;
extern int height;
extern CCraft::Shader gameShader;

float cube_vertices[] = {
	// front
	-0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
};

unsigned int cube_elements[] = {
	// front
	0, 1, 2,
	2, 3, 0,
	// right
	1, 5, 6,
	6, 2, 1,
	// back
	7, 6, 5,
	5, 4, 7,
	// left
	4, 0, 3,
	3, 7, 4,
	// bottom
	4, 5, 1,
	1, 0, 4,
	// top
	3, 2, 6,
	6, 7, 3
};

namespace CCraft {

	Game::Game(int drawDistance)
		: chunks(drawDistance), lookAt(1.0f), projection(1.0f), block_buffer(cube_vertices, sizeof(cube_vertices)),
		block_indices(cube_elements, sizeof(cube_elements))
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
		gameShader.SetUniformMat4f("projection", projection);
		gameShader.SetUniformMat4f("view", lookAt);
		gameShader.setVec3("color", glm::vec3(0.0f, 0.0f, 0.0f));
		block.Bind();
		block_indices.Bind();
		chunks.bind();
		chunks.draw();
	}

}