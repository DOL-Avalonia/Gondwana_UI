#ifndef GONDWANA_LOADER_CONFIGURATIONMANAGER_H
#define GONDWANA_LOADER_CONFIGURATIONMANAGER_H

#include "GameConsts.h"

#include <filesystem>
#include <string_view>
#include <string>
#include <vector>

namespace Gondwana::Loader {

class ConfigurationManager
{
public:
	ConfigurationManager(std::vector<std::string_view> args);

	std::filesystem::path GetExeDirectory() const;
	std::filesystem::path GetDaocPath() const;
	std::filesystem::path GetDaocGameExePath() const;
	Core::EncryptionLevel GetInitialEncryption() const;
	Core::EncryptionLevel GetGameEncryption() const;

private:
	enum class ArgIndex
	{
		ExePath,
		DaocPath,
		InitialEncryption,
		GameEncryption
	};

	std::string_view GetStrArg(
		const std::vector<std::string_view> & args, 
		const ArgIndex                        index, 
		const std::string_view                def = "");

	std::filesystem::path m_ExePath           { "" };
	std::filesystem::path m_ExeDirectory      { "" };
	std::string           m_DaocGameExe       { "game.dll" };
	std::filesystem::path m_DaocPath          { "." };
	std::filesystem::path m_DaocGameExePath      { "" };
	Core::EncryptionLevel m_InitialEncryption { Core::EncryptionLevel::NoEncryption };
	Core::EncryptionLevel m_GameEncryption    { Core::EncryptionLevel::NoEncryption };

};

} // Gondwana::Loader

#endif // GONDWANA_LOADER_CONFIGURATIONMANAGER_H

