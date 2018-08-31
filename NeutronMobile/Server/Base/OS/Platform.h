#pragma once

#include "../Globals.h"

#ifdef NS_BASE_EXPORTS
# ifdef __COMPILING_NS_PLATFORMIMPLEMENTATION_CPP__
#  define NS_BASE_API NS_EXPORT
# else
#  define NS_BASE_API
# endif
#else
# define NS_BASE_API NS_IMPORT
#endif

// Common Includes...
//#include <boost/filesystem/path.hpp>

namespace Ns { namespace OS {
//
//	// --------------------------------------------------
//	// Platform Neutral Currencies...
//	// --------------------------------------------------
//	typedef unsigned long	PlatformProcessId;
//#if defined(NEUTRON_OS_WIN)
//	typedef void*			PlatformModuleHandle;
//	typedef void(__stdcall*	PlatformCallbackFunc)();
//    typedef void*			PlatformWindowHandle;
//	typedef unsigned long	PlatformThreadId;
//#elif defined(NEUTRON_OS_MAC)
//	typedef void*			PlatformModuleHandle;	
//	typedef void*			PlatformCallbackFunc;
//    typedef void*			PlatformWindowHandle;
//	typedef __uint64_t		PlatformThreadId;
//#endif
//
//	// --------------------------------------------------
//	// Startup and Shutdown...
//	// --------------------------------------------------
//	NS_BASE_API void platformStartup();
//	NS_BASE_API void platformShutdown();
//	
//	// --------------------------------------------------
//	// Module Utilities...
//	// --------------------------------------------------
//	NS_BASE_API const Ns::IString& platformModuleExtension();
//	NS_BASE_API const Ns::IString& platformExeExtension();
//	NS_BASE_API const Ns::IString& platformFrameworkExtension();
//	NS_BASE_API PlatformModuleHandle platformGetLoadedModule(const Ns::IString& moduleName);
//	NS_BASE_API PlatformModuleHandle platformLoadModule(const Ns::IString& moduleName);
//	NS_BASE_API bool platformIsModuleHandleValid(const PlatformModuleHandle& module);
//	NS_BASE_API void platformUnloadModule(PlatformModuleHandle& module);
//	NS_BASE_API PlatformCallbackFunc platformGetSymbolAddress(const PlatformModuleHandle& module, const Ns::HString& symbolName);
//	NS_BASE_API bool platformGetModuleVersion(const IString& strDllFileName, uint32& major, uint32& minor, uint32& buildNumber);
//	NS_BASE_API IString platformGetModulePathContainingAddress(const void *pv);
//
//	// --------------------------------------------------
//	// Image Utilities...
//	// --------------------------------------------------
//	NS_BASE_API void platformGetImageSize(const IString& file, int& width, int& height);
//
//	// --------------------------------------------------
//	// Thread utilities...
//	// --------------------------------------------------
//	NS_BASE_API void platformSetUIThread();					// The calling thread is the UI thread.
//	NS_BASE_API bool platformIsUIThread();					// Is the calling thread the UI thread.
//	NS_BASE_API PlatformThreadId platformGetUIThread();		// Get UI Thread ID.
//	NS_BASE_API PlatformThreadId platformThreadId();		// The Thread ID of the calling thread.
//
//	NS_BASE_API PlatformProcessId platformProcessId();		// Get currunt process id.
//
//	// --------------------------------------------------
//	// Environment Utilities...
//	// --------------------------------------------------
//	NS_BASE_API boost::filesystem::wpath platformGetAppDirectory(); // Location of .exe or app bundle
//	NS_BASE_API boost::filesystem::wpath platformGetExecutableDirectory(); // Location of .exe or binary
//	NS_BASE_API boost::filesystem::wpath platformGetTemporaryDirectory();
//	NS_BASE_API boost::filesystem::wpath platformGetUserDataDirectory();
//    NS_BASE_API boost::filesystem::wpath platformGetUserDocumentsDirectory();
//    
//	NS_BASE_API Ns::IString platformGetEnvironmentVariable(const Ns::IString& name);
//	
//	// --------------------------------------------------
//	// File System Utilities...
//	// --------------------------------------------------
//	NS_BASE_API bool platformIsReadOnly(const Ns::IString& path);
//
//	NS_BASE_API bool platformMakeReadOnly(const Ns::IString& path);
//
//    NS_BASE_API bool platformRemoveReadOnly(const Ns::IString& path);
//
//	NS_BASE_API bool platformIsWcharUnicode();
//
//	NS_BASE_API void platformTraceMessage(bool bIsUnicode, const char* fileName, int lineNumber,...);
//
//	// How to use: 
//	//   (1) if your method interface is: someMethod(Ns::HString, ...),you must make sure that
//	//       your method should be used in this way: someMethod("%s", "some text") or someMethod("%S", "some text")
//	//   (2) if your method interface is: someMethod(Ns::IString, ...),you must make sure that
//	//       your method should be used in this way: someMethod(_DNGI("%s"), _DNGI("some text")) or someMethod(_DNGI("%S"), _DNGI("some text"))
//	// Reason: There are some differences between Windows and Mac
//	//  |------------------------------------------------------------------------------|
//	//  |         Valid on Windows             |             Valid on Mac              |
//	//  |------------------------------------------------------------------------------|
//	//  |  printf("%s", "test")                |   printf("%s", "test")                |
//	//  |  printf("%S", _DNGI("test"))         |   printf("%S", _DNGI("test"))         |
//	//  |  wprintf(_DNGI("%s"), _DNGI("test")) |   wprintf(_DNGI("%s"), "test"))       |
//	//  |  wprintf(_DNGI("%S"), "test")        |   wprintf(_DNGI("%S"), _DNGI("test")) |
//	//  |------------------------------------------------------------------------------|
//	// At present, in order to unify the Windows and Mac, please notice that:
//	//  (1)The wchar_t version shouldn't accept char type string
//	//  (2)The char version shouldn't accept wchar_t type string
//	// Right: printf("%s", "test") == printf("%S", "test")
//	// Right: wprintf(_DNGI("%s"), _DNGI("test")) == wprintf(_DNGI("%s"), _DNGI("test"))
//	// Wrong: (1)printf("%s", _DNGI("test")) (2)printf("%S", _DNGI("test"))
//	// Wrong: (1)wprintf(_DNGI("%s"), "test") (2)wprintf(_DNGI("%S"), "test")
//	NS_BASE_API Ns::HString platformFormat(Ns::HString strFormat, va_list args);
//	NS_BASE_API Ns::IString platformFormat(Ns::IString strFormat, va_list args);
//
//	// Debugging support....
//	NS_BASE_API void breakPoint();
//
//	enum EMemoryType {
//		eMemTypeNone         = 0x00000000,
//		eMemTypeWorkingSet   = 0x00000001,
//		eMemTypePagefile     = 0x00000002
//	};
//
//	// Get current process memory usage by type flag
//	NS_BASE_API bool getCurProcessMemory(int nType, double& dValue, double& dPeakValue);
//
//	// CER utilities
//	NS_BASE_API void platformInitializeCERComponent();
//	NS_BASE_API void platformTerminateCERComponent();
//    NS_BASE_API void platformShowCERDialog();
//    
//#if defined(NEUTRON_OS_MAC)
//    NS_BASE_API bool isMacSnowLeopard();
//    NS_BASE_API bool isMacLion();
//#endif
    
}}

#undef NS_BASE_API
