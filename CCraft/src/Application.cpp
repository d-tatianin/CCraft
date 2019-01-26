#include "Application.h"


namespace CCraft
{
	Application::Application()
		: logger("APPLICATION", Logger::INFO)
	{

	}


	bool Application::running()
	{
		return renderer.running;
	}

	void Application::play()
	{
		renderer.render();
	}

}
