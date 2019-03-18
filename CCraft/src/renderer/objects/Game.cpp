#include "Game.h"

extern int width;
extern int height;
extern CCraft::Shader gameShader;

float cube_vertices[] = {
	0.0f, 0.0f, 0.0f,  0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
	1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
	0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	0.0f, 0.0f, 0.0f,  0.0f, 0.0f,

	0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
	1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
	1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	0.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,  0.0f, 0.0f,

	0.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
	0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
	0.0f, 1.0f, 1.0f,  1.0f, 0.0f,

	1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
	1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	1.0f, 0.0f, 1.0f,  0.0f, 0.0f,
	1.0f, 1.0f, 1.0f,  1.0f, 0.0f,

	0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
	1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
	1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

	0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	0.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,  0.0f, 1.0f
};

unsigned int cube_elements[] = {
	0, 1, 2, 3, 4, 5, 6,
	7, 8, 9, 10, 11, 12,
	13, 14, 15, 16, 17, 18,
	19, 20, 21, 22, 23, 24,
	25, 26, 27, 28, 29, 30,
	31, 32, 33, 34, 35
};

namespace CCraft {

	Game::Game(int drawDistance, float fov, float chThickness, FontRenderer& object, glm::vec3& playerCoordinates)
		: chunks(drawDistance, playerCoordinates), lookAt(1.0f), projection(1.0f), block_buffer(cube_vertices, sizeof(cube_vertices)),
		block_indices(cube_elements, sizeof(cube_elements)), fov(fov), hud(chThickness, object)
	{
		projection = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 100.0f);
		VertexBufferLayout block_layout;
		block_layout.Push<float>(3);
		block_layout.Push<float>(2);
		block.AddBuffer(block_buffer, block_layout);
		
	}

	void Game::draw()
	{
		glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		gameShader.Bind();
		gameShader.SetUniformMat4f("projection", projection);
		gameShader.SetUniformMat4f("view", lookAt);
		gameShader.setVec3("color", glm::vec3(0.0f, 0.0f, 0.0f));
		block.Bind();
		block_indices.Bind();
		chunks.updateActiveChunks();
		chunks.draw();
		hud.draw();
	}

}