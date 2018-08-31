#pragma once

//#include "Geometry2D.h"

class Point2D 
{
public:
	Point2D();
    Point2D(int _x, int _y);
	virtual ~Point2D(void);

public:
	int x;
	int y;
};

