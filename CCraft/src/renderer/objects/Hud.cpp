#include "Hud.h"

namespace CCraft
{
	float crosshairVertices[] =
	{
		630.0f, 370.0f, -1.0f,
		630.0f, 350.0f, -1.0f,
		650.0f, 350.0f, -1.0f,
						
		650.0f, 350.0f, -1.0f,
		650.0f, 370.0f, -1.0f,
		630.0f, 370.0f, -1.0f
	};

	Hud::Hud(float chThickness, FontRenderer& object)
		: projection(1.0f), crosshairBuffer(crosshairVertices, sizeof(crosshairVertices)),
		crosshairShader("res/shaders/crosshair.shader"), color(1.0f, 0.0f, 0.0f), scale(1.0f),
		text(object)
	{
		scale = glm::scale(scale, glm::vec3(chThickness, chThickness, chThickness));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		crosshair.AddBuffer(crosshairBuffer, layout);

		projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, 0.1f, 100.0f);
	}

	void Hud::draw()
	{
		glDisable(GL_DEPTH_TEST);
		crosshairShader.Bind();
		crosshairShader.SetUniformMat4f("projection", projection);
		crosshairShader.SetUniformMat4f("scale", scale);
		crosshairShader.setVec3("color", color);
		crosshair.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6); 
		glEnable(GL_DEPTH_TEST);
	}
}