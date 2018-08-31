#include "Pch/BasePch.h"
#define __COMPILING_NS_PLATFORMIMPLEMENTATION_CPP__
#import "../Platform.h"
#undef __COMPILING_NS_PLATFORMIMPLEMENTATION_CPP__

#include <stdlib.h>
#include <mach-o/dyld.h>
#include <dlfcn.h>
#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include "../../Assert/Assert.h"
#include "../../SoftwareVersion/SoftwareVersion.h"
#include "../../Status/Exception.h"
#include <Server/Base/XML/XMLDocument.h>
#include <Server/Base/UnitTest/UnitTestMgr.h>

#include <mach/mach_init.h>
#include <mach/task.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
 
namespace {
    
    bool macSys(SInt32& major, SInt32& minor)
    {
        const bool ok = 
        (   noErr == Gestalt(gestaltSystemVersionMajor, &major)
         && noErr == Gestalt(gestaltSystemVersionMinor, &minor));
        return ok;
    }
    
}

// --------------------------------------------------
// Startup and Shutdown...
// --------------------------------------------------
static NSAutoreleasePool * gPool = nil;
void Ns::OS::platformStartup()
{
	XMLDocument::Initialize();
	if (nil == gPool) {
		gPool = [[NSAutoreleasePool alloc] init];
	}
}
void Ns::OS::platformShutdown()
{
	if (nil == gPool) {
		[gPool release];
	}

	// clear test sub-folder and data if needed
	UnitTestMgr::get()->removeSubTestFolder();
	XMLDocument::Terminate();
}

// --------------------------------------------------
// Module Utilities...
// --------------------------------------------------
const static Ns::IString sModuleExtension = _DNGI(".dylib");
const Ns::IString& Ns::OS::platformModuleExtension()
{
	return sModuleExtension;
}

const static Ns::IString sExeExtension = _DNGI("");
const Ns::IString& Ns::OS::platformExeExtension()
{
	return sExeExtension;
}

const static Ns::IString sFrameworkExtension = _DNGI(".framework");
const Ns::IString& Ns::OS::platformFrameworkExtension()
{
	return sFrameworkExtension;
}

Ns::OS::PlatformModuleHandle Ns::OS::platformGetLoadedModule(const Ns::IString& moduleName)
{
	Ns::OS::PlatformModuleHandle hModule = NULL;
	Ns::HString path = ToHString(moduleName);
	hModule = ::dlopen(path.c_str(), RTLD_NOLOAD);
	return hModule;
}

Ns::OS::PlatformModuleHandle Ns::OS::platformLoadModule(const Ns::IString& moduleName)
{
	Ns::OS::PlatformModuleHandle hModule = NULL;
	Ns::HString path = ToHString(moduleName);
	hModule = ::dlopen(path.c_str(), RTLD_LAZY);
	return hModule;
}

bool Ns::OS::platformIsModuleHandleValid(const PlatformModuleHandle& module)
{
	return (NULL != module);
}

void Ns::OS::platformUnloadModule(PlatformModuleHandle& module)
{
	if (NULL != module)
	{
		::dlclose( module );
		module = NULL;
	}
}

Ns::OS::PlatformCallbackFunc Ns::OS::platformGetSymbolAddress(const Ns::OS::PlatformModuleHandle& module, const Ns::HString& symbolName)
{
	void* hModule = ::dlsym(module, symbolName.c_str());
	return hModule;
}

Ns::HString systemGetOutput(const Ns::HString& cmd)
{
	// execute system command and get the output.
    FILE* commandOutput;
    char output[128];
    int amountRead = 1;
    
    Ns::HString fullOutput;
    
    try
    {
        commandOutput = popen(cmd.c_str(), "r");
        if (NULL == commandOutput)
		{
			Ns::IString excpMessage(_DNGI("An error occured while executing command "));
			excpMessage += Ns::ToIString(cmd);
			throw Ns::Exception(excpMessage);
		}
        
        while(amountRead > 0)
        {
            amountRead = fread(output, 1, 127, commandOutput);
            if (amountRead <= 0) break;
            else
            {
                output[amountRead] = '\0';
                fullOutput += output;
            }
        }
    }
    catch(Ns::Exception& e)
    {
        std::cerr << e.message().c_str() << std::endl;
        pclose(commandOutput);
        return "";
    }
    
    int returnValue = pclose(commandOutput);
    if (returnValue != 0) return "";
    
    return fullOutput;
}

bool Ns::OS::platformGetModuleVersion(const Ns::IString& strModuleName, uint32& major, uint32& minor, uint32& buildNumber)
{
	// TODO, currently explicitly calling /usr/bin/otool.
	// we'll build our own version of otool and integrate it into our build in the future.
	// otool - object file displaying tool, for more details,
	// please refer to http://developer.apple.com/mac/library/documentation/Darwin/Reference/ManPages/man1/otool.1.html
	Ns::HString cmd = ToHString(_DNGI("/usr/bin/otool -L ") + strModuleName);
	Ns::HString output = systemGetOutput(cmd);
	NEUTRON_ASSERT(!output.empty());
	if(output.empty()) return false;
	
	int location = output.find("current version ");
	NEUTRON_ASSERT(location >= 0);
	int end = output.find(")");
	NEUTRON_ASSERT(end >= 0);
	int size = end - location - strlen("current version ");
	NEUTRON_ASSERT(size >= 0);
	
	Ns::HString currVer = output.substr(location+strlen("current version "), size);
	return SoftwareVersion::parseVersionString(currVer, major, minor, buildNumber);
}

Ns::IString Ns::OS::platformGetModulePathContainingAddress(const void *pv)
{
	Dl_info info = {0};
	if (!dladdr(pv, &info)) {
		NEUTRON_ASSERT(!"An image containing the given address could not be found.");
		return IString();
	}
	
	char *p = realpath(info.dli_fname, 0);
	IString ret(ToIString(p));
	free(p);

	return ret;
}

// --------------------------------------------------
// Image Utilities...
// --------------------------------------------------
void Ns::OS::platformGetImageSize(const IString& file, int& width, int& height)
{
	width = 0;
	height = 0;
	
	HString hString = ToHString(file);
	NSString* filePath = [[[NSString alloc] initWithCString: hString.c_str() encoding:NSUTF8StringEncoding] autorelease];
	NSImage* image = [[[NSImage alloc] initWithContentsOfFile:filePath] autorelease];
	if ([image isValid])
	{
		// NSImage::size() has some known issues calculating the size of images
		// whose underlying DPI is different from the user space screen DPI.
		// So we have to get the size from a specific image rep.
		//
        NSBitmapImageRep* rep = [NSBitmapImageRep imageRepWithData:[image TIFFRepresentation]];
        width = [rep pixelsWide];
		height = [rep pixelsHigh];
		
		// This code causes the application to crash periodically
		// when the autorelease pool is flushed.  Don't do this if
		// autorelease is used above!!!
		// [image release];
		
		image = nil;
	}
}

// --------------------------------------------------
// Environment Utilities...
// --------------------------------------------------
Ns::OS::PlatformThreadId sUIThreadId;
void Ns::OS::platformSetUIThread()
{
	sUIThreadId = platformThreadId();
}


bool Ns::OS::platformIsUIThread()
{
	return sUIThreadId == platformThreadId() || sUIThreadId == 0;
}

Ns::OS::PlatformThreadId Ns::OS::platformGetUIThread()
{
	if (sUIThreadId != 0)
		return platformThreadId();
	else
		return sUIThreadId;
}

Ns::OS::PlatformThreadId Ns::OS::platformThreadId()
{
	PlatformThreadId tid;
	pthread_t pid = pthread_self();
	pthread_threadid_np(pid, &tid);
	return tid;
}

Ns::OS::PlatformProcessId Ns::OS::platformProcessId()
{
	return getpid();
}

// --------------------------------------------------
// Environment Utilities...
// --------------------------------------------------
boost::filesystem::wpath Ns::OS::platformGetAppDirectory()
{
	return platformGetExecutableDirectory().parent_path().parent_path();
}

boost::filesystem::wpath Ns::OS::platformGetExecutableDirectory()
{
	boost::filesystem::wpath filename;

	static std::vector<char> path(2048);
    uint32_t siz = path.size();
    int32 ret = _NSGetExecutablePath(&path[0], &siz);
	if (ret < 0) {
		path.resize(siz);
		ret = _NSGetExecutablePath(&path[0], &siz);
		NEUTRON_ASSERT(ret == 0);
	}

	char *p = realpath(&path[0], 0);
	boost::filesystem::wpath real_path(ToIString(p));
	free(p);

	return real_path.parent_path();
}

boost::filesystem::wpath Ns::OS::platformGetTemporaryDirectory()
{
	const char* directory = [NSTemporaryDirectory() UTF8String];
	Ns::IString wDir = Ns::ToIString(directory);
	boost::filesystem::wpath result = wDir;
	return result;
}

boost::filesystem::wpath Ns::OS::platformGetUserDataDirectory()
{
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
	NSString *docDir = [paths objectAtIndex:0];
	boost::filesystem::wpath result = Ns::ToIString([docDir UTF8String]);
	return result;
}

boost::filesystem::wpath Ns::OS::platformGetUserDocumentsDirectory()
{
    
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES); 
    NSString *docDir = [paths objectAtIndex:0]; 
	boost::filesystem::wpath result = Ns::ToIString([docDir UTF8String]);
	return result;
}


Ns::IString Ns::OS::platformGetEnvironmentVariable(const Ns::IString& name)
{
	Ns::HString varName = Ns::ToHString(name);
	char* value = getenv(varName.c_str());
	Ns::HString result;
	if (value != NULL) {
		result = Ns::HString(value);
	}
	return Ns::ToIString(result);
}



// --------------------------------------------------
// File System Utilities...
// --------------------------------------------------
bool Ns::OS::platformIsReadOnly(const Ns::IString& path)
{
    if(!boost::filesystem::exists(path))
        return false;
    
	NSString* filePath = [[[NSString alloc] initWithCString: ToHString(path).c_str() encoding:NSUTF8StringEncoding] autorelease];
	NSFileManager* fileMgr = [[NSFileManager alloc]init];
	return ([fileMgr isWritableFileAtPath:filePath] != TRUE);
}

bool Ns::OS::platformMakeReadOnly(const Ns::IString& path)
{
	NSString* filePath = [[[NSString alloc] initWithCString: ToHString(path).c_str() encoding:NSUTF8StringEncoding] autorelease];
	NSFileManager* fileMgr = [[NSFileManager alloc]init];
	if ([fileMgr isWritableFileAtPath:filePath] == TRUE)
	{
		NSDictionary* newAttribute = [NSDictionary dictionaryWithObject:[NSNumber numberWithBool:YES] forKey:NSFileImmutable];
		return ([fileMgr setAttributes:newAttribute ofItemAtPath:filePath error:NULL] == YES);
	}
	
	return true;
}

bool Ns::OS::platformRemoveReadOnly(const Ns::IString& path)
{
	NSString* filePath = [[[NSString alloc] initWithCString: ToHString(path).c_str() encoding:NSUTF8StringEncoding] autorelease];
	NSFileManager* fileMgr = [[NSFileManager alloc]init];
	if ([fileMgr isWritableFileAtPath:filePath] == FALSE)
	{
		NSDictionary* newAttribute = [NSDictionary dictionaryWithObject:[NSNumber numberWithBool:FALSE] forKey:NSFileImmutable];
		return ([fileMgr setAttributes:newAttribute ofItemAtPath:filePath error:NULL] == YES);
	}
	
	return true;
}

bool Ns::OS::platformIsWcharUnicode()
{
	return true;
}

void Ns::OS::platformTraceMessage (bool bIsUnicode, const char* fileName, int lineNumber, ...)
{
	va_list args;
	va_start(args, lineNumber);
	if(bIsUnicode)
	{
		Ns::IString strFormat(va_arg(args, wchar_t*));
		Ns::IString strTraceMessage = platformFormat(strFormat, args);
		strTraceMessage += _NLI;
		
		// TODO: Need to decide which encoding the current CPU use
		//#if big endian
		//#define WCHAR_ENCODING NSUTF32BigEndianStringEncoding
		//#elif little endian
		//#define WCHAR_ENCODING NSUTF32LittleEndianStringEncoding
		//#endif
		NSString* result = [[NSString alloc] initWithBytes:strTraceMessage.c_str() length:(strTraceMessage.length() * sizeof(wchar_t)) encoding:NSUTF32LittleEndianStringEncoding];
		NSLog(@"%@", result);
		[result release];
	}
	else
	{
		Ns::HString strFormat(va_arg(args, char*));
		Ns::HString strTraceMessage = platformFormat(strFormat, args);
		strTraceMessage += _NLH;
		NSString* result = [[NSString alloc] initWithCString: strTraceMessage.c_str() encoding:NSUTF8StringEncoding];
		NSLog(@"%@", result);
		[result release];
	}
	
	va_end(args);
}

Ns::HString Ns::OS::platformFormat(Ns::HString strFormat, va_list args)
{
	// Unify the uses for Windows and Mac
	boost::replace_all(strFormat, _DNGH("%S"), _DNGH("%s"));
	
	// Get formatted string length
	va_list argsBackup;
	va_copy(argsBackup, args); // "args" changed after calling the vfprintf(...), so we need to copy one for next use
	FILE *devNull = fopen("/dev/null", "a");
	int len = vfprintf(devNull, strFormat.c_str(), args) + 1; // vwprintf(...) will print message to stdout, it's not what we want
	fclose(devNull);
	
	// Get formatted string
	char* buffer = new char[len];
	vsprintf(buffer, strFormat.c_str(), argsBackup);
	va_end(argsBackup);
	
	Ns::HString result(buffer);
	delete[] buffer;
	
	return result;
}

Ns::IString Ns::OS::platformFormat(Ns::IString strFormat, va_list args)
{
	boost::replace_all(strFormat, _DNGH("%s"), _DNGH("%S"));
	
	va_list argsBackup;
	va_copy(argsBackup, args);
	FILE *devNull = fopen("/dev/null", "a");
	int len = vfwprintf(devNull, strFormat.c_str(), args) + 1;
	fclose(devNull);
	
	wchar_t* buffer = new wchar_t[len];
	vswprintf(buffer, len, strFormat.c_str(), argsBackup);
	va_end(argsBackup);
	
	Ns::IString result(buffer);
	delete[] buffer;
	
	return result;
}

void Ns::OS::breakPoint()
{
	NEUTRON_ASSERT(false);
	char* p = NULL;
	*p = 'a';
}

bool Ns::OS::getCurProcessMemory(int nType, double& dValue, double& dPeakValue)
{
    static double s_dPeakValueOfResidentSize = 0.0;
    static double s_dPeakValueOfVirtualSize  = 0.0;
    
    task_basic_info         info;
    mach_port_t             task = mach_task_self();
    mach_msg_type_number_t  tcnt = TASK_BASIC_INFO_COUNT;
    task_info_t             tptr = (task_info_t) &info;
    
    memset(&info, 0, sizeof(info));
    
    const kern_return_t rval = task_info(task, TASK_BASIC_INFO, tptr, &tcnt);
    if (rval == KERN_SUCCESS)
    {
        if (eMemTypeWorkingSet == nType) 
        {
            if (info.resident_size > s_dPeakValueOfResidentSize) 
            {
                s_dPeakValueOfResidentSize = info.resident_size;
            }
            
            dValue     = info.resident_size;
            dPeakValue = s_dPeakValueOfResidentSize;
        } 
        else if (eMemTypePagefile == nType) 
        {
            if (info.virtual_size > s_dPeakValueOfVirtualSize)
            {
                s_dPeakValueOfVirtualSize = info.virtual_size;
            }
            
            dValue     = info.virtual_size;
            dPeakValue = s_dPeakValueOfVirtualSize;
        }
        
        return true;
    }
    
	return false;
}

bool Ns::OS::isMacSnowLeopard()
{
    SInt32 major = 0;
    SInt32 minor = 0;
    if (::macSys(major, minor))
    {
        return (10 == major && 6 == minor);
    }
    
    return false;
}

bool Ns::OS::isMacLion()
{
    SInt32 major = 0;
    SInt32 minor = 0;
    if (::macSys(major, minor))
    {
        return (10 == major && 7 == minor);
    }
    
    return false;
}
