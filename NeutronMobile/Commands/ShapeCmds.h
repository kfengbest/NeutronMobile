//
//  ShapesCmd.h
//  NeutronMobile
//
//  Created by fengka on 7/23/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Command.h"
#import "../Views/ShapeOverlayViews.h"

#import "../Server/Geometry2D/Geometry2D.h"
#import "../Server/Geometry2D/Line2D.h"
#import "../Server/Geometry2D/Rectangle2D.h"
#import "../Server/Geometry2D/Oval2D.h"
#import "../Server/Geometry2D/Sketch.h"

// ShapeCmd
@interface ShapeCmd : Command

@property (nonatomic, strong) ShapeOverlayView* mShapePreview;
@property (nonatomic, strong) UIView* view;
@property (nonatomic, readwrite) Geometry2D* mpSketch;
@property (nonatomic, readwrite) BOOL mIsDrawing;

-(ShapeOverlayView*) makeIfNeeded;
-(void) initWithView:(UIView*) theView;

@end





// OvalCmd
@interface OvalCmd : ShapeCmd

-(ShapeOverlayView*) makeIfNeeded;

@end

