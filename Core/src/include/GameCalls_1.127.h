#ifndef GONDWANA_CORE_GAMECALLS_1_127_H
#define GONDWANA_CORE_GAMECALLS_1_127_H

#include <cstddef>

namespace Gondwana::Core::GameCalls_1_127
{

inline std::ptrdiff_t CallEIPModifier = 4;

//// GetGameTicks

// Legitimate addresses of game's functions to call them from imitations.
inline long long int (*GetGameTicks)() = (long long int (*)())0x00731222;

// Call addresses for hijacking function calls. Naming convention :
// Opcode type (Call, Jmp, Mov), legitimate function name, location.
inline void * Call_GetGameTicks_GameStart              = (void *)0x004434E6;

}

#endif // GONDWANA_CORE_GAMECALLS_1_127_H
