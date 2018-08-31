
#define __COMPILING_NS_GEOMETRYNODE_CPP__
#include "GeometryNode.h"
#undef __COMPILING_NS_GEOMETRYNODE_CPP__

using namespace Ns::Scene;

GeometryNode::GeometryNode()
: Node()
{
    
}

GeometryNode::~GeometryNode()
{
    
}

Geometry* GeometryNode::geometry() const
{
    return m_pMesh;
}

void GeometryNode::geometry(Geometry* pMesh)
{
    m_pMesh = pMesh;
}