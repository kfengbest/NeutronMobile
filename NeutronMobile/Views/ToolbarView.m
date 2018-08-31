/*
     File: HoverView.m
 Abstract: This view contains the UI or controls that hover or appear over the main view.
  Version: 1.1
 
 */

#import "ToolbarView.h"
#import "ToolbarItem.h"

@implementation ToolbarView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        
//       ToolbarItem* item = [[ToolbarItem alloc] init];
//        [self addSubview: item];
        
        UIButton *sampleButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        [sampleButton setFrame:CGRectMake(self.bounds.origin.x, self.bounds.origin.y, 32, 32)];
        [sampleButton setBackgroundImage:[[UIImage imageNamed:@"Left.png"]stretchableImageWithLeftCapWidth:0.0 topCapHeight:0.0] forState:UIControlStateNormal];
        [self addSubview:sampleButton];
        
    }
    return self;
}

- (void)fillRoundedRect:(CGRect)rect inContext:(CGContextRef)context
{
    float radius = 5.0f;
    
    CGContextBeginPath(context);
	CGContextSetGrayFillColor(context, 0.8, 0.5);
	CGContextMoveToPoint(context, CGRectGetMinX(rect) + radius, CGRectGetMinY(rect));
    CGContextAddArc(context, CGRectGetMaxX(rect) - radius, CGRectGetMinY(rect) + radius, radius, 3 * M_PI / 2, 0, 0);
    CGContextAddArc(context, CGRectGetMaxX(rect) - radius, CGRectGetMaxY(rect) - radius, radius, 0, M_PI / 2, 0);
    CGContextAddArc(context, CGRectGetMinX(rect) + radius, CGRectGetMaxY(rect) - radius, radius, M_PI / 2, M_PI, 0);
    CGContextAddArc(context, CGRectGetMinX(rect) + radius, CGRectGetMinY(rect) + radius, radius, M_PI, 3 * M_PI / 2, 0);
	
    CGContextClosePath(context);
    CGContextFillPath(context);
}

- (void)drawRect:(CGRect)rect
{
//	// draw a box with rounded corners to fill the view -
//	CGRect boxRect = self.bounds;
//    CGContextRef ctxt = UIGraphicsGetCurrentContext();	
//	boxRect = CGRectInset(boxRect, 1.0f, 1.0f);
//    [self fillRoundedRect:boxRect inContext:ctxt];
}

@end
