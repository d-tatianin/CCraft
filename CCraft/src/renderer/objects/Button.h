#pragma once
#include "../VertexArray.h"
#include "../VertexBuffer.h"
#include "../VertexBufferLayout.h"
#include "../Texture.h"
#include "../../vendor/glm/glm.hpp"
#include <array>

extern int width;
extern int height;


namespace CCraft
{
	class Button
	{
	public:
		enum class Action
		{
			NONE = 0, PLAY = 1, EXIT = 2, SETTINGS = 3
		};

		enum class Color
		{
			RED = 0, BLUE = 1, GREEN = 2, PURPLE = 3,
			ORANGE = 4, BLACK = 5, WHITE = 6
		};

	public:
		bool mousedOver = false;
		bool pressed = false;
		Color defColor;
		Color mousedOverColor;
		Color pressedColor;
		Action onClick;
		float recalculatedData[4];
	private:
		VertexArray buttonVAO;
		VertexBuffer buttonVBO;
		Texture buttonTexture;
	public:
		Button(float* coords, Action onClick, Color defColor, Color mousedOverColor, Color pressedColor, const char* texPath);
		void draw();
	private:
		float* recalculateForResolution(float* data);
		void recalculateForGLFW(float* data);
		glm::vec3 colorToVec3(Color color);
	};
}