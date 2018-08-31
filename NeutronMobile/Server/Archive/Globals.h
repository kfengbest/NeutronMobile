#pragma once

// Operating System Stuff...
#if defined(_WINDOWS) || defined(_WIN32) || defined(_WIN64)
# define NEUTRON_OS_WIN  
#elif defined(__APPLE__) && defined(__MACH__)
# define NEUTRON_OS_MAC  
#else
# error "Operating System Not Supported By Neutron.  Only Windows and Mac OS X Supported"
#endif

// Deprecating Stuff...
#if defined(__GNUC__)
# define DEPRECATED_PREFIX
# define DEPRECATED_SUFFIX __attribute__ ((deprecated))
#elif defined(_MSC_VER)
# define DEPRECATED_PREFIX __declspec(deprecated)
# define DEPRECATED_SUFFIX
#else
# pragma message("warning: please implement the DEPRECATED macros for this compiler")
# define DEPRECATED_PREFIX
# define DEPRECATED_SUFFIX
#endif

// Always inline
#if defined(__GNUC__)
# define ALWAYS_INLINE_PREFIX
# define ALWAYS_INLINE_SUFFIX __attribute__ ((always_inline))
#elif defined(_MSC_VER)
# define ALWAYS_INLINE_PREFIX __forceinline
# define ALWAYS_INLINE_SUFFIX
#else
# pragma message("warning: please implement the ALWAYS_INLINE macros for this compiler")
# define ALWAYS_INLINE_PREFIX
# define ALWAYS_INLINE_SUFFIX
#endif

// CPU Stuff...
#if defined(_WIN32) && !defined(_WIN64)
# define NEUTRON_32BIT
#else
# define NEUTRON_64BIT
#endif

// Warnings...
#if defined(NEUTRON_OS_WIN)
#pragma warning(disable:4786)	// identifier was truncated to '255' characters in the debug information
#pragma warning(disable:4800)	//  C4800: 'int' : forcing value to bool 'true' or 'false' (performance warning)
#pragma warning(disable:4652)	// compiler option 'Generate Browser Info' inconsistent with precompiled header; current command-line option will override that defined in the precompiled header
#pragma warning(disable:4996)	// Ease the port to DevStudio 2005. Ignore the deprecated libC warnings.
#pragma warning(disable:4251)	// class 'std::vector<_Ty>' needs to have dll-interface to be used by clients of class XX
#pragma warning(disable:4275)	// non dll-interface class '<Base Class>' used as base for dll-interface class '<Subclass>'
#elif defined(NEUTRON_OS_MAC)
#endif

// Includes...
#include <vector>

// Types...
namespace Ns
{
    typedef char						int8;
    typedef short						int16;
    typedef int							int32;
#if defined(NEUTRON_OS_WIN)
    typedef __int64						int64;
#elif defined(NEUTRON_OS_MAC)
	typedef long long					int64;
#endif
    typedef unsigned char				uint8;
    typedef unsigned short				uint16;
    typedef unsigned int				uint32;
#if defined(NEUTRON_OS_WIN)
    typedef unsigned __int64			uint64;
#elif defined(NEUTRON_OS_MAC)
	typedef unsigned long long			uint64;
#endif

    // Integer the size of a pointer...
    typedef uintptr_t					ptr_int;

	// Strings...
    typedef wchar_t						IChar;
    typedef char						HChar;

	// Bytes.
	typedef unsigned char				Byte;
	
	typedef uint64						EntityId;	

};

// Miscellaneous..
#if defined(NEUTRON_OS_WIN)
# define _NLI L"\r\n"
# define _NLH "\r\n"
# define _NSTDCALL __stdcall
#elif defined(NEUTRON_OS_MAC)
# define _NLI L"\n"
# define _NLH "\n"
# define _NSTDCALL
  #if !defined(_MAX_PATH)
   # define _MAX_PATH 1024
  #endif
#endif

// By convention, these macros identify strings that need or need not be
// translated. The static_casts are to prevent using them in the _LCLZ
// macro, which can prevent the string from being picked up by xgettext.
// Unfortunately, this means that usages like _DNGI('A') are no longer
// acceptable; this should be okay since character literals can't really
// be translated anyway.
typedef char _ERROR_macro_expects_string_literal;
typedef wchar_t _ERROR_macro_expects_string_literal_w;
#define _DNGH(X)	(static_cast<const _ERROR_macro_expects_string_literal * const>(X))			// For internal strings that are not user-visible
#define _DNGI(X)	(static_cast<const _ERROR_macro_expects_string_literal_w * const>(L ## X))	// For strings for debugging tools and the like
#define _DGI(X)		(static_cast<const _ERROR_macro_expects_string_literal_w * const>(L ## X))	// To identify something to rework later

// Exports...
#if defined(NEUTRON_OS_WIN)
# define NS_EXPORT __declspec(dllexport)
# define NS_IMPORT __declspec(dllimport)
# define NS_EXPORT_METHOD __declspec(dllexport)
#elif defined(NEUTRON_OS_MAC)
# define NS_EXPORT __attribute__ ((visibility("default")))
# define NS_IMPORT
# define NS_EXPORT_METHOD extern "C" __attribute__ ((visibility("default")))
#endif

