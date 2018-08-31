#pragma once

#include "../Globals.h"
#include <string>

#ifdef NS_BASE_EXPORTS
# ifdef __COMPILING_NS_RESOURCEMGR_CPP__
#  define NS_BASE_API NS_EXPORT
# else
#  define NS_BASE_API
# endif
#else
# define NS_BASE_API NS_IMPORT
#endif

namespace Ns {
    
	class NS_BASE_API ResourceMgr
    {
    public:
        
        virtual std::string getResourcePath() const = 0;

    };
}


#undef NS_BASE_API


