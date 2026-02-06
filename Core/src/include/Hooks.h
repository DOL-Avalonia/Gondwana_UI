#ifndef GONDWANA_CORE_HOOKS_H
#define GONDWANA_CORE_HOOKS_H

#include <vector>

namespace Gondwana::Util::System { class Process; }

namespace Gondwana::Core::Hooks
{

class Hook
{
public:
	enum class Opcode
	{
		CALL
	};

	Hook(void * hookFunction, void * hookingAddress, Opcode opcode);
	bool Apply(Util::System::Process & process);
	bool Undo(Util::System::Process & process);

private:
	void * const m_HookingAddress;
	Opcode const m_Opcode;

	void * m_HookFunctionRelativeAddress;
	void * m_PreviousAddress = nullptr;
};

extern std::vector<Hook> Hooks;

bool InstallHooks(Util::System::Process & process);
bool RemoveHooks(Util::System::Process & process);

/* DECLARE HOOKS BELOW.
 
   These are imitations of functions called by the game.
   Their addresses will be written over legitimate calls.
   Usually these functions need to call the ones they are
   imitating and return their result back to the hijacked call.

   The function declaration is followed by a comment with
   a legitimate function name which it imitates.
 */

long long int GameStart();                                         // GetGameTicks
unsigned short WriteReceviedPacket(unsigned short i);              // ntohs
int CraftingLoaded(int a);                                         // LoadCrafting

}

#endif // GONDWANA_CORE_HOOKS_H
