#include "Log.h"
#include "Config/ConfigurationManager.h"

#include <string>
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
	std::wstring daocGameDll = daocPath + L"\\game.dll";
	unsigned short port = 10300;
	std::wstring address = L"127.0.0.1";
	int worldId = 1;
	std::wstring userName = L"daroking";
	std::wstring password = L"passpass";

	log.Write("Starting process : {}", daocGameDll);

	
	return 0;
}

