
#include "Line2D.h"


Line2D::Line2D(Entity* parent,const Point2D& startPoint, const Point2D& endPoint)
	: Geometry2D(parent),
	m_startPoint(startPoint),
	m_endPoint(endPoint)
{
    m_points.push_back(startPoint);
    m_points.push_back(endPoint);
}

Line2D::~Line2D(void)
{
}

Point2D 
Line2D::startPoint()
{
	return m_startPoint;
}

Point2D 
Line2D::endPoint()
{
	return m_endPoint;
}

void 
Line2D::realizeGeometry(std::vector<Point2D>& pointList)
{
    pointList.push_back(m_startPoint);
    pointList.push_back(m_endPoint);
    
}