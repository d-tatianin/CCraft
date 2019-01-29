#include "Menu.h"
extern int width;
extern int height;

//float button1_data[] = {
//		400.0f, 660.0f, -1.0f,
//		400.0f, 540.0f, -1.0f,
//		800.0f, 660.0f, -1.0f,
//		400.0f, 540.0f, -1.0f,
//		800.0f, 540.0f, -1.0f,
//		800.0f, 660.0f, -1.0f
//};

float button1_data[] = {

	440.0f, 660.0f, -1.0f,
	440.0f, 540.0f, -1.0f,
	840.0f, 660.0f, -1.0f,
	440.0f, 540.0f, -1.0f,
	840.0f, 540.0f, -1.0f,
	840.0f, 660.0f, -1.0f
};

namespace CCraft
{

	Menu::Menu()
		:menuShader("res/shaders/menu.shader"), button1_buffer(recalculate(button1_data, 18), sizeof(button1_data)), menuMat(1.0f)
	{
		//this is an example of how we are going to be initializing elements of the menu
		VertexBufferLayout button_layout;
		button_layout.Push<float>(3);
		button_1.AddBuffer(button1_buffer, button_layout);
		menuMat = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.1f, 100.0f);
	}

	void Menu::draw()
	{
		menuShader.Bind();
		menuShader.SetUniformMat4f("menuMat", menuMat);

		if (button1.pressed)
			menuShader.setVec3("color", glm::vec3(1.0f, 0.0f, 0.0f));
		else if(button1.mouseOvered)
			menuShader.setVec3("color", glm::vec3(0.188f, 0.662f, 0.737f));
		else
			menuShader.setVec3("color", glm::vec3(0.0f, 0.0f, 0.0f));

		button_1.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}


	//todo automate the recalculate method to automatically recalculate height and width
	float* Menu::recalculate(float data[], int size)
	{
		float unitWidth = (float)width / (float)1280;
		float unitHeight = (float)height / (float)720;

		int widthCounter = 0;
		int heightCounter = 1;

		while (heightCounter < size)
		{
			data[widthCounter] *= unitWidth;
			data[heightCounter] *= unitHeight;
			widthCounter += 3;
			heightCounter += 3;
		}

		//for(int i(0); i<size; i++)
		//{
		//	if (i == 0 || i == 3 || i == 6 || i == 9 || i == 12 || i == 15)
		//		data[i] *= unitWidth;
		//	if (i == 1 || i == 4 || i == 7 || i == 10 || i == 13 || i == 16)
		//		data[i] *= unitHeight;
		//}
		
		return data;
	}
}