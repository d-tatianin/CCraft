#include "application.h"

namespace CCraft
{
	Application::Application()
	{
		launch();
	}

	Application::~Application()
	{
		shutDown();
	}

	void Application::launch()
	{
		parseConfig("res/config.txt");
		initWindow();
		initOpenGL();
	}

	void Application::parseConfig(const char* configPath)
	{
		std::cout << "Configuration file successfully parsed." << std::endl;
	}

	void Application::initWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(width, height, "CCraft", NULL, NULL);

		if (window == NULL)
		{
			std::cout << "Couldn't initialize the window." << std::endl;
			glfwTerminate();
		}
		else
		{
			glfwMakeContextCurrent(window);
			std::cout << "Window successfully initialized." << std::endl;
		}
		
	}

	void Application::initOpenGL()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD." << std::endl;
		}
		else
			std::cout << "OpenGL successfully initialized." << std::endl;
	}

	bool Application::running()
	{
		if (glfwWindowShouldClose(window))
			return false;
		else
			return true;
	}

	void Application::play()
	{
		//rendering starts
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//post rendering tasks
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	void Application::shutDown()
	{
		glfwTerminate();
		std::cout << "Successfully terminated." << std::endl;
		std::cout << "Press enter to continue..." << std::endl;
		std::cin.get();
	}
}
