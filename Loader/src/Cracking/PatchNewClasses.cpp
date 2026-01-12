#include "PatchNewClasses.h"
#include "MemoryMap.h"
#include "../System/Process.h"
#include "Log.h"
#include "GameConsts.h"

#include <array>
#include <memory>

namespace Gondwana::Loader 
{

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
	
	const auto classesCount = static_cast<int>(GameData::CharacterClassNames.rbegin()->first) + 1;
	const size_t memSize = ClassStrLen * classesCount;
	m_NewClasses = process.Alloc(memSize);
	if (m_NewClasses == nullptr)
	{
		Logger::log.Write("NewClasses: cannot allocate memory in process.");
		return false;
	}

	std::unique_ptr<char[]> newClasses(new char[memSize]);
	memset(newClasses.get(), 0, memSize);
	for (const auto& [charClass, className] : GameData::CharacterClassNames)
	{
	 	const auto offset = static_cast<size_t>(charClass) * ClassStrLen;
		memcpy(newClasses.get() + offset, className.c_str(), className.size());
	}

	if (!process.WriteBytes(m_NewClasses, newClasses.get(), memSize))
	{
		Logger::log.Write("NewClasses: cannot write strings into process memory.");
		return false;
	}
	Logger::log.Write("NewClasses: new class strings copied into process memory.");

	if (!PatchAddress(process, m_NewClasses))
	{
		Logger::log.Write("NewClasses: patch applied.");
		return false;
	}

	Logger::log.Write("NewClasses: patch applied.");

	return true;
}

bool PatchNewClasses::Undo(System::Process & process)
{
	if (m_OldAddress == nullptr)
		return false;
	PatchAddress(process, m_OldAddress);
	process.Free(m_NewClasses);
	m_NewClasses = nullptr;
	m_OldAddress = nullptr;
	return true;
}

bool PatchNewClasses::PatchAddress(System::Process& process, void * newDataPtr)
{
	for (auto address : MemoryMap::Classes::ClassNamesRefs)
	{
		if (!process.WriteBytes(address, &newDataPtr, sizeof(newDataPtr)))
			return false;
	}
	return true;
}

} // Gondwana::Loader



