
#include "Rectangle2D.h"


Rectangle2D::Rectangle2D(Entity* parent,const Point2D& startPoint, const Point2D& endPoint)
	: Geometry2D(parent),
	m_startPoint(startPoint),
	m_endPoint(endPoint)
{
    m_points.push_back(startPoint);
    m_points.push_back(Point2D(startPoint.x,endPoint.y));
    m_points.push_back(endPoint);
    m_points.push_back(Point2D(endPoint.x,startPoint.y));
    m_points.push_back(startPoint);
}

Rectangle2D::~Rectangle2D(void)
{
}

Point2D 
	Rectangle2D::startPoint()
{
	return m_startPoint;
}

Point2D 
	Rectangle2D::endPoint()
{
	return m_endPoint;
}
