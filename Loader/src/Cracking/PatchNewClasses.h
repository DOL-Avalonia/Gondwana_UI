#ifndef GONDWANA_LOADER_PATCHNEWCLASS_H
#define GONDWANA_LOADER_PATCHNEWCLASS_H

#include <string>
#include <vector>

namespace Gondwana::Loader
{

namespace System 
{

class Process;

}

class PatchNewClasses
{
public:
	bool Apply(System::Process & process);
	bool Undo(System::Process & process);

private:
	bool Write(System::Process & process, void * newDataPtr);

	void * m_OldAddress = nullptr;
	void * m_NewClasses = nullptr;

	static const std::vector<std::string> Classes;
	static constexpr size_t ClassStrLen = 30;
};

} // Gondwana::Loader

#endif // GONDWANA_LOADER_PATCHNEWCLASS_H

