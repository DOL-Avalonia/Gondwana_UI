#ifndef GONDWANA_LOADER_PATCHNEWCLASS_H
#define GONDWANA_LOADER_PATCHNEWCLASS_H

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
};

} // Gondwana::Loader

#endif // GONDWANA_LOADER_PATCHNEWCLASS_H

