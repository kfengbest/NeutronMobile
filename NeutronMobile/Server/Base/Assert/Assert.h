#pragma once
#include <assert.h>
 
#include "../Globals.h"
#ifdef NS_BASE_EXPORTS
# ifdef __COMPILING_NS_ASSERT_CPP__
#  define NS_BASE_API NS_EXPORT
# else
#  define NS_BASE_API
# endif
#else
# define NS_BASE_API NS_IMPORT
#endif

// Basic Assert...
#ifdef _DEBUG
#define NEUTRON_ASSERT(X)	do { } while (0)
#endif

//
//#include <signal.h>
//
//// Functions for verifying that derived classes forward important
//// calls for things like Create / Destroy to base classes...
//namespace Ns { namespace Assert {
//
//	NS_BASE_API void preAssert();
//	NS_BASE_API void postAssert();
//	NS_BASE_API bool isAsserting();
//
//	NS_BASE_API void virtualVerified( Ns::ptr_int pObj, const char* fnName );
//	NS_BASE_API bool isVirtualVerified( Ns::ptr_int pObj, const char* fnName );
//
//	NS_BASE_API int getAssertAction(const char *b_as_string, const char *function, const char *pretty_function, const char *file, int line);
//
//	// set unit test starting flag, should be only called by UI main thread
//	NS_BASE_API void setAutomatedTestStartFlag(bool bShowUIDialog);
//	// set unit test end flag, should be only called by UI main thread
//	NS_BASE_API void setAutomatedTestEndFlag();
//	// get latest running error report if there any, should be only called by UI main thread
//	NS_BASE_API IString	getLastErrReport();
//}}
//
//// __NEUTRON_ASSERT isn't intended to be used directly, use NEUTRON_ASSERT instead.
////
//#if defined(NEUTRON_OS_WIN)
//#define __NEUTRON_ASSERT(X) \
//	do { \
//		int ret = ::Ns::Assert::getAssertAction(#X, __FUNCTION__, __FUNCSIG__, __FILE__, __LINE__); \
//		if (ret > 0) \
//			::__debugbreak(); \
//		else if (ret < 0) { \
//			::raise(SIGABRT); \
//			::_exit(3); \
//		} \
//	} while (0)
//#elif defined(NEUTRON_OS_MAC)
//#define __NEUTRON_ASSERT(X) \
//	do { \
//		int ret = ::Ns::Assert::getAssertAction(#X, __FUNCTION__, __PRETTY_FUNCTION__, __FILE__, __LINE__); \
//		if (ret > 0) \
//			::raise(SIGTRAP); \
//		else if (ret < 0) { \
//			::raise(SIGABRT); \
//		} \
//	} while (0)
//#endif
//
//// Basic Assert...
//#ifdef _DEBUG
//#define NEUTRON_ASSERT(X)	do {								\
//								if (!(X)) {						\
//									Ns::Assert::preAssert();	\
//									__NEUTRON_ASSERT(X);		\
//									Ns::Assert::postAssert();	\
//								}								\
//							}									\
//							while (0)
//#else
//#define NEUTRON_ASSERT(X)	do { } while (0)
//#endif
//
//#ifdef _DEBUG
//#define NEUTRON_VIRTUAL_VERIFY(fnName)		this->fnName(); NEUTRON_ASSERT(Ns::Assert::isVirtualVerified((Ns::ptr_int)((void*)this), #fnName))
//#define NEUTRON_VIRTUAL_VERIFIED(fnName)	Ns::Assert::virtualVerified((Ns::ptr_int)((void*)this), #fnName)
//#else
//#define NEUTRON_VIRTUAL_VERIFY(fnName)		this->fnName()
//#define NEUTRON_VIRTUAL_VERIFIED(fnName)  
//#endif
//
#undef NS_BASE_API
