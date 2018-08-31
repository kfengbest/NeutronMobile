
#define __COMPILING_NS_NODE_CPP__
#include "Node.h"
#undef __COMPILING_NS_NODE_CPP__

using namespace Ns::Scene;

Node::Node()
: Entity(NULL),
m_globalMatrix(mat4::Identity()),
m_color(0.5,0.5,0.5,1.0)
{
    
}

Node::~Node()
{
    
}