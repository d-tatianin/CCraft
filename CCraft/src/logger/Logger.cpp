#include "Logger.h"

namespace CCraft
{
	Logger::Logger(const char* programName)
		: filter(level::INFO), programName(programName)
	{
		setFilter(filter);
	}

	Logger::Logger(const char* programName, level filter)
		: filter(filter), programName(programName)
	{
		setFilter(filter);
	}

	void Logger::log(const char* message, level lvl)
	{
		const char* level = filterToString(lvl);
		if (lvl >= filter)
			std::cout << programName << "::" << level << "::" << message << std::endl;
	}

	void Logger::setFilter(level lvl)
	{
		filter = lvl;
	}

	const char* Logger::filterToString(level lvl)
	{
		if (lvl == level::INFO)
		{
			const char* string = "INFO";
			return string;
		}
		else if (lvl == level::WARN)
		{
			const char* string = "WARNING";
			return string;
		}
		else if (lvl == level::FATAL)
		{
			const char* string = "FATAL";
			return string;
		}
	}
}

