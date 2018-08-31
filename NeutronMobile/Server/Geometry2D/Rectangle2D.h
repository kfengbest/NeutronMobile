#pragma once

#include "Geometry2D.h"
#include "Point2D.h"

class Rectangle2D : public Geometry2D
{
public:
	Rectangle2D(Entity* parent,const Point2D& startPoint, const Point2D& endPoint);
	virtual ~Rectangle2D(void);

	Point2D startPoint();
	Point2D endPoint();

private:
	Point2D m_startPoint;
	Point2D m_endPoint;
};
