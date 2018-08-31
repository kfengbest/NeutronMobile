//
//  Mesh.cpp
//  NeutronMobile
//
//  Created by fengka on 8/18/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#define __COMPILING_NS_MESH_CPP__
#include "Mesh.h"
#undef __COMPILING_NS_MESH_CPP__

#include "Scene.h"

using namespace Ns;
using namespace Ns::Scene;


Mesh::Mesh(Scene* scene)
: Geometry(scene),
m_coneVertices(),
m_coneIndices(),
m_bodyIndexCount(0),
m_diskIndexCount(0)
{
    
}

Mesh::~Mesh()
{
    
}

const std::vector<Vertex>&
Mesh::vertices()
{
    return m_coneVertices;
}

std::vector<unsigned char>
Mesh::indices()
{
    return m_coneIndices;
}
