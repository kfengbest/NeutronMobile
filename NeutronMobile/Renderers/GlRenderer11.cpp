//
//  GlRenderer1.cpp
//  TestGL
//
//  Created by fengka on 8/25/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#include "../Server/Scene/Renderer.h"
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

#include "GlMesh11.h"
#include "../Server/Scene/Scene.h"
#include "../Server/Scene/GeometryNode.h"
#include "../Server/Scene/GroupNode.h"
#include "../Server/Scene/Camera.h"
#include "GlContext.h"

using namespace Ns::Scene;
using namespace std;

class GlRenderer11 : public Renderer
{
public:
    GlRenderer11();
    virtual void initialize(int width, int height);
    virtual void render3D(Scene *scene);
    
private:
    GLuint m_framebuffer;
    GLuint m_colorRenderBuffer;
    GLuint m_depthRenderBuffer;
    
};

GlRenderer11::GlRenderer11()
{
    // create color render buffer.
    glGenRenderbuffersOES(1, &m_colorRenderBuffer);
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, m_colorRenderBuffer);
}

Renderer* CreateRenderer1()
{
    return new GlRenderer11();
}

void GlRenderer11::initialize(int width, int height)
{
    // create depth render buffer
    glGenRenderbuffersOES(1, &m_depthRenderBuffer);
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, m_depthRenderBuffer);
    glRenderbufferStorageOES(GL_RENDERBUFFER_OES, GL_DEPTH_COMPONENT16_OES, width, height);
    
    // create frame buffer, attach with color and depth buffer.
    glGenFramebuffersOES(1, &m_framebuffer);
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, m_framebuffer);
    glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES,
                                 GL_COLOR_ATTACHMENT0_OES,
                                 GL_RENDERBUFFER_OES,
                                 m_colorRenderBuffer);
    glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES,
                                 GL_DEPTH_ATTACHMENT_OES,
                                 GL_RENDERBUFFER_OES,
                                 m_depthRenderBuffer);
    
    // Bind color buffer for rendering.
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, m_colorRenderBuffer);
    
    glViewport(0, 0, width, height);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
    // setup lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    // Setup the material properties.
    vec4 specular(0.25f, 0.25f, 0.25f, 1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular.Pointer());
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0f);
    
    glMatrixMode(GL_PROJECTION);
    glFrustumf(-1.6, 1.6, -2.4, 2.4, 5, 10);
    
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(0, 0, -7);
    
}

void GlRenderer11::render3D(Scene *scene)
{
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set lighting.
    vec4 lightPosition(0.25, 0.25, 1, 0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition.Pointer());
    
    GroupNode::NodeList nodes = scene->rootNode()->children();
    GroupNode::NodeList::iterator it = nodes.begin();
    for (; it != nodes.end(); ++it) {
        
        if (GeometryNode* pGeoNode = dynamic_cast<GeometryNode*>(*it)) {
            
            if (Geometry* pMesh = pGeoNode->geometry()) {
                
                if (pMesh->getAttachment() == NULL) {
                    GlMesh11* pGlMesh = new GlMesh11(pMesh);
                    pMesh->setAttachment(pGlMesh);
                }
                else{
                    GlMesh11* pGlMesh = dynamic_cast<GlMesh11*>(pMesh->getAttachment());
                    
                    // Transform.
                    mat4 m = pGeoNode->globalMatrix();
                    glMatrixMode(GL_MODELVIEW);
                    mat4 cameraMtx = GlContext::get()->camera()->orientation().ToMatrix();
                    mat4 zTranslation = mat4::Translate(0, 0, -7);
                    m = cameraMtx * m * zTranslation;
                    glLoadMatrixf(m.Pointer());
                    
                    // Material
                    vec4 diffuse = pGeoNode->color();
                    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse.Pointer());
                    pGlMesh->render(true);
                    
                }
            }
        }
    }
    
}
