#pragma once

#include "Geometry2D.h"
#include "Point2D.h"

class Line2D : public Geometry2D
{
public:
	Line2D(Entity* parent, const Point2D& startPoint, const Point2D& endPoint);
	virtual ~Line2D(void);

	Point2D startPoint();
	Point2D endPoint();

protected:
    virtual void realizeGeometry(std::vector<Point2D>& pointList);
    
private:
	Point2D m_startPoint;
	Point2D m_endPoint;
};

