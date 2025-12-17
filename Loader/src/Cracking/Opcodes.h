#ifndef GONDWANA_LOADER_OPCODES_H
#define GONDWANA_LOADER_OPCODES_H

#include <cstdint>
#include <vector>

namespace Gondwana::Loader {

using Opcodes = std::vector<uint8_t>;

// Single processor instruction
struct Instruction 
{
	const char *  mnemo;
	Opcodes       opcodes;
};

// Opcodes that can contain address to system procedure that
extern const std::vector<Instruction> Instructions;

}

#endif
