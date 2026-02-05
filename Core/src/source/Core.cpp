#include "Core.h"
#include "Util/Process.h"
#include "GameCalls.h"

namespace Gondwana::Core
{

std::unique_ptr<Gondwana::Core::Core> s_Core;

Core::Core() :
	m_GameStartHook{ &Hooks::GameStart, GameCalls::Call_GetGameTicks_GameStart, Hooks::Hook::Opcode::CALL }
{
	m_Process.reset(new Util::System::Process());

	m_GameStartHook.Apply(*m_Process);
}

Core::~Core()
{
	if (!m_Process)
		return;

	m_GameStartHook.Undo(*m_Process);
}

void Core::OnGameStarted()
{
	MessageBoxA(nullptr, "Game started.", "Gondwana", MB_OK | MB_ICONINFORMATION);
}

}

