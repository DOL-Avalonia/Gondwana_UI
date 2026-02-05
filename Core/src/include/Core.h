#ifndef GONDWANA_CORE_CORE_H
#define GONDWANA_CORE_CORE_H

#include "Util/Process.h"
#include "Hooks.h"
#include <memory>

namespace Gondwana::Core
{

class Core
{

public:
	Core();
	~Core();

	void OnGameStarted();

private:
	std::unique_ptr<Util::System::Process> m_Process;
	Hooks::Hook m_GameStartHook;
};

extern std::unique_ptr<Gondwana::Core::Core> s_Core;

}

///// Hooks

#endif GONDWANA_CORE_CORE_H
