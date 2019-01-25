#pragma once
#include <iostream>
#include <string>

namespace CCraft {

	class Logger
	{
	public:
		enum level
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
		std::string filterToString(level lvl);
	};

}
