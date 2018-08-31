//
//  GlMesh11.h
//  NeutronMobile
//
//  Created by fengka on 8/18/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#ifndef __NeutronMobile__GlContext__
#define __NeutronMobile__GlContext__

#include "../Server/Base/Globals.h"

namespace Ns { namespace Scene{
    class Camera;
    class Renderer;
    class Scene;
}}

class GlContext
{
private:
    GlContext();
    
public:
    virtual ~GlContext();

    static GlContext* get();
    
    void initialize(int width, int height);
    
    Ns::Scene::Camera* camera() const {return m_pCamera;}
    Ns::Scene::Renderer* renderer() const {return m_pRenderer;}
    void renderer(Ns::Scene::Renderer* pRenderer) { m_pRenderer = pRenderer;}
    Ns::Scene::Scene* mainScene() const {return m_pScene;}
    void mainScene(Ns::Scene::Scene* pScene) { m_pScene = pScene;}

private:
    int m_width;
    int m_height;
    Ns::Scene::Camera* m_pCamera;
    Ns::Scene::Renderer* m_pRenderer;
    Ns::Scene::Scene* m_pScene;
};

#endif /* defined(__NeutronMobile__GlContext__) */

