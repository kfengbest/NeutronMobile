#pragma once

#include "Entity.h"
#include "INodeSource.h"
#include "../Types/Color.h"
#include "Point2D.h"
#include <vector>

class Point2D;

class Geometry2D : public Entity,
					public INodeSource
{
public:
	Geometry2D(Entity* parent);
	virtual ~Geometry2D(void);

	void lineThickness(float thickness);
	float lineThickness() const;
	void lineColor(const Ns::Core::Color& color);
	const const Ns::Core::Color& lineColor() const;
    const std::vector<Point2D>& pointsStrip();
    
	virtual void draw(){};

protected:
    std::vector<Point2D> m_points;
    
private:
    Ns::Core::Color m_color;
	float m_thickness;

};

