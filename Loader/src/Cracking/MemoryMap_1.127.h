#ifndef GONDWANA_LOADER_MEMORYMAP_1_127_H
#define GONDWANA_LOADER_MEMORYMAP_1_127_H

#include <array>
#include <cstdint>

namespace Gondwana::Loader::MemoryMap_1_127 
{

// Variables to alter game behaviour.
inline void * InitialEncryptionLevel                   = (void *)0x00411057;
inline void * GameEncryptionLevel                      = (void *)0x00411067;
inline void * Logger                                   = (void *)0x00428209;

namespace Classes {

/*
 * @brief References to class names array.
 * 
 * @detail 
 * These are all the offsets in the process' memory space, 
 * where the classes array is referenced. These addresses will be
 * replaced with the address of a new array.
 * 
 */
inline std::array<void *, 5> ClassNamesRefs = 
{
	(void*)0x0450995,
	(void*)0x04E0037,
	(void*)0x04E020B,
	(void*)0x04E03A4,
	(void*)0x04E04E9
};

}

} // Gondwana::Loader::MemoryMap_1_127

#endif // GONDWANA_LOADER_MEMORYMAP_1_127_H
