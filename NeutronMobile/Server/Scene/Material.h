#pragma once

#include "../Base/Globals.h"


#ifdef NS_SCENE_EXPORTS
# ifdef __COMPILING_NS_MATERIAL_CPP__
#  define NS_SCENE_API NS_EXPORT
# else
#  define NS_SCENE_API
# endif
#else
# define NS_SCENE_API NS_IMPORT
#endif

namespace Ns { namespace Scene {
    
    class Scene;
    
    class NS_SCENE_API Material{
                
    };
}}


#undef NS_SCENE_API

