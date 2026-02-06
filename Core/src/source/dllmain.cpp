#include "Core.h"
#include "Hooks.h"
#include "Util/Process.h"
#include <windows.h>
#include <memory>

static std::unique_ptr<Gondwana::Util::System::Process> s_Process;

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
    switch (reason)
    {
		case DLL_PROCESS_ATTACH: 
            s_Process.reset(new Gondwana::Util::System::Process());
            Gondwana::Core::s_Core.reset(new Gondwana::Core::Core(s_Process.get()));
            if (!Gondwana::Core::Hooks::InstallHooks(*s_Process))
            {
                MessageBoxA(nullptr, "Hooks not installed!", "Gondwana", MB_OK | MB_ICONERROR);
            }
            break;

		case DLL_THREAD_ATTACH:
            break;

		case DLL_THREAD_DETACH:
            break;

		case DLL_PROCESS_DETACH:
            Gondwana::Core::Hooks::RemoveHooks(*s_Process);
            Gondwana::Core::s_Core.reset();
			break;
    }
    return TRUE;
}

