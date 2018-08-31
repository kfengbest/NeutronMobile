#pragma once
#include "../Archive/Globals.h"
#include <string>
#include <vector>
#include <set>

//#include <boost/uuid/uuid.hpp>
//#include <boost/unordered_set.hpp>
//#include <boost/unordered_map.hpp>

#ifdef NS_BASE_EXPORTS
# ifdef __COMPILING_NS_GLOBALS_CPP__
#  define NS_BASE_API NS_EXPORT
# else
#  define NS_BASE_API
# endif
#else
# define NS_BASE_API NS_IMPORT
#endif

#define FY_EPSILON 1.0e-7
#define COS_THRESH (1.0f - FY_EPSILON)
#define PI 3.14159265358979323846f
#define TWOPI 6.28318530717958623200f
#define fyfastabs(f) ((f) < 0 ? -(f) : (f))
#define fymin(a,b) ((a) < (b) ? (a) : (b))
#define fymax(a,b) ((a) > (b) ? (a) : (b))

namespace Ns {

	typedef std::basic_string<IChar>	IString;
	typedef std::basic_string<HChar>	HString;
	typedef std::vector<unsigned char>	Bytes;
	Bytes								BytesConvert(const HString& strHSrc);
	HString								BytesConvert(const Bytes& bytes);
//	typedef std::set<EntityId>			EntityIds;

	/// Assumes \a strHSrc uses UTF-8 encoding.
	/*NS_ARCHIVE_API*/ 
	NS_BASE_API std::auto_ptr<wchar_t>			ToStringW(const char* strHSrc);

	/// Converts \a strISrc to a UTF-8 string.
	/*NS_ARCHIVE_API*/
	NS_BASE_API std::auto_ptr<char>				ToStringA(const wchar_t* strISrc);

//	// UUID...
//	typedef boost::uuids::uuid			Uuid;
//	typedef std::vector<Uuid>			Uuids;
	
	// Strings...
	DEPRECATED_PREFIX IString StringConvert(const HString& strHSrc) DEPRECATED_SUFFIX; // Use ToIString or ToHString instead
	DEPRECATED_PREFIX HString StringConvert(const IString& strISrc) DEPRECATED_SUFFIX; // Use ToIString or ToHString instead
	typedef std::vector<IString> IStringVec;

	/// Assumes \a strHSrc uses UTF-8 encoding.
	NS_BASE_API IString ToIString(const HString& strHSrc);
	
	/// Converts \a strISrc to a UTF-8 string.
	NS_BASE_API HString ToHString(const IString& strISrc);

	// Mathematical constants.
	/* Definitions of useful mathematical constants
	 * The following is an extract from math.h, in case someone wants to add constants
	 * M_E        - e
	 * M_LOG2E    - log2(e)
	 * M_LOG10E   - log10(e)
	 * M_LN2      - ln(2)
	 * M_LN10     - ln(10)
	 * M_PI       - pi
	 * M_PI_2     - pi/2
	 * M_PI_4     - pi/4
	 * M_1_PI     - 1/pi
	 * M_2_PI     - 2/pi
	 * M_2_SQRTPI - 2/sqrt(pi)
	 * M_SQRT2    - sqrt(2)
	 * M_SQRT1_2  - 1/sqrt(2)

	 *	#define M_E        2.71828182845904523536
	 *	#define M_LOG2E    1.44269504088896340736
	 *	#define M_LOG10E   0.434294481903251827651
	 *	#define M_LN2      0.693147180559945309417
	 *	#define M_LN10     2.30258509299404568402
	 *	#define M_PI       3.14159265358979323846
	 *	#define M_PI_2     1.57079632679489661923
	 *	#define M_PI_4     0.785398163397448309616
	 *	#define M_1_PI     0.318309886183790671538
	 *	#define M_2_PI     0.636619772367581343076
	 *	#define M_2_SQRTPI 1.12837916709551257390
	 *	#define M_SQRT2    1.41421356237309504880
	 *	#define M_SQRT1_2  0.707106781186547524401
	 */

	const double kPi = 3.14159265358979323846;
	const double kTwoPi = kPi*2;
	const double kHalfPi = kPi/2;
    
    
}

inline Ns::IString Ns::StringConvert(const Ns::HString& strHSrc)
{
	return ToIString(strHSrc);
}

inline Ns::HString Ns::StringConvert(const Ns::IString& strISrc)
{
	return ToHString(strISrc);
}

inline Ns::Bytes Ns::BytesConvert(const HString& strHSrc)
{
	return Bytes(strHSrc.begin(), strHSrc.end());
}

inline Ns::HString Ns::BytesConvert(const Bytes& bytes)
{
	return HString(bytes.begin(), bytes.end());
}

#if defined (NEUTRON_OS_WIN)
#include <hash_set>
#include <hash_map>
#elif defined(NEUTRON_OS_MAC)
#include <ext/hash_set>
#include <ext/hash_map>
namespace std {
	using namespace __gnu_cxx;
}

#endif

#undef NS_BASE_API
