#include "Button.h"
#include <iostream>
namespace CCraft
{
	Button::Button(float coords[])
		: data(coords)
	{
		recalculateForResolution();
		recalculateForGLFW();
	}

	void Button::recalculateForResolution()
	{
		float unitWidth = (float)width / (float)1280;
		float unitHeight = (float)height / (float)720;

		int widthCounter = 0;
		int heightCounter = 1;

		while (heightCounter < 25)
		{
			data[widthCounter] *= unitWidth;
			data[heightCounter] *= unitHeight;
			widthCounter += 5;
			heightCounter += 5;
		}
	}

	void Button::recalculateForGLFW()
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
	
}
