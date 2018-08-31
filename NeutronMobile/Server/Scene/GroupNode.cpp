
#define __COMPILING_NS_GROUPNODE_CPP__
#include "GroupNode.h"
#undef __COMPILING_NS_GROUPNODE_CPP__

using namespace Ns::Scene;

GroupNode::GroupNode()
: Node()
{
    
}

GroupNode::~GroupNode()
{
    removeAllChildren();
}

void GroupNode::addChild(Node* pNode)
{
    NodeList::iterator i = std::find(m_children.begin(), m_children.end(), pNode);
	if (i == m_children.end())
	{
		m_children.push_back(pNode);
	}
}

void GroupNode::removeChild(Node* pNode)
{
    NodeList::iterator i = std::find(m_children.begin(), m_children.end(), pNode);
	if (i != m_children.end())
	{
		m_children.erase(i);
	}
}

void GroupNode::removeAllChildren()
{
    
    m_children.clear();
}

const GroupNode::NodeList&	GroupNode::children() const
{
    return m_children;
}