#define __COMPILING_NS_GLOBALS_CPP__
#include "Globals.h"
#undef __COMPILING_NS_GLOBALS_CPP__
#include "utf8/utf8.h"
 
using namespace Ns;

IString Ns::ToIString(const HString& strHSrc)
{
	IString utfXstr;
	utfXstr.reserve(utf8::unchecked::distance(strHSrc.begin(), strHSrc.end()));
	if (sizeof(IString::value_type) == 2)
		utf8::unchecked::utf8to16(strHSrc.begin(), strHSrc.end(), std::back_inserter(utfXstr));
	else if (sizeof(IString::value_type) == 4)
		utf8::unchecked::utf8to32(strHSrc.begin(), strHSrc.end(), std::back_inserter(utfXstr));
	return utfXstr;
}

HString Ns::ToHString(const IString& strISrc)
{
	HString utf8str;
	utf8str.reserve(strISrc.size());
	if (sizeof(IString::value_type) == 2)
		utf8::unchecked::utf16to8(strISrc.begin(), strISrc.end(), std::back_inserter(utf8str));
	else if (sizeof(IString::value_type) == 4)
		utf8::unchecked::utf32to8(strISrc.begin(), strISrc.end(), std::back_inserter(utf8str));
	return utf8str;
}

std::auto_ptr<wchar_t> Ns::ToStringW(const char* strHSrc)
{	
	size_t length = strlen(strHSrc) + 1;
	std::auto_ptr<wchar_t> _strSrc((wchar_t*)operator new(sizeof(wchar_t)*(length)));
	
	HString _strHSrc(strHSrc);
	IString utfXstr;
	utfXstr.reserve(length);
	if (sizeof(IString::value_type) == 2)
		utf8::unchecked::utf8to16(_strHSrc.begin(), _strHSrc.end(), std::back_inserter(utfXstr));
	else if (sizeof(IString::value_type) == 4)
		utf8::unchecked::utf8to32(_strHSrc.begin(), _strHSrc.end(), std::back_inserter(utfXstr));
	wcscpy(_strSrc.get(), utfXstr.c_str());
	return _strSrc;
}

std::auto_ptr<char> Ns::ToStringA(const wchar_t* strISrc)
{	
	IString _strISrc(strISrc);
	HString utf8str;
	// Reserve the max buffer size, so that we will always get good performance.
	utf8str.reserve(sizeof(wchar_t)*wcslen(strISrc)+1);
    
	if (sizeof(IString::value_type) == 2)
		utf8::unchecked::utf16to8(_strISrc.begin(), _strISrc.end(), std::back_inserter(utf8str));
	else if (sizeof(IString::value_type) == 4)
		utf8::unchecked::utf32to8(_strISrc.begin(), _strISrc.end(), std::back_inserter(utf8str));

    // For the Unicode Code encoding, the multiple bytes characters such as Chinese and Japanese will take more than one bytes
	// so we need to allocate the exactly size of char buffer after the convention.
	size_t length = utf8str.length() + 1;
	std::auto_ptr<char> _strSrc( (char*)::operator new(sizeof(char)*(length)));    
	strcpy(_strSrc.get(), utf8str.c_str());
    
	return _strSrc;
}