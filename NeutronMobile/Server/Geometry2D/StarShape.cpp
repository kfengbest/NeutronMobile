//
//  StarShape.cpp
//  NeutronMobile
//
//  Created by fengka on 8/3/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#include "StarShape.h"

StarShape::StarShape(Entity* parent,const Point2D& startPoint, const Point2D& endPoint)
: Geometry2D(parent),
m_startPoint(startPoint),
m_endPoint(endPoint)
{
    int width = m_endPoint.x - m_startPoint.x;
    int height = m_endPoint.y - m_startPoint.y;
    
    Point2D p0(m_startPoint.x + width/2, m_startPoint.y);
    Point2D p1(m_startPoint.x + width/3, m_endPoint.y);
    Point2D p2(m_endPoint.x, m_startPoint.y + height/3);
    Point2D p3(m_startPoint.x, m_startPoint.y + height/3);
    Point2D p4(m_startPoint.x + width * 2 / 3, m_endPoint.y);

    m_points.push_back(p0);
    m_points.push_back(p1);
    m_points.push_back(p2);
    m_points.push_back(p3);
    m_points.push_back(p4);
    m_points.push_back(p0);
}

StarShape::~StarShape(void)
{
}

Point2D 
StarShape::startPoint()
{
	return m_startPoint;
}

Point2D 
StarShape::endPoint()
{
	return m_endPoint;
}
