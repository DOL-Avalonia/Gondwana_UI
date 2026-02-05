#pragma once

class SharedMemory
{


	/*

	HANDLE hMapFile = CreateFileMappingA(
					INVALID_HANDLE_VALUE,
					NULL,
					PAGE_READWRITE,
					0,
					sizeof(SharedMemoryMap),
					"Global\\DarsonIAThookMemory");

	if (hMapFile == NULL) // shared memory creation error
	{
		printf("Cannot create shared memory object (%d).\n", GetLastError());
		return 0;
	}

	// map pointer to a view of shared memory
	SharedMemoryMap* mapView = (SharedMemoryMap*)MapViewOfFile(
		hMapFile,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		sizeof(SharedMemoryMap));

	if (mapView == NULL) // error mapping shared memory
	{
		printf("Cannot map view of file.\n");
		return 0;
	}
*/
};

