
#include "Sketch.h"


Sketch::Sketch(Entity* parent)
	: Geometry2D(parent)
{
}


Sketch::~Sketch(void)
{
}

void 
Sketch::addPoint2D(const Point2D& point)
{
	m_points.push_back(point);
}