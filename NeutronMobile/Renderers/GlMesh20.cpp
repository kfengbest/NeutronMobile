//
//  GlMesh11.cpp
//  NeutronMobile
//
//  Created by fengka on 8/18/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#include "GlMesh20.h"
#include "../Server/Scene/Mesh.h"
#include <vector>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

using namespace Ns::Scene;


GlMesh20::GlMesh20(Ns::Scene::Mesh* mesh)
: Ns::Object(),
m_mesh(mesh)
{
    createCone();
    
}

void GlMesh20::render(bool textured)
{
//    if(m_mesh == NULL || m_mesh->getNumVertices() == 0)
//		return;
//   

//    GLsizei stride = sizeof(Vertex2);
//    const GLvoid* colorOffset = (GLvoid*) sizeof(vec3);
//   
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
//    glVertexAttribPointer(positionSlot, 3, GL_FLOAT, GL_FALSE, stride, 0);
//    glVertexAttribPointer(colorSlot, 4, GL_FLOAT, GL_FALSE, stride, colorOffset);
//    glEnableVertexAttribArray(positionSlot);
//    
//    const GLvoid* bodyOffset = 0;
//    const GLvoid* diskOffset = (GLvoid*) m_bodyIndexCount;
//    
//    glEnableVertexAttribArray(colorSlot);
//    glDrawElements(GL_TRIANGLES, m_bodyIndexCount, GL_UNSIGNED_BYTE, bodyOffset);
//    glDisableVertexAttribArray(colorSlot);
//    glVertexAttrib4f(colorSlot, 1, 1, 1, 1);
//    glDrawElements(GL_TRIANGLES, m_diskIndexCount, GL_UNSIGNED_BYTE, diskOffset);
//    
//    glDisableVertexAttribArray(positionSlot);


}


GlMesh20::~GlMesh20()
{
    
}

void GlMesh20::createCone()
{
    const float coneRadius = 0.5f;
    const float coneHeight = 1.866f;
    const int coneSlices = 40;
    const float dtheta = TwoPi / coneSlices;
    const int vertexCount = coneSlices * 2 + 1;
    const int diskCenterIndex = vertexCount - 1;
    
    m_bodyIndexCount = coneSlices * 3;
    m_diskIndexCount = coneSlices * 3;
    
    std::vector<Vertex2> coneVertices(vertexCount);
    std::vector<Vertex2>::iterator vertex = coneVertices.begin();
    
    // Cone's body
    for (float theta = 0; vertex != coneVertices.end() - 1; theta += dtheta) {
        
        // Grayscale gradient
        float brightness = abs(sin(theta));
        vec4 color(brightness, brightness, brightness, 1);
        
        // Apex vertex
        vertex->Position = vec3(0, 1, 0);
        vertex->Color = color;
        vertex++;
        
        // Rim vertex
        vertex->Position.x = coneRadius * cos(theta);
        vertex->Position.y = 1 - coneHeight;
        vertex->Position.z = coneRadius * sin(theta);
        vertex->Color = color;
        vertex++;
    }
    
    // Disk center
    vertex->Position = vec3(0, 1 - coneHeight, 0);
    vertex->Color = vec4(1, 1, 1, 1);
    
    // Create the VBO for the vertices.
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 coneVertices.size() * sizeof(coneVertices[0]),
                 &coneVertices[0],
                 GL_STATIC_DRAW);
    
    std::vector<GLubyte> coneIndices(m_bodyIndexCount + m_diskIndexCount);
    std::vector<GLubyte>::iterator index = coneIndices.begin();
    
    // Body triangles
    for (int i = 0; i < coneSlices * 2; i += 2) {
        *index++ = i;
        *index++ = (i + 1) % (2 * coneSlices);
        *index++ = (i + 3) % (2 * coneSlices);
    }
    
    // Disk triangles
    for (int i = 1; i < coneSlices * 2 + 1; i += 2) {
        *index++ = diskCenterIndex;
        *index++ = i;
        *index++ = (i + 2) % (2 * coneSlices);
    }
    
    // Create the VBO for the indices.
    glGenBuffers(1, &m_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 coneIndices.size() * sizeof(coneIndices[0]),
                 &coneIndices[0],
                 GL_STATIC_DRAW);

}

