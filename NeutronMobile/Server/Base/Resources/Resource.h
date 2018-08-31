#pragma once
 
#include "../Globals.h"

#ifdef NS_BASE_EXPORTS
# ifdef __COMPILING_NS_RESOURCE_CPP__
#  define NS_BASE_API NS_EXPORT
# else
#  define NS_BASE_API
# endif
#else
# define NS_BASE_API NS_IMPORT
#endif

namespace Ns {

	class NS_BASE_API Resource{
        
    };
}


#undef NS_BASE_API


