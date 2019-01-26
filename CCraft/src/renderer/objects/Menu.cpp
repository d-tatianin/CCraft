#include "Menu.h"

namespace CCraft
{
	float button1_data[] = {
		-0.5f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.5f, 0.0f, 0.0f
	};

	Menu::Menu()
		:menuShader("res/shaders/menu.shader"), button1_buffer(recalculate(button1_data, 9), sizeof(float) * 9)
	{
		//this is an example of how we are going to be initializing elements of the menu
		VertexBufferLayout button_layout;
		button_layout.Push<float>(3);
		button_1.AddBuffer(button1_buffer, button_layout);
	}

	void Menu::draw()
	{
		menuShader.Bind();
		button_1.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	float* Menu::recalculate(float* data, int size)
	{
		
		//double unit = game.width;
		return data;
	}
}