#ifndef GONDWANA_LOGGER_WIDESTRHELPERS_H
#define GONDWANA_LOGGER_WIDESTRHELPERS_H

#include <string>

namespace Gondwana::Logger {

std::wstring StrToWide(const std::string & string);
std::string WideToStr(const std::wstring & wide_string);

}

#endif GONDWANA_LOGGER_WIDESTRHELPERS_H

