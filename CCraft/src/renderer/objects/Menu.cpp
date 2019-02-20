#include "Menu.h"
extern int width;
extern int height;
extern CCraft::Shader menuShader;
namespace CCraft
{

	/* 
	TODO:
	- Button initialization happens entirely in the Button class.
	- Button has a .draw() method.
	- Button has a Texture class object, which has a .bind() method.
	- Buttons vector is created in the Renderer class and its reference is shared among Menu and InputHandler classes.
	*/

	Menu::Menu(std::vector<Button>& buttons)
		:buttons(buttons)
	{
		menuMat = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.1f, 100.0f);
	}

	void Menu::draw()
	{
		
		menuShader.Bind();
		menuShader.SetUniformMat4f("menuMat", menuMat);
		menuShader.SetUniform1i("texOne", 0);

		for (Button &but : buttons)
		{
			but.draw();
		}

	}

}