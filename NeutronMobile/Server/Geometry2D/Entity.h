#pragma once

#include <vector>
#include "../Base/Types/Object.h"

class Entity;
typedef std::vector<Entity*> EntityVec;

class Entity : Ns::Object
{
public:
	Entity(Entity* parent);
	virtual ~Entity(void);

	Entity* parent();

private:
	Entity* m_parent;
};

