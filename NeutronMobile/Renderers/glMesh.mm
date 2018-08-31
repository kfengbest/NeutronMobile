//
//  glMesh.cpp
//  NeutronMobile
//
//  Created by fengka on 8/18/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#include "glMesh.h"
#include "../Server/Scene/Mesh.h"
#include <GLKit/GLKit.h>

using namespace Ns::Scene;


glMesh::glMesh(Ns::Scene::Mesh* mesh)
: Ns::Object(),
m_mesh(mesh)
{
    m_glVertexArray=0;
    m_glIndexBuffer=0;
    m_glVertexBuffer=0;
    
//    glGenVertexArraysOES(1, &m_glVertexArray);
//    glBindVertexArrayOES(m_glVertexArray);
//    
//    // allocate the vertex buffer
//    glGenBuffers(1, &m_glVertexBuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, m_glVertexBuffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(Ns::Scene::Vertex)*24, m_mesh->getVertices(), GL_STATIC_DRAW);
//    
//    // and index buffer
//    glGenBuffers(1, &m_glIndexBuffer);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_glIndexBuffer);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned char)*36, m_mesh->getIndices(), GL_STATIC_DRAW);
//    
//    glEnableVertexAttribArray(GLKVertexAttribPosition);
//    glVertexAttribPointer(GLKVertexAttribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Ns::Scene::Vertex), (const GLvoid *) offsetof(Ns::Scene::Vertex, Position));
//    
//    glEnableVertexAttribArray(GLKVertexAttribColor);
//    glVertexAttribPointer(GLKVertexAttribColor, 4, GL_FLOAT, GL_FALSE, sizeof(Ns::Scene::Vertex), (const GLvoid *) offsetof(Ns::Scene::Vertex, Color));
//    
//    glBindVertexArrayOES(0);    
    
}

void glMesh::render(bool textured)
{
//    if(m_mesh == NULL || m_mesh->getNumVertices() == 0)
//		return;
//    
//    glBindVertexArrayOES(m_glVertexArray);
//    glDrawElements(GL_TRIANGLES, m_mesh->getNumIndices(), GL_UNSIGNED_BYTE, 0);
//    glBindVertexArrayOES(0);
}


glMesh::~glMesh()
{
    
}

