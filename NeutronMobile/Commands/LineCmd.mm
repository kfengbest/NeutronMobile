//
//  LineCmd.m
//  NeutronMobile
//
//  Created by fengka on 8/3/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#import "LineCmd.h"

// Line Cmd
@implementation LineCmd

-(ShapeOverlayView*) makeIfNeeded
{
    if (self.mShapePreview == nil) {
        self.mShapePreview = [LineOverlayView alloc];
    }
    
    return self.mShapePreview;
}

- (void)touchesEnded:(NSSet *)touches
{
    Point2D p0(self.mShapePreview.mx0, self.mShapePreview.my0);
    Point2D p1(self.mShapePreview.mx1, self.mShapePreview.my1);
    
    self.mpSketch = new Line2D(self.mpDocument, p0, p1);
    self.mpSketch->lineThickness( self.mpDocument->m_thickness);
    self.mpSketch->lineColor(self.mpDocument->m_color);
    self.mpDocument->addEntity(self.mpSketch);
    
    [super touchesEnded:touches];
    [self.view setNeedsDisplay];
}
@end