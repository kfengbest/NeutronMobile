//
//  StarCommand.m
//  NeutronMobile
//
//  Created by fengka on 8/3/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#import "StarCommand.h"
#import "../Views/ShapeOverlayViews.h"
#import "../Server/Geometry2D/StarShape.h"

@implementation StarCommand


-(ShapeOverlayView*) makeIfNeeded
{
    if (self.mShapePreview == nil) {
        self.mShapePreview = [RectangleOverlayView alloc];
    }
    
    return self.mShapePreview;
}

- (void)touchesEnded:(NSSet *)touches
{
    
    Point2D p0(self.mShapePreview.mx0, self.mShapePreview.my0);
    Point2D p1(self.mShapePreview.mx1, self.mShapePreview.my1);
    
    self.mpSketch = new StarShape(self.mpDocument, p0, p1);
    self.mpSketch->lineThickness( self.mpDocument->m_thickness);
    self.mpSketch->lineColor(self.mpDocument->m_color);
    self.mpDocument->addEntity(self.mpSketch);
    
    [super touchesEnded:touches];
    [self.view setNeedsDisplay];
}


@end
