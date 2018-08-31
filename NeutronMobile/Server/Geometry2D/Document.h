#pragma once

#include "Entity.h"
#include "INodeSource.h"
#include "../Types/Color.h"

class Document : public Entity,
				public INodeSource
{
public:
	Document(void);
	virtual ~Document(void);
	
	void addEntity(Entity* pEntity);
    const EntityVec& entities();
    
	virtual void draw();

// Temporary to share data. remove it later.
public:
    Ns::Core::Color m_color;
	float m_thickness;
    
private:
	EntityVec m_entities;

};

