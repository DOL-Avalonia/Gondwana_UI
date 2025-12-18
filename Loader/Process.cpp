#include "Process.h"

#include <windows.h>

namespace Gondwana::Loader 
{

Process::Process(
	std::wstring_view executable, 
	std::wstring_view commandLine, 
	std::wstring_view workingDirectory,
	bool attached,
	bool suspended) :
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

void Process::ResetProcessInformation()
{
	m_ProcessInformation.dwProcessId = 0;
	m_ProcessInformation.dwThreadId = 0;
	m_ProcessInformation.hProcess = INVALID_HANDLE_VALUE;
	m_ProcessInformation.hThread = INVALID_HANDLE_VALUE;
}

}


