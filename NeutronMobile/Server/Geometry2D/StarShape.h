//
//  StarShape.h
//  NeutronMobile
//
//  Created by fengka on 8/3/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#ifndef __NeutronMobile__StarShape__
#define __NeutronMobile__StarShape__


#include "Geometry2D.h"
#include "Point2D.h"

class StarShape : public Geometry2D
{
public:
	StarShape(Entity* parent,const Point2D& startPoint, const Point2D& endPoint);
	virtual ~StarShape(void);
    
	Point2D startPoint();
	Point2D endPoint();
    
private:
	Point2D m_startPoint;
	Point2D m_endPoint;
};


#endif /* defined(__NeutronMobile__StarShape__) */
