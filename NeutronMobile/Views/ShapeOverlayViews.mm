//
//  ShapeOverlayViews.m
//  NeutronMobile
//
//  Created by fengka on 7/22/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#import "ShapeOverlayViews.h"

@implementation ShapeOverlayView
@synthesize mx0 = _mx0, my0 = _my0, mx1 = _mx1, my1 = _my1;


- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end



@implementation LineOverlayView

- (void)drawRect:(CGRect)rect
{
    // Drawing code
    CGContextRef context = UIGraphicsGetCurrentContext();
    
    // draw line
    // white
    CGColorRef colorRef = [[UIColor whiteColor] CGColor];
    CGContextSetStrokeColorWithColor(context, colorRef);
	CGContextSetLineWidth(context, 1.0);
    CGContextMoveToPoint(context, self.mx0, self.my0);
    CGContextAddLineToPoint(context, self.mx1, self.my1);
    CGContextStrokePath(context);
    
    // dashed black
    CGContextBeginPath(context);
    CGContextSetStrokeColorWithColor(context, [[UIColor blackColor] CGColor]);
    CGFloat dash = 10.0;
    CGContextSetLineDash(context, 0.0, &dash, 1);
    CGContextMoveToPoint(context, self.mx0, self.my0);
    CGContextAddLineToPoint(context, self.mx1, self.my1);
    CGContextStrokePath(context);
}

@end

@implementation RectangleOverlayView

- (void)drawRect:(CGRect)rect
{
    // Drawing code
    CGContextRef context = UIGraphicsGetCurrentContext();
    
    // draw rectangle
    // white
    CGColorRef colorRef = [[UIColor whiteColor] CGColor];
    CGContextSetStrokeColorWithColor(context, colorRef);
	CGContextSetLineWidth(context, 1.0);
    CGRect bounds = CGRectMake(MIN(self.mx0, self.mx1), MIN(self.my0, self.my1), fabs(self.mx0 - self.mx1), fabs(self.my0 - self.my1));
	CGContextStrokeRect(context, bounds);
    
    // dashed black
    colorRef = [[UIColor blackColor] CGColor];
    CGContextSetStrokeColorWithColor(context, colorRef);
    CGFloat dash = 10.0;
    CGContextSetLineDash(context, 0.0, &dash, 1);
	CGContextStrokeRect(context, bounds);
    
}


@end

@implementation OvalOverlayView

- (void)drawRect:(CGRect)rect
{
    // Drawing code
    CGContextRef context = UIGraphicsGetCurrentContext();
    
    // draw oval
    // white
    CGColorRef colorRef = [[UIColor whiteColor] CGColor];
    CGContextSetStrokeColorWithColor(context, colorRef);
	CGContextSetLineWidth(context, 1.0);
    CGRect bounds = CGRectMake(MIN(self.mx0, self.mx1), MIN(self.my0, self.my1), fabs(self.mx0-self.mx1), fabs(self.my0-self.my1));
	CGContextStrokeEllipseInRect(context, bounds);
    
    // dashed black
    colorRef = [[UIColor blackColor] CGColor];
    CGContextSetStrokeColorWithColor(context, colorRef);
    CGFloat dash = 10.0;
    CGContextSetLineDash(context, 0.0, &dash, 1);
	CGContextStrokeEllipseInRect(context, bounds);
}

@end
