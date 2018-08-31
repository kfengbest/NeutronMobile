//
//  Graphics2dView.m
//  NeutronMobile
//
//  Created by fengka on 7/21/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#import "Graphics2dView.h"

#import "Server/Geometry2D/Geometry2D.h"
#import "Server/Types/Color.h"

@interface Graphics2dView ()
@property(nonatomic, readwrite, assign) float diameter;
@property(nonatomic, strong) UIColor *color;

@end

@implementation Graphics2dView
@synthesize mpDocument = _mpDocument;


- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        
    }
    return self;
}

- (void)drawRect:(CGRect)rect
{
 /* //Brush outline view
    float diameter = 1.6;
    
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGRect bounds = [self bounds];
    float inset = bounds.size.width - diameter;
    if (inset < 0.0) {
        inset = 0.0;
    }
    bounds = CGRectInset(bounds, inset / 2.0, inset / 2.0);
    
    // draw current color
    CGContextBeginPath(context);
    CGColorRef colorRef = UIColor.redColor;
    CGContextSetFillColorWithColor(context, colorRef);
	CGContextFillEllipseInRect(context, bounds);
    
    // draw circle outline: white
    CGContextBeginPath(context);
    
    colorRef = [[UIColor whiteColor] CGColor];
    CGContextSetStrokeColorWithColor(context, colorRef);
	CGContextSetLineWidth(context, 1.0);
	CGContextStrokeEllipseInRect(context, bounds);
    
    // draw circle outline: black
    bounds = CGRectInset(bounds, -1.0, -1.0);
    CGContextBeginPath(context);
    
    colorRef = [[UIColor blackColor] CGColor];
    CGContextSetStrokeColorWithColor(context, colorRef);
	CGContextSetLineWidth(context, 1.0);
	CGContextStrokeEllipseInRect(context, bounds);
*/
    

/*
    // Drawing code
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGRect bounds = [self bounds];
    bounds = CGRectInset(bounds, 6.0, 6.0);
    
    // draw cross hair
    #define kInnerGap 10.0
    
    CGFloat xC = self.bounds.size.width / 2.0;
    CGFloat yC = self.bounds.size.height / 2.0;
    
    CGContextBeginPath(context);
    CGContextSetStrokeColorWithColor(context, [[UIColor blackColor] CGColor]);
	CGContextSetLineWidth(context, 1.0);
    CGContextMoveToPoint(context, bounds.origin.x, yC);
    CGContextAddLineToPoint(context, xC - kInnerGap, yC);
    CGContextMoveToPoint(context, xC + kInnerGap, yC);
    CGContextAddLineToPoint(context, bounds.size.width + bounds.origin.x, yC);
    
    CGContextMoveToPoint(context, xC,  bounds.origin.y);
    CGContextAddLineToPoint(context, xC,  yC - kInnerGap);
    CGContextMoveToPoint(context, xC, yC + kInnerGap);
    CGContextAddLineToPoint(context, xC, bounds.size.height + bounds.origin.y);
    
    CGContextStrokePath(context);
 
    */
 
    
    CGContextRef context = UIGraphicsGetCurrentContext();
    
    if (self.mpDocument != NULL) {
        EntityVec::const_iterator it = self.mpDocument->entities().begin();
        EntityVec::const_iterator ite = self.mpDocument->entities().end();
        for (; it != ite ; ++it) {
            Geometry2D* pGeo = dynamic_cast<Geometry2D*>(*it);
            if (pGeo) {
                float weight = pGeo->lineThickness();
                Ns::Core::Color color = pGeo->lineColor();
                
                std::vector<Point2D> points = pGeo->pointsStrip();
                
                std::vector<Point2D>::iterator it = points.begin();
                std::vector<Point2D>::iterator ite = points.end();
                
                CGFloat components[4] = {color.red(),color.green(),color.blue(),color.alpha()};
                CGColorRef newRGB = CGColorCreate(CGColorSpaceCreateDeviceRGB(), components);
                CGContextSetStrokeColorWithColor(context, newRGB);
                CGContextSetLineWidth(context, weight);
                if (it != ite) {
                    CGContextMoveToPoint(context, it->x, it->y);
                    it++;
                }
                
                while (it != ite) {
                    CGContextAddLineToPoint(context, it->x, it->y);
                    it++;
                }
                
                CGContextStrokePath(context);
            }
        }
        
    }
    
}


@end
