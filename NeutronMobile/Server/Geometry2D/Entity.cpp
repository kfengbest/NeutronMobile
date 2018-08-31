
#include "Entity.h"

using namespace Ns;

Entity::Entity(Entity* parent)
	:Object(),
    m_parent(parent)
{
}


Entity::~Entity(void)
{
}

Entity* 
Entity::parent()
{
	return m_parent;
}