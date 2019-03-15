#include "FontRenderer.h"

extern int width;
extern int height;

namespace CCraft
{
	FontRenderer::FontRenderer()
		: logger("FONT_RENDERER"), fontShader("res/shaders/font.shader"), projection(1.0f)
	{
		projection = glm::ortho(0.0f, (float)width, 0.0f, (float)height);
		if (FT_Init_FreeType(&ft))
			logger.log("Failed to initialize FreeType library.", Logger::level::FATAL);

		if (FT_New_Face(ft, "res/fonts/arial.ttf", 0, &face))
			logger.log("Failed to load font.", Logger::level::FATAL);

		FT_Set_Pixel_Sizes(face, 0, 48);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		loadCharacters();

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void FontRenderer::renderText(std::string text, float x, float y, float size, Color color)
	{
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		fontShader.Bind();
		fontShader.setVec3("color", colorToVec3(color));
		fontShader.SetUniformMat4f("projection", projection);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(VAO);

		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++)
		{
			Character ch = characters[*c];

			float xpos = x + ch.bearing.x * size;
			float ypos = y - (ch.size.y - ch.bearing.y) * size;
			
			float w = ch.size.x * size;
			float h = ch.size.y * size;
			
			float vertices[6][4] = {
				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos,     ypos,       0.0, 1.0 },
				{ xpos + w, ypos,       1.0, 1.0 },

				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos + w, ypos,       1.0, 1.0 },
				{ xpos + w, ypos + h,   1.0, 0.0 }
			};
			
			glBindTexture(GL_TEXTURE_2D, ch.texID);
			
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			
			glDrawArrays(GL_TRIANGLES, 0, 6);
			x += (ch.advance >> 6) * size; 
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_CULL_FACE);
		glDisable(GL_BLEND);
	}

	void FontRenderer::loadCharacters()
	{
		for (unsigned char c = 0; c < 128; c++)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				logger.log("Failed to load glyph.", Logger::level::FATAL);
				continue;
			}
			
			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			
			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};
			characters.insert(std::make_pair(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		FT_Done_Face(face);
		FT_Done_FreeType(ft);
	}

	glm::vec3 FontRenderer::colorToVec3(Color color)
	{
		if (color == Color::RED)
			return glm::vec3(1.0f, 0.0f, 0.0f);
		else if (color == Color::GREEN)
			return glm::vec3(0.0f, 1.0f, 0.0f);
		else if (color == Color::BLUE)
			return glm::vec3(0.0f, 0.0f, 1.0f);
		else if (color == Color::PURPLE)
			return glm::vec3(1.0f, 0.0f, 1.0f);
		else if (color == Color::ORANGE)
			return glm::vec3(1.0f, 0.55f, 0.0f);
		else if (color == Color::BLACK)
			return glm::vec3(0.0f, 0.0f, 0.0f);
		else if (color == Color::WHITE)
			return glm::vec3(1.0f, 1.0f, 1.0f);
		else
			return glm::vec3(0.0f, 0.0f, 0.0f);
	}
}