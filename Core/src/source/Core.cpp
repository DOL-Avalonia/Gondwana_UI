// Core.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "Core.h"

#include <winsock.h>

// This is an example of an exported variable
CORE_API int nCore=0;

CORE_API unsigned short WriteReceviedPacket(unsigned short ntohsArgument)
{
    return ntohs(ntohsArgument);
}

// This is the constructor of a class that has been exported.
CCore::CCore()
{
    return;
}

