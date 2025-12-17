#ifndef GONDWANA_CORE_SHAREDMEMORYMAP_H
#define GONDWANA_CORE_SHAREDMEMORYMAP_H

#include "GameConsts.h"

namespace Gondwana::Core {

struct SharedMemoryMap
{
	EncryptionLevel InitialEncryptionLevel { EncryptionLevel::Initial };
	EncryptionLevel GameEncryptionLevel { EncryptionLevel::Full };
};

} // Gondwana::Core

#endif // GONDWANA_CORE_SHAREDMEMORYMAP_H

