#include "Menu.h"
extern int width;
extern int height;

namespace CCraft
{

	Menu::Menu(Button &button1, Button &button2, Button &button3)
		: button1(button1), button2(button2), button3(button3), menuShader("res/shaders/menu.shader"), 
		button1_buffer(button1.data, (18*sizeof(float))), button2_buffer(button2.data, (18 * sizeof(float))), 
		button3_buffer(button3.data, (18 * sizeof(float))), menuMat(1.0f)
	{
		//this is an example of how we are going to be initializing elements of the menu
		VertexBufferLayout button_layout_1;
		button_layout_1.Push<float>(3);
		button_1.AddBuffer(button1_buffer, button_layout_1);
		menuMat = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.1f, 100.0f);

		VertexBufferLayout button_layout_2;
		button_layout_2.Push<float>(3);
		button_2.AddBuffer(button2_buffer, button_layout_2);
		menuMat = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.1f, 100.0f);

		VertexBufferLayout button_layout_3;
		button_layout_3.Push<float>(3);
		button_3.AddBuffer(button3_buffer, button_layout_3);
		menuMat = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.1f, 100.0f);
	}

	void Menu::draw()
	{
		menuShader.Bind();
		menuShader.SetUniformMat4f("menuMat", menuMat);

		if (button1.pressed)
		{
			menuShader.setVec3("color", glm::vec3(1.0f, 0.0f, 0.0f));
			playPressed = true;
		}
			
		else if(button1.mousedOver)
			menuShader.setVec3("color", glm::vec3(0.188f, 0.662f, 0.737f));
		else
			menuShader.setVec3("color", glm::vec3(0.0f, 0.0f, 1.0f));

		button_1.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);

		if (button2.pressed)
			menuShader.setVec3("color", glm::vec3(1.0f, 0.0f, 0.0f));
		else if (button2.mousedOver)
			menuShader.setVec3("color", glm::vec3(0.188f, 0.662f, 0.737f));
		else
			menuShader.setVec3("color", glm::vec3(0.0f, 0.0f, 1.0f));

		button_2.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);

		if (button3.pressed)
		{
			menuShader.setVec3("color", glm::vec3(1.0f, 0.0f, 0.0f));
			quitPressed = true;
		}
		else if (button3.mousedOver)
			menuShader.setVec3("color", glm::vec3(0.188f, 0.662f, 0.737f));
		else
			menuShader.setVec3("color", glm::vec3(0.0f, 0.0f, 1.0f));
		
		button_3.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);

	}

}