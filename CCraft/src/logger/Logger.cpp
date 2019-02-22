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

	const char* Logger::filterToString(level& lvl)
	{
		if (lvl == level::INFO)
			return "INFO";
		else if (lvl == level::WARN)
			return "WARNING";
		else if (lvl == level::FATAL)
			return "FATAL";
		else
			return "UNKNOWN";
	}
}

