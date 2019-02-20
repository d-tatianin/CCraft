#include "Button.h"
#include "../Shader.h"
#include <iostream>

extern CCraft::Shader menuShader;

namespace CCraft
{
	Button::Button(float* coords, Action onClick, Color defColor, Color mousedOverColor, Color pressedColor, const char* texPath)
		: defColor(defColor), mousedOverColor(mousedOverColor), pressedColor(pressedColor), onClick(onClick),
		buttonVBO(recalculateForResolution(coords), 120), buttonTexture(texPath)
	{
		VertexBufferLayout buttonLayout;
		buttonLayout.Push<float>(3);
		buttonLayout.Push<float>(2);
		buttonVAO.AddBuffer(buttonVBO, buttonLayout);
		recalculateForGLFW(coords);
	}

	float* Button::recalculateForResolution(float* data)
	{
		float unitWidth = (float)width / (float)1280;
		float unitHeight = (float)height / (float)720;

		int widthCounter = 0;
		int heightCounter = 1;

		while (heightCounter < 30)
		{
			data[widthCounter] *= unitWidth;
			data[heightCounter] *= unitHeight;
			widthCounter += 5;
			heightCounter += 5;
		}
		return data;
	}

	void Button::recalculateForGLFW(float* data)
	{
		int widthCounter = 0;
		int heightCounter = 1;
		float smallestX = 10000.0f;
		float smallestY = 10000.0f;
		float biggestX = -200.0f;
		float biggestY = -200.0f;

		while (heightCounter < 23)
		{
			if (data[widthCounter] < smallestX)
				smallestX = data[widthCounter];
			if (data[widthCounter] > biggestX)
				biggestX = data[widthCounter];
			if (data[heightCounter] < smallestY)
				smallestY = data[heightCounter];
			if (data[heightCounter] > biggestY)
				biggestY = data[heightCounter];
			widthCounter += 5;
			heightCounter += 5;
		}

		recalculatedData[0] = smallestX;
		recalculatedData[1] = ((biggestY - height) * -1);
		recalculatedData[2] = biggestX;
		recalculatedData[3] = ((smallestY - height) * -1);
	}

	void Button::draw()
	{
		if (pressed)
			menuShader.setVec3("color", colorToVec3(pressedColor));
		else if (mousedOver)
			menuShader.setVec3("color", colorToVec3(mousedOverColor));
		else
			menuShader.setVec3("color", colorToVec3(defColor));
		
		buttonVAO.Bind();
		buttonTexture.bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	glm::vec3 Button::colorToVec3(Color color)
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
