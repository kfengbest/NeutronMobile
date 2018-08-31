#pragma once

#include "Geometry2D.h"
#include "Point2D.h"
#include <vector>

class Sketch : public Geometry2D
{
public:
	Sketch(Entity* parent);
	virtual ~Sketch(void);

	void addPoint2D(const Point2D& point);

};

