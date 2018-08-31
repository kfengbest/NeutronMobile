//
//  ShapesCmd.m
//  NeutronMobile
//
//  Created by fengka on 7/23/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#import "ShapeCmds.h"

@implementation ShapeCmd
@synthesize view = _view;
@synthesize mShapePreview = _mShapePreview;
@synthesize mpSketch = _mpSketch;
@synthesize mIsDrawing = _mIsDrawing;

-(void) initWithView : (UIView*)theView
{
    self.view = theView;
}

- (void)touchesBegan:(NSSet *)touches
{
    self.mShapePreview.hidden = NO;
    self.mIsDrawing = YES;
    
    for (UITouch *touch in touches) {
        
        CGPoint loc = [touch locationInView : self.view];
        self.mShapePreview.mx0 = loc.x;
        self.mShapePreview.my0 = loc.y;
        
    }
}

- (void)touchesMoved:(NSSet *)touches
{
    for (UITouch *touch in touches) {
        
        CGPoint loc = [touch locationInView : self.view];
        self.mShapePreview.mx1 = loc.x;
        self.mShapePreview.my1 = loc.y;
        [self.mShapePreview setNeedsDisplay];
    }
}

- (void)touchesEnded:(NSSet *)touches
{
    self.mIsDrawing = NO;
    
    self.mShapePreview.mx0 = 0.0;
    self.mShapePreview.my0 = 0.0;
    self.mShapePreview.mx1 = 0.0;
    self.mShapePreview.my1 = 0.0;
    [self.mShapePreview setNeedsDisplay];
    
    self.mShapePreview.hidden = YES;
    
}

- (void)touchesCancelled:(NSSet *)touches
{
}

- (void)begin
{
    CGRect rectFrame = [self.view bounds];
    self.mShapePreview = [self makeIfNeeded];
    [self.mShapePreview initWithFrame:rectFrame];
    self.mShapePreview.opaque = NO;
    self.mShapePreview.userInteractionEnabled = NO;
    self.mShapePreview.hidden = YES;
    [self.view addSubview:self.mShapePreview];
}

- (void)end
{
    [self.mShapePreview removeFromSuperview];
}

-(ShapeOverlayView*) makeIfNeeded
{
    return nil;
}

@end



// Oval Cmd
@implementation OvalCmd

-(ShapeOverlayView*) makeIfNeeded
{
    if (self.mShapePreview == nil) {
        self.mShapePreview = [OvalOverlayView alloc];
    }
    
    return self.mShapePreview;
}
@end
