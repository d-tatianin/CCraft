#pragma once
#include "../VertexArray.h"
#include "../VertexBuffer.h"
#include "../VertexBufferLayout.h"
#include "../Shader.h"
#include "../../vendor/glm/glm.hpp"
#include "../../vendor/glm/gtc/matrix_transform.hpp"
#include "../../GameModules/ChunkController.h"
namespace CCraft
{
	class Game
	{
	public:
		ChunkController chunks;
		glm::mat4 lookAt;
		glm::mat4 projection;
	private:
		VertexArray block;
		VertexBuffer block_buffer;
	public:
		Game();
		void draw();
	};
}


