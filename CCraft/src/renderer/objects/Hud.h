#pragma once

#include "../VertexArray.h"
#include "../VertexBuffer.h"
#include "../VertexBufferLayout.h"
#include "../Shader.h"
#include "../../vendor/glm/glm.hpp"
#include "../../vendor/glm/gtc/matrix_transform.hpp"

namespace CCraft
{
	class Hud
	{
	private:
		glm::mat4 projection;
		VertexArray crosshair;
		VertexBuffer crosshairBuffer;
		Shader crosshairShader;
		glm::mat4 scale;
	public:
		glm::vec3 color;
	public:
		Hud(float chThickness);
		void draw();
	};
}

