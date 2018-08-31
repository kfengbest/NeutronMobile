#include "Pch/BasePch.h"
#define __COMPILING_NS_ASSERT_CPP__
#include "Assert.h"
#undef __COMPILING_NS_ASSERT_CPP__

//
//#include "../OS/Platform.h"
//#include "../UnitTest/UnitTestMgr.h"
// 
//#include <set>
//#include <tbb/atomic.h>
//
//#if defined(NEUTRON_OS_WIN)
//# include <Windows.h>
//# include <signal.h>
//#elif defined(NEUTRON_OS_MAC)
//# include <CoreFoundation/CoreFoundation.h>
//#endif
//
//using namespace Ns;
//
//struct VerificationKey 
//{
//	Ns::ptr_int obj;
//	Ns::HString fn;
//};
//bool operator<(const VerificationKey& lhs, const VerificationKey& rhs)
//{
//	return lhs.obj < rhs.obj && lhs.fn < rhs.fn;
//}
//bool operator==(const VerificationKey& lhs, const VerificationKey& rhs)
//{
//	return lhs.obj == rhs.obj && lhs.fn == rhs.fn;
//}
//
//typedef std::set<VerificationKey> Verifications;
//
//static tbb::atomic<int> g_Assertions;
//
//// these two variables should only be set by UI main thread when starting the test,
//// it is not necessary to set it thread safe
//static bool g_runningAutomatedTests = false;
//static bool g_showUIDialog = true;
//
//static tbb::spin_mutex	s_mutex;
//static int g_totalAlerts = 0;
//
//static Verifications* verifications() 
//{
//	static Verifications s_theOneAndOnly;
//	return &s_theOneAndOnly;
//}
//
//void Ns::Assert::preAssert()
//{
//	g_Assertions++;
//}
//
//void Ns::Assert::postAssert()
//{
//	g_Assertions--;
//}
//
//bool Ns::Assert::isAsserting()
//{
//	return (g_Assertions > 0);
//}
//
//void Ns::Assert::virtualVerified(Ns::ptr_int obj, const char* fnName)
//{
//	VerificationKey key;
//	key.obj = obj;
//	key.fn = fnName;
//
//	Verifications* pVerifications = verifications();
//	pVerifications->insert(key);
//}
//bool Ns::Assert::isVirtualVerified(Ns::ptr_int obj, const char* fnName)
//{
//	VerificationKey key;
//	key.obj = obj;
//	key.fn = fnName;
//
//	Verifications* pVerifications = verifications();
//	bool bVerified = (pVerifications->end() != pVerifications->find(key));
//	if (bVerified)
//	{
//		pVerifications->erase(key);
//	}
//	return bVerified;
//}
//
//namespace {
//	int displayAssert(const std::string &header, const std::string &body)
//	{
//#if defined(NEUTRON_OS_WIN)
//		std::string text(header + "\n\n" + body + "\n\n(Press Retry to debug the application.)");
//		switch (::MessageBoxA(0, text.c_str(), "Neutron Assert", MB_ABORTRETRYIGNORE|MB_ICONERROR|MB_SETFOREGROUND|MB_TASKMODAL|MB_DEFBUTTON3)) {
//		case IDIGNORE:
//			return 0;
//		case IDRETRY:
//			return 1;
//		case IDABORT:
//		default:
//			return -1;
//		}
//#elif defined(NEUTRON_OS_MAC)
//		CFStringRef cfheader = CFStringCreateWithCString(kCFAllocatorDefault, header.c_str(), kCFStringEncodingUTF8);
//		CFStringRef cfbody = CFStringCreateWithCString(kCFAllocatorDefault, body.c_str(), kCFStringEncodingUTF8);
//
//		CFOptionFlags option_flags;
//		CFUserNotificationDisplayAlert(0, kCFUserNotificationStopAlertLevel, 0, 0, 0,
//									   cfheader,
//									   cfbody,
//									   CFSTR("Continue application"),
//									   CFSTR("Break into debugger"),
//									   CFSTR("Stop application"),
//									   &option_flags);
//		CFRelease(cfheader);
//		CFRelease(cfbody);
//
//		switch (option_flags) {
//		case kCFUserNotificationDefaultResponse:
//			return 0;
//			
//		case kCFUserNotificationAlternateResponse:
//			return 1;
//			
//		case kCFUserNotificationOtherResponse:
//		case kCFUserNotificationCancelResponse:
//		default:
//			return -1;
//		}
//#endif
//	}
//}
//
//#if defined(NEUTRON_OS_WIN)
//# define OPENQUOTE "\""
//# define CLOSEQUOTE "\""
//#elif defined(NEUTRON_OS_MAC)
//# define OPENQUOTE "\xE2\x80\x9C"
//# define CLOSEQUOTE "\xE2\x80\x9D"
//#endif
//
//void Ns::Assert::setAutomatedTestStartFlag(bool bShowUIDialog)
//{
//	g_runningAutomatedTests = true;
//	g_showUIDialog = bShowUIDialog;
//
//	tbb::spin_mutex::scoped_lock lock(s_mutex);
//	g_totalAlerts = 0;
//}
//
//void Ns::Assert::setAutomatedTestEndFlag()
//{
//	g_runningAutomatedTests = false;
//
//	// reset this stat flag to general showing dialog status
//	g_showUIDialog = true;
//}
//
//IString Ns::Assert::getLastErrReport()
//{
//	if (g_totalAlerts > 0)
//	{
//		IString strReport = (boost::wformat(_DNGI("Total failed NEUTRON_ASSERTs: %1%")) %g_totalAlerts).str();
//		strReport += _DNGI("\n");
//		return strReport;
//	}
//	else
//		return _DNGI("");
//}
//
//int Ns::Assert::getAssertAction(const char *b_as_string, const char *function, const char *pretty_function, const char *file, int line)
//{
//	int nRet = 0;
//	if (g_showUIDialog)
//	{
//		std::string header("Asserting " OPENQUOTE);
//		header += b_as_string;
//		header += CLOSEQUOTE " in ";
//		header += function;
//		header += " failed.";
//
//		std::string body;
//		body += "Function: ";
//		body += pretty_function;
//
//		{
//			body += "\n\nApplication: ";
//#if defined(NEUTRON_OS_WIN)
//			char buffer[4096];
//			::GetModuleFileNameA(0, buffer, _countof(buffer));
//			body += buffer;
//#elif defined(NEUTRON_OS_MAC)
//			CFURLRef exe_url = CFBundleCopyExecutableURL(CFBundleGetMainBundle());
//			char buffer[4096];
//			if (CFStringGetCString(CFURLGetString(exe_url), buffer, sizeof(buffer)/sizeof(buffer[0]), kCFStringEncodingUTF8))
//				body += buffer;
//			else
//				body += "(unknown)";
//			CFRelease(exe_url);
//#endif
//		}
//
//		body += "\nFile: ";
//		body += file;
//
//		{
//			body += "\nLine: ";
//			char buffer[64];
//			sprintf(buffer, "%d", line);
//			body += buffer;
//		}
//
//		nRet = displayAssert(header, body);
//	}
//
//	if (g_runningAutomatedTests)
//	{
//		// add assert error statistic process
//		HString strFailedInfo = (boost::format("NEUTRON_ASSERT failed with \"%1%\" in %2%. Function: %3%, File: %4%, Line: %5%") 
//			%b_as_string %function %pretty_function %file %line).str();
//				
//		tbb::spin_mutex::scoped_lock lock(s_mutex);
//		UnitTestMgr::get()->suppressedDialog(strFailedInfo, false);
//		g_totalAlerts++;
//	}
//
//	return nRet;
//}
