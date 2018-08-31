//
//  SketchCmd.m
//  NeutronMobile
//
//  Created by fengka on 8/3/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#import "SketchCmd.h"


// Sketch Cmd
@implementation SketchCmd

- (void)touchesBegan:(NSSet *)touches
{
    self.mIsDrawing = YES;
    self.mpSketch = new Sketch(self.mpDocument);
    self.mpSketch->lineThickness( self.mpDocument->m_thickness);
    self.mpSketch->lineColor(self.mpDocument->m_color);
    self.mpDocument->addEntity(self.mpSketch);
    
    for (UITouch *touch in touches) {
        
        CGPoint loc = [touch locationInView : self.view];
        Sketch* pSketch = (Sketch*)self.mpSketch;
        pSketch->addPoint2D(Point2D(loc.x,loc.y));
        
    }
}

- (void)touchesMoved:(NSSet *)touches
{
    for (UITouch *touch in touches) {
        
        CGPoint loc = [touch locationInView : self.view];
        Sketch* pSketch = (Sketch*)self.mpSketch;
        pSketch->addPoint2D(Point2D(loc.x,loc.y));
        [self.view setNeedsDisplay];
    }
}

- (void)touchesEnded:(NSSet *)touches
{
    self.mIsDrawing = NO;
    
    for (UITouch *touch in touches) {
        
        CGPoint loc = [touch locationInView : self.view];
        Sketch* pSketch = (Sketch*)self.mpSketch;
        pSketch->addPoint2D(Point2D(loc.x,loc.y));
        [self.view setNeedsDisplay];
    }
    
}

@end