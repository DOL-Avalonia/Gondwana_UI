#include "Log.h"
#include "Config/ConfigurationManager.h"
#include "System/Process.h"
#include "Cracking/MemoryMap.h"
#include "Cracking/PatchNewClasses.h"
#include "GameConsts.h"

#include <string>
#include <chrono>
#include <thread>
#include <windows.h>

int main(int argc, char* argv[])
{
	using namespace Gondwana;
	using namespace Gondwana::Loader;
	using namespace std::string_literals;
	using Logger::log;

	log.Write("*** Gondwana Loader * 2025 (C) IDClick ***");

	//ConfigurationManager config({ argv, argv + argc });

	const std::wstring daocPath = L"I:\\src\\upwork\\IDClick\\DAoC";
	std::wstring daocGameDll = daocPath + L"\\game.exe";
	unsigned short port = 10300;
	std::wstring address = L"127.0.0.1";
	int worldId = 1;
	std::wstring userName = L"daroking";
	std::wstring password = L"passpass";
	std::wstring commandLine = L".\\game.dll " +
		address + L" " + std::to_wstring(port) + L" " + std::to_wstring(worldId) + L" " + userName + L" " + password;

	log.Write("Starting process : {}", daocGameDll);
	log.Write("Command line arguments : {}", commandLine);

	System::Process process{ daocGameDll, commandLine, daocPath, true, false };
	process.Create();

	log.Write("Injecting patches ...");

	constexpr auto EncryptionLevel = Core::EncryptionLevel::NoEncryption;

	if (!process.WriteBytes(MemoryMap::InitialEncryptionLevel, (void*)&EncryptionLevel, sizeof(EncryptionLevel)))
	{
		log.Write("Patching encryption level failed.");
		return -1;
	}

	if (!process.WriteBytes(MemoryMap::GameEncryptionLevel, (void*)&EncryptionLevel, sizeof(EncryptionLevel)))
	{
		log.Write("Patching encryption level failed.");
		return -1;
	}

	PatchNewClasses patchNewClasses;

	if (!patchNewClasses.Apply(process))
	{
		log.Write("Patching new classes failed.");
		return -1;
	}
	
	log.Write("Resuming the process' main thread.");
	process.Start();
	log.Write("Waiting for the process to exit ...");
	process.Join();
	
	return 0;
}

