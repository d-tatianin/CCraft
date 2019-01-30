#include "Menu.h"
extern int width;
extern int height;

//float button1_data[] = {
//
//	440.0f, 660.0f, -1.0f,
//	440.0f, 540.0f, -1.0f,
//	840.0f, 660.0f, -1.0f,
//	440.0f, 540.0f, -1.0f,
//	840.0f, 540.0f, -1.0f,
//	840.0f, 660.0f, -1.0f
//};

namespace CCraft
{

	Menu::Menu(Button &button1)//also button 2,3 to follow up
		: button1(button1), menuShader("res/shaders/menu.shader"), button1_buffer(button1.data, (18*sizeof(float))), menuMat(1.0f)
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
		else if(button1.mousedOver)
			menuShader.setVec3("color", glm::vec3(0.188f, 0.662f, 0.737f));
		else
			menuShader.setVec3("color", glm::vec3(0.0f, 0.0f, 0.0f));

		button_1.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

}