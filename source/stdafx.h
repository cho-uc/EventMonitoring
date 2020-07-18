// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#pragma warning(disable : 4995)
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>
#include <Strsafe.h>
#include <queue>
#include <vector>
#include <atomic>
#include <thread>
#include <tlhelp32.h> //for process checking

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

//ATL/WTL
#define _ATL_NO_MSIMG // Omits static linking of MSImg32.dll which is not fully supported in Windows NT
#include <atlbase.h>
#include <atlstr.h>
#include <atlapp.h>
#include <atlwin.h>
#include <atldlgs.h>
#include <atlscrl.h>
#include <atlctrls.h>
#include <atlctrlw.h>
#include <atlddx.h>

#ifdef _UNICODE
typedef wchar_t TCHAR;
#else
typedef char TCHAR;
#endif // _UNICODE

#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif // _UNICODEv

static const int SLEEP_TIME = 100; //ms