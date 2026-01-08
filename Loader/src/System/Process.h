#ifndef GONDWANA_LOADER_PROCESS_H
#define GONDWANA_LOADER_PROCESS_H

#include <windows.h>
#include <string>

namespace Gondwana::Loader::System
{

class Process
{
public:
	Process(
		std::wstring_view executable,
		std::wstring_view commandLine,
		std::wstring_view workingDirectory,
		bool suspended,
		bool attached
	);

	~Process();

	bool Create();
	bool Start();
	void Stop();
	bool Join(unsigned int timeoutMs = INFINITE);
	bool ReadBytes(void * address, void * bytes, size_t size);
	bool WriteBytes(void * address, void * bytes, size_t size);
	bool ReadBytesFromRPage(void * address, void * bytes, size_t size);
	bool WriteBytesToRWPage(void * address, void const * bytes, size_t size);
	HANDLE InjectDll(std::wstring_view dllPath);

private:
	void ResetProcessInformation();

	const std::wstring m_Executable;
	const std::wstring m_CommandLine;
	const std::wstring m_WorkingDirectory;
	const bool m_Suspended;
	const bool m_Attached;
	PROCESS_INFORMATION m_ProcessInformation;
};

}

#endif // GONDWANA_LOADER_PROCESS_H
