#include "PatchNewClasses.h"
#include "MemoryMap.h"
#include "../System/Process.h"

namespace Gondwana::Loader 
{

bool PatchNewClasses::Apply(System::Process & process)
{
	if (m_OldAddress)
		return false;

	if (!process.ReadBytes(MemoryMap::Classes::ClassNamesRefs[0], &m_OldAddress, sizeof(m_OldAddress)))
		return false;

	return false;
}

bool PatchNewClasses::Undo(System::Process & process)
{
	m_OldAddress = nullptr;
	return false;
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



