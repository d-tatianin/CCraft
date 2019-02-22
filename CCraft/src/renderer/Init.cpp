#include "Init.h"

extern int width;
extern int height;

namespace CCraft
{
	Initializer::Initializer()
		: logger("INITIALIZER", Logger::level::INFO)
	{
		parseConfig("res/config.txt");
		initWindow();
		initOpenGL();
	}

	void Initializer::parseConfig(const std::string& configPath)
	{
		enum class configSetting
		{
			NONE = -1, WIDTH = 0, HEIGHT = 1, SENS = 2, DDISTANCE = 3, 
			VSYNC = 4, FULLSCREEN = 5, FOV = 6
		};

		std::ifstream stream(configPath);
		std::string line;
		std::stringstream ss[7];

		configSetting setting = configSetting::NONE;

		while (getline(stream, line))
		{

			if (line.find("width:") != std::string::npos)
				setting = configSetting::WIDTH;
			else if (line.find("height:") != std::string::npos)
				setting = configSetting::HEIGHT;
			else if (line.find("mouse sensitivity:") != std::string::npos)
				setting = configSetting::SENS;
			else if (line.find("draw distance:") != std::string::npos)
				setting = configSetting::DDISTANCE;
			else if (line.find("lock fps:") != std::string::npos)
				setting = configSetting::VSYNC;
			else if (line.find("full screen:") != std::string::npos)
				setting = configSetting::FULLSCREEN;
			else if (line.find("field of view:") != std::string::npos)
				setting = configSetting::FOV;
			else if (setting != configSetting::NONE)
				ss[(int)setting] << line;
		}

		width = atoi((ss[0].str()).c_str());
		height = atoi((ss[1].str()).c_str());
		sensitivity = strtof(ss[2].str().c_str(), 0);
		drawDistance = atoi((ss[3].str()).c_str());
		vsync = atoi((ss[4].str()).c_str());
		fullscreen = atoi((ss[5].str()).c_str());
		fov = strtof(ss[6].str().c_str(), 0);

		if (width < 300 || height < 300)
		{
			logger.log("Couldn't find resolution settings in configuration file, applying default settings.", Logger::level::WARN);
			width = 800;
			height = 600;
		}
		if (!sensitivity)
		{
			logger.log("Couldn't find sensitivity settings in configuration file, applying default settings.", Logger::level::WARN);
			sensitivity = 0.08f;
		}
		if (!fov)
		{
			logger.log("Couldn't find field of view settings in configuration file, applying default settings.", Logger::level::WARN);
			fov = 45.0f;
		}
	}



	void Initializer::initWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		if(fullscreen)
			window = glfwCreateWindow(width, height, "CCraft", glfwGetPrimaryMonitor(), NULL);
		else 
			window = glfwCreateWindow(width, height, "CCraft", NULL, NULL);

		if (window == NULL)
		{
			logger.log("Couldn't initialize the window.", Logger::level::FATAL);
			glfwTerminate();
		}
		else
		{
			glfwMakeContextCurrent(window);
			glfwSwapInterval(vsync);
			logger.log("Window successfully initialized.", Logger::level::INFO);
		}

	}

	void Initializer::initOpenGL()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			logger.log("Failed to initialize GLAD.", Logger::level::FATAL);
		}
		else
			logger.log("OpenGL successfully initialized.", Logger::level::INFO);
	}
}
