#include "PatchNewClasses.h"
#include "MemoryMap.h"
#include "../System/Process.h"
#include "Log.h"

#include <array>
#include <memory>

namespace Gondwana::Loader 
{

const std::vector<std::string> PatchNewClasses::Classes = {
	"",
	"Acolyte6",
	"AlbionRogue7",
	"Disciple0",
	"Elementalist5",
	"Fighter4",
	"Forester7",
	"Guardian2",
	"Mage8",
	"Magician1",
	"MidgardRogue8",
	"Mystic6",
	"Naturalist3",
	"Seer7",
	"Stalker4",
	"Viking5",
	"Armsman",
	"Cabalist3",
	"Cleric",
	"Friar0",
	"Heretic3",
	"Infiltrator",
	"Mercenary1",
	"Minstrel",
	"Necromancer2",
	"Paladin",
	"Reaver9",
	"Scout",
	"Sorcerer",
	"Theurgist",
	"Wizard",
	"MaulerAlb0",
	"Occultist5",
	"DarkKnight4",
	"RedMage3",
	"ChaosMage6",
	"Psion7",
	"Berserker1",
	"Bonedancer0",
	"Healer6",
	"Hunter5",
	"Runemaster9",
	"Savage2",
	"Shadowblade3",
	"Shaman8",
	"Skald4",
	"Spiritmaster7",
	"Thane1",
	"Valkyrie4",
	"Warlock9",
	"Warrior2",
	"MaulerMid1",
	"HelWarden8",
	"Einherjar9",
	"Geomancer0",
	"Corsair1",
	"Alchemist2",
	"Animist5",
	"Bainshee9",
	"Bard8",
	"Blademaster3",
	"Champion5",
	"Druid7",
	"Eldritch0",
	"Enchanter1",
	"Hero4",
	"Mentalist2",
	"Nightshade9",
	"Ranger0",
	"Valewalker6",
	"Vampiir8",
	"Warden6",
	"MaulerHib2",
	"Reaper3",
	"Dragoon4",
	"BlueMage5",
	"ElementalKnight6",
	"PuppetMaster7"
};

bool PatchNewClasses::Apply(System::Process & process)
{
	Logger::log.Write("NewClasses: Applying ...");

	if (m_OldAddress)
	{
		Logger::log.Write("NewClasses: Already applied.");
		return false;
	}

	if (!process.ReadBytes(MemoryMap::Classes::ClassNamesRefs[0], &m_OldAddress, sizeof(m_OldAddress)))
	{
		Logger::log.Write("NewClasses: cannot read process memory.");
		return false;
	}

	Logger::log.Write("NewClasses: old classes memory is {}.", m_OldAddress);

	const size_t memSize = ClassStrLen * Classes.size();
	m_NewClasses = process.Alloc(memSize);
	if (m_NewClasses == nullptr)
	{
		Logger::log.Write("NewClasses: cannot allocate memory in process.");
		return false;
	}

	std::unique_ptr<char[]> newClasses(new char[memSize]);
	memset(newClasses.get(), 0, memSize);
	size_t offset = 0;
	for (const auto& classStr : Classes)
	{
		memcpy(newClasses.get() + offset, classStr.c_str(), classStr.size());
		offset += ClassStrLen;
	}

	Logger::log.Write("NewClasses: new class strings copied into process memory.");

	if (!process.WriteBytes(m_NewClasses, newClasses.get(), memSize))
	{
		Logger::log.Write("NewClasses: cannot patch code.");
		return false;
	}

	Logger::log.Write("NewClasses: patch applied.");

	return true;
}

bool PatchNewClasses::Undo(System::Process & process)
{
	if (m_OldAddress == nullptr)
		return false;
	Write(process, m_OldAddress);
	process.Free(m_NewClasses);
	m_NewClasses = nullptr;
	m_OldAddress = nullptr;
	return true;
}

bool PatchNewClasses::Write(System::Process& process, void * newDataPtr)
{
	for (auto address : MemoryMap::Classes::ClassNamesRefs)
	{
		if (!process.WriteBytes(address, &newDataPtr, sizeof(newDataPtr)))
			return false;
	}
	return true;
}

} // Gondwana::Loader



