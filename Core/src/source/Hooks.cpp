#include "Hooks.h"
#include "GameCalls.h"
#include "Util/Process.h"
#include "Core.h"

#include <winsock.h>
#include <windows.h>

namespace Gondwana::Core::Hooks
{

std::vector<Hook> Hooks = 
{
	{ &Hooks::GameStart,      GameCalls::Call_GetGameTicks_GameStart, Hooks::Hook::Opcode::CALL },
	{ &Hooks::CraftingLoaded, GameCalls::Call_LoadCrafting_1,         Hooks::Hook::Opcode::CALL },
	{ &Hooks::CraftingLoaded, GameCalls::Call_LoadCrafting_2,         Hooks::Hook::Opcode::CALL },
};

bool InstallHooks(Util::System::Process & process)
{
	bool result = true;
	for (auto & hook : Hooks)
	{
		result = result && hook.Apply(process);
	}
	return result;
}

bool RemoveHooks(Util::System::Process & process)
{
	bool result = true;
	for (auto& hook : Hooks)
	{
		result = result && hook.Undo(process);
	}
	return result;
}

Hook::Hook(void * hookFunction, void * hookingAddress, Opcode opcode) :
	m_HookingAddress {hookingAddress},
	m_Opcode {opcode}
{
	std::ptrdiff_t EIPoffset = 0;
	switch (opcode)
	{
		case Opcode::CALL: EIPoffset = 4; break;
	}
	m_HookFunctionRelativeAddress = (void *) (std::ptrdiff_t(hookFunction) - (std::ptrdiff_t(m_HookingAddress) + EIPoffset));
}

bool Hook::Apply(Util::System::Process & process)
{
	if (m_PreviousAddress)
		return true; // Already applied.

	return process.WriteBytes(m_HookingAddress, &m_HookFunctionRelativeAddress, sizeof(void *));
}

bool Hook::Undo(Util::System::Process& process)
{
	if (!m_PreviousAddress)
		return false; // Not applied.

	return process.WriteBytes(m_HookingAddress, &m_PreviousAddress, sizeof(void *));
}

long long int GameStart()
{
	s_Core->OnGameStarted();
	return Gondwana::Core::GameCalls::GetGameTicks();
}

unsigned short WriteReceviedPacket(unsigned short i)
{
	return ntohs(i);
}

int CraftingLoaded(int a)
{
	int result = Gondwana::Core::GameCalls::LoadCrafting(a);
	s_Core->OnCraftingLoaded();
	return result;
}

}


