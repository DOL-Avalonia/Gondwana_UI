#ifndef LOGGER_LOG_H
#define LOGGER_LOG_H

#include <format>
#include <iostream>

namespace Gondwana::Logger {

class Log
{
public:
	// TODO(dstaniak) : Initialize output streams.

	template<typename... Args>
	void Write(char const* format, Args&&... args)
	{
		if constexpr (sizeof...(args) > 0)
			std::cout << std::format(format, std::forward<Args>(args)...) << std::endl;
		else
			std::cout << format << std::endl;
	}

	template<typename TText>
	void Write(TText text)
	{
		std::cout << text << std::endl;
	}

};

extern Log log;

}

#endif // LOGGER_LOG_H

