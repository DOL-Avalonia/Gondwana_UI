#ifndef GONDWANA_LOADER_PROCESS_H
#define GONDWANA_LOADER_PROCESS_H

#include <windows.h>
#include <string>

namespace Gondwana::Util::System
{

class Process
{
public:
	struct Thread
	{
		HANDLE handle {NULL};
		DWORD  id     {0};
		DWORD  result {0};
	};

	Process(
		std::wstring_view executable,
		std::wstring_view commandLine,
		std::wstring_view workingDirectory,
		bool suspended,
		bool attached
	);

	explicit Process(const PROCESS_INFORMATION processInformation);
	Process();

	class TmpMemory
	{
	public:
		TmpMemory(TmpMemory && other);
		~TmpMemory();
		void * Address();
		operator void *();
		operator uintptr_t ();

	private:
		friend class Process;

		TmpMemory(Process const & process, size_t size);

		Process const & m_Process;
		void * m_Address;
	};

	~Process();

	bool Create();
	bool Start();
	void Stop();
	bool Join(unsigned int timeoutMs = INFINITE);

	bool ReadBytes(void * address, void * bytes, size_t size);
	bool WriteBytes(void * address, void * bytes, size_t size);
	bool ReadBytesFromRPage(void * address, void * bytes, size_t size);
	bool WriteBytesToRWPage(void * address, void const * bytes, size_t size);

	void * Alloc(size_t size) const;
	void Free(void * address) const;
	TmpMemory AllocTmp(size_t size) const;

	Thread StartThread(LPTHREAD_START_ROUTINE function, void * argument) const;
	void JoinThread(Thread & thread) const;
	std::pair<bool, DWORD> SyncThread(LPTHREAD_START_ROUTINE function, void * argument) const;

	HANDLE InjectDll(std::wstring_view dllPath);

private:
	void ResetProcessInformation();

	const bool m_Owned;
	const std::wstring m_Executable;
	const std::wstring m_CommandLine;
	const std::wstring m_WorkingDirectory;
	const bool m_Suspended;
	const bool m_Attached;
	PROCESS_INFORMATION m_ProcessInformation;
};

}

#endif // GONDWANA_LOADER_PROCESS_H
