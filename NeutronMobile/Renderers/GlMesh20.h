//
//  GlMesh11.h
//  NeutronMobile
//
//  Created by fengka on 8/18/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#ifndef __NeutronMobile__GlMesh20__
#define __NeutronMobile__GlMesh20__

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "../Server/Base/Types/Object.h"
#include "../Server/Scene/Mesh.h"
#include "../server/Types/Vector.hpp"


namespace Ns { namespace Scene{
    class Mesh;
}}

struct Vertex2 {
    vec3 Position;
    vec4 Color;
};

class GlMesh20 : public Ns::Object
{
  
public:
    GlMesh20(Ns::Scene::Mesh* mesh);
    virtual ~GlMesh20();

    void render(bool textured);

private:
    void createCone();
    
private:
    Ns::Scene::Mesh *m_mesh;
    
    GLuint m_vertexBuffer;
    GLuint m_indexBuffer;
    int m_diskIndexCount;
    int m_bodyIndexCount;

};

#endif /* defined(__NeutronMobile__GlMesh1111__) */
