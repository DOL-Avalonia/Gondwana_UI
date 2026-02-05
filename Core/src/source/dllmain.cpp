#include "Core.h"
#include <windows.h>
#include <memory>

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
    switch (reason)
    {
		case DLL_PROCESS_ATTACH: 
            Gondwana::Core::s_Core.reset(new Gondwana::Core::Core());
            break;

		case DLL_THREAD_ATTACH:
            break;

		case DLL_THREAD_DETACH:
            break;

		case DLL_PROCESS_DETACH:
            Gondwana::Core::s_Core.reset();
			break;
    }
    return TRUE;
}

