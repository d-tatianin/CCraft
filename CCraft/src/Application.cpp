#include "Application.h"


namespace CCraft
{
	

	Application::Application()
		: logger("APPLICATION", Logger::INFO)
	{
		input.setWindow(renderer.getWindowID());
	}

	void Application::setMouseCoords(double x, double y)
	{
		input.mouse_callback(x, y);
	}

	bool Application::running()
	{
		return renderer.running;
	}

	void Application::play()
	{
		input.proccess();
		renderer.render();
	}

}
