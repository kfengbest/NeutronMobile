#pragma once

#include "../Base/Globals.h"


#ifdef NS_GEOMETRY3D_EXPORTS
# ifdef __COMPILING_NS_CUBE_CPP__
#  define NS_GEOMETRY3D_API NS_EXPORT
# else
#  define NS_GEOMETRY3D_API
# endif
#else
# define NS_GEOMETRY3D_API NS_IMPORT
#endif

namespace Ns { namespace Geometry {
    
    class NS_GEOMETRY3D_API Cube{
        
    };
}}


#undef NS_GEOMETRY3D_API
