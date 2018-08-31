//
//  Scene.cpp
//  NeutronMobile
//
//  Created by fengka on 8/17/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#include "Scene.h"

using namespace Ns::Scene;

Scene::Scene()
{
    m_pRoot = new GroupNode();
}

Scene::~Scene()
{
    delete m_pRoot;
}

GroupNode* Scene::rootNode() const
{
    return m_pRoot;
}
