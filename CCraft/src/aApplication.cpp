#include "Application.h"
#include <string>
#include <fstream>
#include <sstream>

namespace CCraft
{
	Application::Application()
		: logger("Application", Logger::INFO)
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
			logger.log("Configuration file successfully parsed.", Logger::INFO);
		else
			logger.log("Error parsing configuration file.", Logger::FATAL);
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
			logger.log("Couldn't initialize the window.", Logger::FATAL);
			glfwTerminate();
		}
		else
		{
			glfwMakeContextCurrent(window);
			logger.log("Window successfully initialized.", Logger::INFO);
		}
		
	}

	void Application::initOpenGL()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			logger.log("Failed to initialize GLAD.", Logger::FATAL);
		}
		else
			logger.log("OpenGL successfully initialized.", Logger::INFO);
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
		logger.log("Successfully terminated.", Logger::INFO);
		logger.log("Press enter to continue...", Logger::INFO);
		std::cin.get();
	}
}
