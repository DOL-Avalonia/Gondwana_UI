#ifndef GONDWANA_CORE_CORE_H
#define GONDWANA_CORE_CORE_H

#include "Hooks.h"
#include <memory>

namespace Gondwana::Util::System { class Process; }

namespace Gondwana::Core
{

class Core
{

public:
	explicit Core(Util::System::Process * process);

	void OnCraftingLoaded();
	void OnGameStarted();

private:
	Util::System::Process * m_Process;
};

extern std::unique_ptr<Gondwana::Core::Core> s_Core;

}

///// Hooks

#endif GONDWANA_CORE_CORE_H
