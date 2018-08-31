
#include "Geometry2D.h"


Geometry2D::Geometry2D(Entity* parent)
	: Entity(parent),
	m_thickness(1.0),
    m_color()
{
}


Geometry2D::~Geometry2D(void)
{
}

void 
Geometry2D::lineThickness(float thickness)
{
	m_thickness = thickness;
}

float 
Geometry2D::lineThickness() const
{
	return m_thickness;
}

void 
Geometry2D::lineColor(const Ns::Core::Color& color)
{
	m_color = color;
}

const Ns::Core::Color& 
Geometry2D::lineColor() const
{
	return m_color;
}
  
const std::vector<Point2D>& 
Geometry2D::pointsStrip()
{
    return m_points;
}
