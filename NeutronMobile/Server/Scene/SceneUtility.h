//
//  SceneUtility.h
//  NeutronMobile
//
//  Created by fengka on 8/18/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#pragma once

#include "../Base/Globals.h"
#include "Mesh.h"

#ifdef NS_SCENE_EXPORTS
# ifdef __COMPILING_NS_SCENEUTILITY_CPP__
#  define NS_SCENE_API NS_EXPORT
# else
#  define NS_SCENE_API
# endif
#else
# define NS_SCENE_API NS_IMPORT
#endif

namespace Ns { namespace Scene {
    
    class NS_SCENE_API SceneUtility
    {
    public:
        
        static Mesh* createCube();
        static Mesh* createCone();
        
    };
}}


#undef NS_SCENE_API