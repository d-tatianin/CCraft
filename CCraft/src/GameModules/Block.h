#pragma once

#include "glad/glad.h"
#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../renderer/Shader.h"

extern CCraft::Shader gameShader;

namespace CCraft
{
	struct Block
	{
	public:
		unsigned int id;
		glm::mat4 coordinates = glm::mat4(1.0f);
	public:
		Block(glm::mat4 translation, int id)
			: id(id), coordinates(translation) {}
	};
}