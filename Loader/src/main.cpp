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

	ConfigurationManager config;

	log.Write("Starting process : {}", config.GetDaocGameExePath().wstring());

	System::Process process
	{ 
		config.GetDaocGameExePath().wstring(), 
		config.GetGameDllCommandLine(), 
		config.GetDaocPath().wstring(), 
		true, 
		false
	};

	if (!process.Create())
	{
		log.Write("Could not start process.");
		return -1;
	}

	log.Write("Injecting patches ...");

	constexpr auto EncryptionLevel = GameData::EncryptionLevel::NoEncryption;

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

