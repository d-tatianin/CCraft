#pragma once
#include "../Shader.h"
#include "../../vendor/glm/glm.hpp"
#include "../../vendor/glm/gtc/matrix_transform.hpp"
#include "Button.h"
#include <vector>

namespace CCraft
{
	class Menu
	{
	private:
		glm::mat4 menuMat;
		std::vector<Button>& buttons;
	public:
		Menu(std::vector<Button>& buttons);
		void draw();
	};
	

}