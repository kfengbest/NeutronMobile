//
//  Scene.h
//  NeutronMobile
//
//  Created by fengka on 8/18/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#pragma once

#include "../Base/Globals.h"
#include "GroupNode.h"

#ifdef NS_SCENE_EXPORTS
# ifdef __COMPILING_NS_SCENE_CPP__
#  define NS_SCENE_API NS_EXPORT
# else
#  define NS_SCENE_API
# endif
#else
# define NS_SCENE_API NS_IMPORT
#endif

namespace Ns { namespace Scene {
    class NS_SCENE_API Scene{
    public:
        
        Scene();
        ~Scene();
        
        GroupNode* rootNode() const;
        
    private:
        GroupNode* m_pRoot;
    };
}}


#undef NS_SCENE_API