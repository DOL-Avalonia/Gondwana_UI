#include "ConfigurationManager.h"
#include "Log.h"

namespace Gondwana::Loader {

ConfigurationManager::ConfigurationManager(std::vector<std::string_view> args)
{
	m_ExePath = GetStrArg(args, ArgIndex::ExePath, m_ExePath.string());
	m_ExeDirectory = m_ExePath.parent_path();

	m_DaocPath = GetStrArg(args, ArgIndex::DaocPath, m_DaocPath.string());
	m_DaocGameExePath = m_DaocPath.append(m_DaocGameExe);

	using Logger::log;
}

std::filesystem::path ConfigurationManager::GetExeDirectory() const
{
	return m_ExeDirectory;
}

std::filesystem::path ConfigurationManager::GetDaocPath() const
{
	return m_DaocPath;
}

std::filesystem::path ConfigurationManager::GetDaocGameExePath() const
{
	return m_DaocGameExePath;
}

Core::EncryptionLevel ConfigurationManager::GetInitialEncryption() const
{
	return m_InitialEncryption;
}

Core::EncryptionLevel ConfigurationManager::GetGameEncryption() const
{
	return m_GameEncryption;
}

std::string_view ConfigurationManager::GetStrArg(
	const std::vector<std::string_view> & args, 
	const ArgIndex                        index, 
	const std::string_view                def)
{
	const size_t i = static_cast<size_t>(index);
	if (i >= args.size())
		return def;

	return args[i];
}

} // Gondwana::Loader
