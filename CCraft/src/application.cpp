#include "application.h"
#include <string>
#include <fstream>
#include <sstream>

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

	void Application::parseConfig(const std::string& configPath)
	{
		enum class configSetting
		{
			NONE = -1, WIDTH = 0, HEIGHT = 1
		};

		std::ifstream stream(configPath);
		std::string line;
		std::stringstream ss[2];
		
		configSetting setting = configSetting::NONE;

		while (getline(stream, line))
		{

			if (line.find("width:") != std::string::npos)
				setting = configSetting::WIDTH;
			else if (line.find("height:") != std::string::npos)
				setting = configSetting::HEIGHT;
			else if (setting != configSetting::NONE)
				ss[(int)setting] << line;
		}

		width = atoi((ss[0].str()).c_str());
		height = atoi((ss[1].str()).c_str());

		if (width != -1 && height != -1)
			std::cout << "Configuration file successfully parsed." << std::endl;
		else
			std::cout << "Error parsing configuration file." << std::endl;
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
