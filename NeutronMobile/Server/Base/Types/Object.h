#pragma once

// ------------------------------------------------------------
// Object is the base class from which the majority of all 
// classes derive.  Currently it is very lightweight, and
// only provides a virtual method for determining whether
// the class implements an interface.  Interfaces should
// not derive from Object.
// -----------------------------------------------------------

#include "../Globals.h"

#ifdef NS_BASE_EXPORTS
# ifdef __COMPILING_NS_OBJECT_CPP__
#  define NS_BASE_API NS_EXPORT
# else
#  define NS_BASE_API
# endif
#else
# define NS_BASE_API NS_IMPORT
#endif

namespace Ns 
{
	class NS_BASE_API Object
	{
	public:
		Object();		
		virtual ~Object();
	};


}


#undef NS_BASE_API
