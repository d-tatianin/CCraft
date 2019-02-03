#pragma once
#include "../VertexArray.h"
#include "../VertexBuffer.h"
#include "../VertexBufferLayout.h"
#include "../Shader.h"
#include "../../vendor/glm/glm.hpp"
#include "../../vendor/glm/gtc/matrix_transform.hpp"

namespace CCraft
{
	class Game
	{
	public:
		glm::mat4 lookAt;
		glm::mat4 projection;
		glm::mat4 model;
		glm::mat4 MVP;
	private:
		VertexArray block;
		VertexBuffer block_buffer;
		Shader gameShader;
	public:
		Game();
		void draw();
	};
}


