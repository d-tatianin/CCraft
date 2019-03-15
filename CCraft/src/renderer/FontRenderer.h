#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>
#include <string>
#include "../logger/Logger.h"
#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "Shader.h"


namespace CCraft
{
	class FontRenderer
	{
	private:

		struct Character
		{
			unsigned int texID;
			glm::ivec2 size;
			glm::ivec2 bearing;
			unsigned int advance;
		};

		Logger logger;
		FT_Library ft;
		FT_Face face;
		std::map<char, Character> characters;

		Shader fontShader;

		glm::mat4 projection;

		unsigned int VAO;
		unsigned int VBO;

	public:

		enum class Color
		{
			RED = 0, BLUE = 1, GREEN = 2, PURPLE = 3,
			ORANGE = 4, BLACK = 5, WHITE = 6
		};

		FontRenderer();
		void renderText(std::string text, float x, float y, float size, Color color);
	private:
		void loadCharacters();
		glm::vec3 colorToVec3(Color color);

	};
}

