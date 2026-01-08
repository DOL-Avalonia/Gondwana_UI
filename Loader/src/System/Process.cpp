#include "Process.h"
#include "Log.h"

#include <windows.h>

namespace Gondwana::Loader::System
{

Process::Process(
	std::wstring_view executable, 
	std::wstring_view commandLine, 
	std::wstring_view workingDirectory,
	bool suspended,
	bool attached) :
	m_Executable {executable},
	m_CommandLine {commandLine},
	m_WorkingDirectory {workingDirectory},
	m_Suspended {suspended},
	m_Attached {attached}
{
	ResetProcessInformation();
}

Process::~Process()
{
	Stop();
}

bool Process::Create()
{
	if (m_ProcessInformation.hProcess != INVALID_HANDLE_VALUE)
		return false;

	DWORD creationFlags =
		NORMAL_PRIORITY_CLASS |
		(m_Suspended ? CREATE_SUSPENDED : 0);

	STARTUPINFO startupInfo
	{
		.cb = sizeof(STARTUPINFO),
		.lpReserved = nullptr,
		.lpDesktop = nullptr,
		.lpTitle = nullptr,
		.dwX = 0,
		.dwY = 0,
		.dwXSize = 0,
		.dwYSize = 0,
		.dwXCountChars = 0,
		.dwYCountChars = 0,
		.dwFillAttribute = 0,
		.dwFlags = 0,
		.wShowWindow = 0,
		.cbReserved2 = 0,
		.lpReserved2 = nullptr,
		.hStdInput = nullptr,
		.hStdOutput = nullptr,
		.hStdError = nullptr,
	};

	BOOL result = CreateProcessW(
		m_Executable.data(),
		const_cast<wchar_t *>(m_CommandLine.data()),
		NULL, // process attributes
		NULL, // thread attributes
		FALSE, // inherit handles
		creationFlags,
		NULL, // environment
		m_WorkingDirectory.data(),
		&startupInfo,
		&m_ProcessInformation
	);
	return result != FALSE;
}

bool Process::Start()
{
	if (m_ProcessInformation.hProcess == INVALID_HANDLE_VALUE)
		return false;

	if (int result = ResumeThread(m_ProcessInformation.hThread); result == -1)
	{
		DWORD error = GetLastError();
		return false;
	}
	return true;
}

void Process::Stop()
{
	if (m_ProcessInformation.hProcess == INVALID_HANDLE_VALUE)
		return;
	TerminateProcess(m_ProcessInformation.hThread, 0);
	ResetProcessInformation();
}

bool Process::Join(unsigned int timeoutMs)
{
	if (m_ProcessInformation.hProcess == INVALID_HANDLE_VALUE)
		return false;

	const DWORD waitResult = WaitForSingleObject(m_ProcessInformation.hProcess, timeoutMs);

	bool result = false;
	switch (waitResult)
	{
		case WAIT_OBJECT_0 : result = true ; break;
		case WAIT_ABANDONED: result = false; break;
		case WAIT_TIMEOUT  : result = false; break;
		case WAIT_FAILED   : result = false; break;
	}

	return result;
}

bool Process::ReadBytes(void* address, void* bytes, size_t size)
{
	if (m_ProcessInformation.hProcess == INVALID_HANDLE_VALUE)
		return false;

	DWORD wrote_bytes = 0;

	// TODO(dstaniak) : Make a page access modifier class for this :
	DWORD oldProtect;
	BOOL protectFix = VirtualProtectEx(
		m_ProcessInformation.hProcess,
		address,
		size,
		PAGE_READWRITE,
		&oldProtect
	);

	if (protectFix == FALSE)
		return false;

	bool result = ReadBytesFromRPage(address, bytes, size);

	DWORD pageRWflags;
	BOOL restoreProtection = VirtualProtectEx(
		m_ProcessInformation.hProcess,
		address,
		size,
		oldProtect,
		&pageRWflags
	);

	if (restoreProtection == FALSE)
		Logger::log.Write("[WARN] Cannot restore protection for {:8X} ({} bytes).", (unsigned int)address, size);

	return result;
}

bool Process::WriteBytes(void* address, void* bytes, size_t size)
{
	if (m_ProcessInformation.hProcess == INVALID_HANDLE_VALUE)
		return false;

	DWORD wrote_bytes = 0;

	DWORD oldProtect;
	BOOL protectFix = VirtualProtectEx(
		m_ProcessInformation.hProcess,
		address,
		size,
		PAGE_READWRITE,
		&oldProtect
	);

	if (protectFix == FALSE)
		return false;

	bool result = WriteBytesToRWPage(address, bytes, size);

	DWORD pageRWflags;
	BOOL restoreProtection = VirtualProtectEx(
		m_ProcessInformation.hProcess,
		address,
		size,
		oldProtect,
		&pageRWflags
	);

	if (restoreProtection == FALSE)
		Logger::log.Write("[WARN] Cannot restore protection for {:8X} ({} bytes).", (unsigned int)address, size);

	return result;
}

bool Process::ReadBytesFromRPage(void * address, void * bytes, size_t size)
{
	if (m_ProcessInformation.hProcess == INVALID_HANDLE_VALUE)
		return false;

	DWORD readBytes;
	BOOL readResult = ReadProcessMemory(
		m_ProcessInformation.hProcess,
		address,
		bytes,
		size,
		&readBytes);

	return (readResult != FALSE) && (readBytes == size);
}

bool Process::WriteBytesToRWPage(void * address, void const * bytes, size_t size)
{
	if (m_ProcessInformation.hProcess == INVALID_HANDLE_VALUE)
		return false;

	DWORD wroteBytes;
	BOOL writeResult = WriteProcessMemory(
		m_ProcessInformation.hProcess,
		address,
		bytes,
		size,
		&wroteBytes);

	return (writeResult != FALSE) && (wroteBytes == size);
}

HANDLE Process::InjectDll(std::wstring_view dllPath)
{
	if (m_ProcessInformation.hProcess == INVALID_HANDLE_VALUE || dllPath.size() == 0)
		return INVALID_HANDLE_VALUE;

	const auto CharSize = sizeof(wchar_t);
	const std::uintptr_t BytesSize = CharSize * dllPath.size();

	void * inProcessMemory = VirtualAllocEx(
		m_ProcessInformation.hProcess, 
		NULL, 
		BytesSize + CharSize,
		MEM_COMMIT, 
		PAGE_READWRITE
	);

	if (inProcessMemory == nullptr)
		return INVALID_HANDLE_VALUE;

	if (!WriteBytesToRWPage(inProcessMemory, dllPath.data(), BytesSize))
		return INVALID_HANDLE_VALUE;

	const wchar_t NullTerminator = 0;
	void * trailingZeroAddress = reinterpret_cast<void *>(reinterpret_cast<std::uintptr_t>(inProcessMemory) + BytesSize);
	if (!WriteBytesToRWPage(trailingZeroAddress, &NullTerminator, CharSize))
		return INVALID_HANDLE_VALUE;

	HMODULE kernel32 = GetModuleHandleA("kernel32.dll");
	FARPROC loadLibraryA = GetProcAddress(static_cast<HINSTANCE>(kernel32), "LoadLibraryA");

	// TODO(dstaniak) : Continue here!

	/*HMODULE injectedDll = static_cast<HMODULE>(
		RemoteCodeExecute()
	);*/

	return INVALID_HANDLE_VALUE;
}

void Process::ResetProcessInformation()
{
	m_ProcessInformation.dwProcessId = 0;
	m_ProcessInformation.dwThreadId = 0;
	m_ProcessInformation.hProcess = INVALID_HANDLE_VALUE;
	m_ProcessInformation.hThread = INVALID_HANDLE_VALUE;
}

}

