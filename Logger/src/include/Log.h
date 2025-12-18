#ifndef LOGGER_LOG_H
#define LOGGER_LOG_H

#include "WideStrHelpers.h"

#include <locale>
#include <format>
#include <iostream>

template<typename CharT>                                                                        
struct std::formatter<std::wstring, CharT>                                                          
{                                                                                               
	std::formatter<std::basic_string_view<CharT>> internal;                                     
                                                                                                
	template <class ParseContext>                                                               
	constexpr typename ParseContext::iterator parse(ParseContext& ctx)                          
	{                                                                                           
		return internal.parse(ctx);                                                             
	}                                                                                           
                                                                                                
	template<class FormatContext>                                                               
	typename FormatContext::iterator format(std::wstring f, FormatContext& ctx) const               
	{                                                                                           
		return internal.format(Gondwana::Logger::WideToStr(f), ctx);
	}                                                                                           
};

namespace Gondwana::Logger {

class Log
{
public:
	// TODO(dstaniak) : Initialize output streams.

	template<typename TFormat, typename... Args>
	void Write(TFormat&& format, Args && ... args)
	{
		if constexpr (sizeof...(args) > 0)
			std::cout << std::vformat(format,
				std::make_format_args(args...)) << std::endl;
		else
			std::cout << format << std::endl;
	}
};

extern Log log;

}

#endif // LOGGER_LOG_H

