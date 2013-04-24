#ifndef CSHIFT_PLATFORM_OS_API_BASE_H
#define CSHIFT_PLATFORM_OS_API_BASE_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include <stdarg.h>  // TODO: MinGW specific
#include <WinDef.h>  // TODO: MinGW specific

// on Windows XP, Windows Server 2003, Windows Vista, Windows 7, Windows Server 2008,
#include <WinBase.h>
// Windows Server 2008 R2
//#include <Windows.h>

#define PLATFORM_OS_API_CONVENTION WINAPI

#endif // CSHIFT_PLATFORM_OS_API_BASE_H

