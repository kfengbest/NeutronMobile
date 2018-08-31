//
//  ShapeOverlayViews.h
//  NeutronMobile
//
//  Created by fengka on 7/22/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ShapeOverlayView : UIView

@property(nonatomic, readwrite) CGFloat mx0;
@property(nonatomic, readwrite) CGFloat my0;
@property(nonatomic, readwrite) CGFloat mx1;
@property(nonatomic, readwrite) CGFloat my1;

@end

// Line
@interface LineOverlayView : ShapeOverlayView

@end

// Rectangle
@interface RectangleOverlayView : ShapeOverlayView

@end

// Oval
@interface OvalOverlayView : ShapeOverlayView
{
}
@end

