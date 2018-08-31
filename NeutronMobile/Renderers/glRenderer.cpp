//
//  glRenderer.cpp
//  NeutronMobile
//
//  Created by fengka on 8/18/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#include "../Server/Scene/Renderer.h"

#include "glMesh.h"
#include "../Server/Scene/Scene.h"
#include "../Server/Scene/GeometryNode.h"
#include "../Server/Scene/GroupNode.h"

using namespace Ns::Scene;

class glRenderer : public Ns::Scene::Renderer
{
public:
    glRenderer();
    virtual void render3D(Ns::Scene::Scene *scene );
    virtual void initialize(int width, int height);
};

glRenderer::glRenderer()
{
    
}

void glRenderer::render3D(Ns::Scene::Scene *scene)
{
    GroupNode::NodeList nodes = scene->rootNode()->children();
    GroupNode::NodeList::iterator it = nodes.begin();
    for (; it != nodes.end(); ++it) {
        
        if (GeometryNode* pGeoNode = dynamic_cast<GeometryNode*>(*it)) {
            
            if (Mesh* pMesh = dynamic_cast<Mesh*>(pGeoNode->geometry())) {
                
                if (pMesh->getAttachment() == NULL) {
                    glMesh* pGlMesh = new glMesh(pMesh);
                    pMesh->setAttachment(pGlMesh);
                }
                else{
                    glMesh* pGlMesh = dynamic_cast<glMesh*>(pMesh->getAttachment());
                    pGlMesh->render(true);
                }
            }
        }
    }
    
}

void glRenderer::initialize(int width, int height)
{
    
}

Renderer* CreateRenderer()
{
    return new glRenderer();
}
