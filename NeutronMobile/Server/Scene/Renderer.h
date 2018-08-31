//
//  Render.h
//  NeutronMobile
//
//  Created by fengka on 8/18/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#pragma once

#include "../Base/Globals.h"


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
    
    class Scene;
    
    class NS_SCENE_API Renderer{
        
    public:
        virtual void render3D(Scene *scene) = 0;
        virtual void initialize(int width, int height) = 0;

    };
    

    
}}

Ns::Scene::Renderer* CreateRenderer();
Ns::Scene::Renderer* CreateRenderer1();
Ns::Scene::Renderer* CreateRenderer2();

#undef NS_SCENE_API
