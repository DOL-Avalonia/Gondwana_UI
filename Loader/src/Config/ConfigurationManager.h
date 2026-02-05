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
	ConfigurationManager();

	std::filesystem::path GetExeDirectory() const;
	std::filesystem::path GetCoreDllPath() const;

	std::filesystem::path GetDaocPath() const;
	std::wstring GetDaocGameExe() const;
	std::filesystem::path GetDaocGameExePath() const;

	std::wstring GetServerAddress() const;
	unsigned short GetServerPort() const;
	int GetWorldId() const;
	std::wstring GetLogin() const;
	std::wstring GetPassword() const;

	GameData::EncryptionLevel GetInitialEncryption() const;
	GameData::EncryptionLevel GetGameEncryption() const;

	std::wstring GetGameDllCommandLine() const;

private:
	enum class ArgIndex
	{
		ExePath,
		DaocPath,
		DaocGameExe,
		ServerAddress,
		ServerPort,
		WorldId,
		Login,
		Password
	};

	std::wstring_view GetStrArg(
		const std::vector<std::wstring_view> & args, 
		const ArgIndex                         index, 
		const std::wstring_view                def = L"");

	int GetIntArg(
		const std::vector<std::wstring_view> & args, 
		const ArgIndex                         index, 
		const int                              def = 0);

/*
I:\src\upwork\IDClick\DAoC game.exe 127.0.0.1 10300 daroking passpass

	const std::wstring daocPath = L"I:\\src\\upwork\\IDClick\\DAoC";
	std::wstring daocGameDll = daocPath + L"\\game.exe";
	unsigned short port = 10300;
	std::wstring address = L"127.0.0.1";
	int worldId = 1;
	std::wstring userName = L"daroking";
	std::wstring password = L"passpass";
	std::wstring commandLine = L".\\game.exe " +
		address + L" " + std::to_wstring(port) + L" " + std::to_wstring(worldId) + L" " + userName + L" " + password;


*/

	std::filesystem::path m_ExePath               { "" };
	std::filesystem::path m_ExeDirectory          { "" };
	std::filesystem::path m_CoreDllPath           { "" };

	std::filesystem::path m_DaocPath              { "." };
	std::wstring          m_DaocGameExe           { L"game.dll" };
	std::filesystem::path m_DaocGameExePath       { "" };

	std::wstring          m_ServerAddress         { L"127.0.0.1" };
	unsigned short        m_ServerPort            { 10300 };
	int                   m_WorldId               { 1 };
	std::wstring          m_Login                 { L"" };
	std::wstring          m_Password              { L"" };

	GameData::EncryptionLevel m_InitialEncryption { GameData::EncryptionLevel::NoEncryption };
	GameData::EncryptionLevel m_GameEncryption    { GameData::EncryptionLevel::NoEncryption };

};

} // Gondwana::Loader

#endif // GONDWANA_LOADER_CONFIGURATIONMANAGER_H

