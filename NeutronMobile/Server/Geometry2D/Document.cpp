
#include "Document.h"
#include "Geometry2D.h"

Document::Document(void)
	:Entity(NULL),
    m_thickness(1.0),
    m_color()
{
}


Document::~Document(void)
{
}

void 
Document::addEntity(Entity* pEntity)
{
	m_entities.push_back(pEntity);
}

void 
Document::draw()
{
	EntityVec::iterator it = m_entities.begin();
	EntityVec::iterator ite = m_entities.end();
	for (;it != ite; ++it)
	{
		if (Geometry2D* geo = dynamic_cast<Geometry2D*>(*it))
		{
			geo->draw();
		}
	}
}

const EntityVec& 
Document::entities()
{
    return m_entities;
}
