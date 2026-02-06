#include "Core.h"
#include "Util/Process.h"
#include "GameCalls.h"
#include "Crafting.h"
#include "GameConsts.h"

namespace Gondwana::Core
{

std::unique_ptr<Gondwana::Core::Core> s_Core;

Core::Core(Util::System::Process * process) :
	m_Process {process}
{}

void Core::OnCraftingLoaded()
{
	// TODO(dstaniak) : Make this more civilised.
	void * cookingAddress = (void*)(std::ptrdiff_t(GameCalls::CraftingInfo) + sizeof(GameData::Crafting::Crafting) * static_cast<size_t>(GameData::CraftingSkill::CookingCrafting));
	void * scholarAddress = (void*)(std::ptrdiff_t(GameCalls::CraftingInfo) + sizeof(GameData::Crafting::Scholar ) * static_cast<size_t>(GameData::CraftingSkill::ScholarCrafting));

	auto result = m_Process->WriteBytes(cookingAddress, &GameData::Crafting::Cooking, sizeof(GameData::Crafting::Crafting));
	result = result && m_Process->WriteBytes(scholarAddress, &GameData::Crafting::Scholar, sizeof(GameData::Crafting::Scholar ));

	if (!result)
		MessageBoxA(nullptr, "Could not load crafting.", "Gondwana", MB_OK | MB_ICONERROR);
}

void Core::OnGameStarted()
{
	// TODO: Put here anything just before player entering the game (all data ready).
}

}

