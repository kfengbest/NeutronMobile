//
//  glMesh.h
//  NeutronMobile
//
//  Created by fengka on 8/18/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#ifndef __NeutronMobile__glMesh__
#define __NeutronMobile__glMesh__

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include "../Server/Base/Types/Object.h"
#include "../Server/Scene/Mesh.h"


namespace Ns { namespace Scene{
    class Mesh;
}}

class glMesh : public Ns::Object
{
  
public:
    glMesh(Ns::Scene::Mesh* mesh);
    virtual ~glMesh();

    void render(bool textured);

private:
    Ns::Scene::Mesh *m_mesh;
    
    GLuint m_glVertexArray;
    GLuint m_glVertexBuffer;
    GLuint m_glIndexBuffer;


};

#endif /* defined(__NeutronMobile__glMesh__) */
