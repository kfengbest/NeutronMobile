//
//  GlMesh11.cpp
//  NeutronMobile
//
//  Created by fengka on 8/18/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#include "GlMesh11.h"
#include "../Server/Scene/Mesh.h"
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include <vector>


using namespace Ns::Scene;
using namespace std;

GlMesh11::GlMesh11(Ns::Scene::Geometry* mesh)
: Ns::Object(),
m_mesh(mesh),
m_vertexBuffer(0),
m_indexBuffer(0),
m_indexCount(0)
{
//    createCone();

    createVBO();
}

void GlMesh11::render(bool textured)
{
  //  renderCone();
    
    renderVBO();
}


GlMesh11::~GlMesh11()
{
    
}

void GlMesh11::createCone()
{
    const float coneRadius = 0.5f;
    const float coneHeight = 1.866f;
    const int coneSlices = 40;
    const float dtheta = TwoPi / coneSlices;
    const int vertexCount = coneSlices * 2 + 1;
    const int diskCenterIndex = vertexCount - 1;
    
    m_bodyIndexCount = coneSlices * 3;
    m_diskIndexCount = coneSlices * 3;
    
    vector<Vertex> coneVertices(vertexCount);
    vector<Vertex>::iterator vertex = coneVertices.begin();
    
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
    
    vector<GLubyte> coneIndices(m_bodyIndexCount + m_diskIndexCount);
    vector<GLubyte>::iterator index = coneIndices.begin();
    
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

void GlMesh11::renderCone()
{

    const GLvoid* pColorOffset = (GLvoid*) sizeof(vec3);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), 0);
    glColorPointer(4, GL_FLOAT, sizeof(Vertex), pColorOffset);
    glEnableClientState(GL_VERTEX_ARRAY);
    const GLvoid* pBodyIndexOffset = 0;
    const GLvoid* pDiskIndexOffset = (GLvoid*)m_bodyIndexCount;
    
    glColor4f(1, 0, 0, 1);
    glDrawElements(GL_LINES, m_bodyIndexCount, GL_UNSIGNED_BYTE, pBodyIndexOffset);
    
    glEnableClientState(GL_COLOR_ARRAY);
    glDrawElements(GL_TRIANGLES, m_bodyIndexCount, GL_UNSIGNED_BYTE, pBodyIndexOffset);
    glDisableClientState(GL_COLOR_ARRAY);

    glColor4f(1, 1, 1, 1);
    glDrawElements(GL_TRIANGLES, m_diskIndexCount, GL_UNSIGNED_BYTE, pDiskIndexOffset);
    glDisableClientState(GL_VERTEX_ARRAY);
    
}

void GlMesh11::createVBO()
{
    // Create the VBO for the vertices.
    vector<float> vertices;
    m_mesh->GenerateVertices(vertices, VertexFlagsNormals);
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 vertices.size() * sizeof(vertices[0]),
                 &vertices[0],
                 GL_STATIC_DRAW);
    
    // Create a new VBO for the indices if needed.
    int indexCount = m_mesh->GetTriangleIndexCount();
    m_indexCount = indexCount;
    
    vector<GLushort> indices(indexCount);
    m_mesh->GenerateTriangleIndices(indices);
    glGenBuffers(1, &m_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indexCount * sizeof(GLushort),
                 &indices[0],
                 GL_STATIC_DRAW);

}

void GlMesh11::renderVBO()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    

    
//    // Set material.
//    vec3 color(0.25,0.75, 1);
//    color = color * 0.75f;
//    vec4 diffuse(color.x, color.y, color.z, 1);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse.Pointer());
    
    // Draw the mesh.
    int stride = 2 * sizeof(vec3);
    const GLvoid* normalOffset = (const GLvoid*) sizeof(vec3);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glVertexPointer(3, GL_FLOAT, stride, 0);
    glNormalPointer(GL_FLOAT, stride, normalOffset);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, 0);
}

