#include "logger.h"

namespace CCraft {

	Logger::Logger(const char* programName)
	{
		this->programName = programName;
		filter = level::INFO;
		setFilter(filter);
	}

	Logger::Logger(const char* programName, level filter)
	{
		this->programName = programName;
		this->filter = filter;
		setFilter(filter);
	}

	void Logger::log(const char* message, level lvl)
	{
		std::string level = filterToString(lvl);
		if (lvl >= filter) 
			std::cout << programName << "::" << level << "::" << message << std::endl;
	}

	void Logger::setFilter(level lvl)
	{
		filter = lvl;
	}

	std::string Logger::filterToString(level lvl)
	{
		std::string enumToString;
		if (lvl == level::INFO)
			enumToString = "INFO";
		if (lvl == level::WARN)
			enumToString = "WARNING";
		if (lvl == level::FATAL)
			enumToString = "FATAL";
		return enumToString;
	}
}