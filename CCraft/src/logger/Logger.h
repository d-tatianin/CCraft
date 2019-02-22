#pragma once
#include <iostream>

namespace CCraft
{
	class Logger
	{
	public:
		enum class level
		{
			INFO = 0, WARN = 1, FATAL = 2
		};
	private:
		level filter;
		const char* programName;
	public:
		Logger(const char* programName);
		Logger(const char* programName, level filter);
		void log(const char* message, level lvl);
		void setFilter(level lvl);
	private:
		const char* filterToString(level& lvl);
	};

}
