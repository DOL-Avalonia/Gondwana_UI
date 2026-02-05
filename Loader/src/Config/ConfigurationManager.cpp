#include "ConfigurationManager.h"
#include "Log.h"

#include <Windows.h>

namespace Gondwana::Loader {

ConfigurationManager::ConfigurationManager()
{
	int argc;
	auto argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	std::vector<std::wstring_view> args{argv, argv + argc};

	m_ExePath = GetStrArg(args, ArgIndex::ExePath, m_ExePath.wstring());
	m_ExeDirectory = m_ExePath.parent_path();
	m_CoreDllPath = m_ExeDirectory;
	m_CoreDllPath.append("Core.dll");

	m_DaocPath = GetStrArg(args, ArgIndex::DaocPath, m_DaocPath.wstring());
	m_DaocGameExe = GetStrArg(args, ArgIndex::DaocGameExe, m_DaocGameExe);
	m_DaocGameExePath = m_DaocPath;
	m_DaocGameExePath.append(m_DaocGameExe);

	m_ServerAddress = GetStrArg(args, ArgIndex::ServerAddress, m_ServerAddress);
	m_ServerPort = static_cast<decltype(m_ServerPort)>(GetIntArg(args, ArgIndex::ServerPort, m_ServerPort));
	m_WorldId = GetIntArg(args, ArgIndex::WorldId, m_WorldId);
	m_Login = GetStrArg(args, ArgIndex::Login, m_Login);
	m_Password = GetStrArg(args, ArgIndex::Password, m_Password);

	using Logger::log;

	log.Write("Configuration :");
	log.Write("- DAoC game : {}", m_DaocGameExePath.wstring());
	log.Write("- Server : {}:{} [{}]", m_ServerAddress, m_ServerPort, m_WorldId);
	log.Write("- Login : {}", m_Login);
}

std::filesystem::path ConfigurationManager::GetExeDirectory() const
{
	return m_ExeDirectory;
}

std::filesystem::path ConfigurationManager::GetDaocPath() const
{
	return m_DaocPath;
}

std::wstring ConfigurationManager::GetDaocGameExe() const
{
	return m_DaocGameExe;
}

std::filesystem::path ConfigurationManager::GetDaocGameExePath() const
{
	return m_DaocGameExePath;
}

std::filesystem::path ConfigurationManager::GetCoreDllPath() const
{
	return m_CoreDllPath;
}

std::wstring ConfigurationManager::GetServerAddress() const
{
	return m_ServerAddress;
}

unsigned short ConfigurationManager::GetServerPort() const
{
	return m_ServerPort;
}

int ConfigurationManager::GetWorldId() const
{
	return m_WorldId;
}

std::wstring ConfigurationManager::GetLogin() const
{
	return m_Login;
}

std::wstring ConfigurationManager::GetPassword() const
{
	return m_Password;
}

GameData::EncryptionLevel ConfigurationManager::GetInitialEncryption() const
{
	return m_InitialEncryption;
}

GameData::EncryptionLevel ConfigurationManager::GetGameEncryption() const
{
	return m_GameEncryption;
}

std::wstring ConfigurationManager::GetGameDllCommandLine() const
{
	return std::wstring
	{
		L".\\" + GetDaocGameExe() + L" " +
		GetServerAddress() + L" " +
		std::to_wstring(GetServerPort()) + L" " +
		std::to_wstring(GetWorldId()) + L" " +
		GetLogin() + L" " +
		GetPassword()
	};
}

std::wstring_view ConfigurationManager::GetStrArg(
	const std::vector<std::wstring_view> & args, 
	const ArgIndex                         index, 
	const std::wstring_view                def)
{
	const size_t i = static_cast<size_t>(index);
	if (i >= args.size())
		return def;

	return args[i];
}

int ConfigurationManager::GetIntArg(
	const std::vector<std::wstring_view>& args, 
	const ArgIndex index, 
	const int def)
{
	const size_t i = static_cast<size_t>(index);
	if (i >= args.size())
		return def;

	return std::stoi(std::wstring(args[i]));
}

} // Gondwana::Loader
