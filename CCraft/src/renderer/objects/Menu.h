#pragma once

#include "../VertexArray.h"
#include "../VertexBuffer.h"
#include "../VertexBufferLayout.h"
#include "../Shader.h"
#include "../../vendor/glm/glm.hpp"
#include "../../vendor/glm/gtc/matrix_transform.hpp"

namespace CCraft
{
	class Menu
	{
	private:
		VertexArray button_1;
		VertexBuffer button1_buffer;
		//an example of creating a buffer for each button
		//VertexArray button_2;
		//VertexBuffer button2_buffer;
		//VertexArray button_3;
		//VertexBuffer button3_buffer;
		Shader menuShader;
		glm::mat4 menuMat;
	public:
		Menu();
		//~Menu();
		void draw();
		//void update();
	private:
		float* recalculate(float data[], int size);
	};
	

}