#pragma once
#include <vector>
#include "Point2D.h"

class INodeSource
{
public:
	virtual void draw() = 0;
    virtual void realizeGeometry(std::vector<Point2D>& pointList){};
};

