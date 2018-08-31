//
//  GlMesh11.h
//  NeutronMobile
//
//  Created by fengka on 8/18/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#ifndef __NeutronMobile__GlMesh11__
#define __NeutronMobile__GlMesh11__

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include "../Server/Base/Types/Object.h"
#include "../Server/Scene/Mesh.h"
#include "../server/Types/Vector.hpp"

namespace Ns { namespace Scene{
    class Mesh;
}}

class GlMesh11 : public Ns::Object
{
  
public:
    GlMesh11(Ns::Scene::Geometry* mesh);
    virtual ~GlMesh11();

    void render(bool textured);


private:
    Ns::Scene::Geometry *m_mesh;
    
    GLuint  m_vertexBuffer;
    GLuint  m_indexBuffer;
    int     m_indexCount;

    int m_diskIndexCount;
    int m_bodyIndexCount;
    void createCone();
    void renderCone();

    void createVBO();
    void renderVBO();

};

#endif /* defined(__NeutronMobile__GlMesh1111__) */
