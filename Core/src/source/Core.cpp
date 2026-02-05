#include "Core.h"
#include "Util/Process.h"
#include "GameCalls.h"
#include "Crafting.h"
#include "GameConsts.h"

namespace Gondwana::Core
{

std::unique_ptr<Gondwana::Core::Core> s_Core;

// TODO(dstaniak) : Take away hooks from here. Make hooks class which will do the hooking and unhooking and call the Core instance.
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
	void * cookingAddress = (void*)(std::ptrdiff_t(GameCalls::CraftingInfo) + sizeof(GameData::Crafting::Crafting) * static_cast<size_t>(GameData::CraftingSkill::CookingCrafting));
	void * scholarAddress = (void*)(std::ptrdiff_t(GameCalls::CraftingInfo) + sizeof(GameData::Crafting::Scholar ) * static_cast<size_t>(GameData::CraftingSkill::ScholarCrafting));

	auto result = m_Process->WriteBytes(cookingAddress, &GameData::Crafting::Cooking, sizeof(GameData::Crafting::Crafting));
	result = result && m_Process->WriteBytes(scholarAddress, &GameData::Crafting::Scholar, sizeof(GameData::Crafting::Scholar ));

	if (!result)
		MessageBoxA(nullptr, "Could not apply crafting patch!", "Gondwana", MB_OK | MB_ICONERROR);
}

}

