//
//  ViewController.h
//  NeutronMobile
//
//  Created by fengka on 7/21/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Server/Geometry2D/Document.h"


@interface ViewControllerVPaint : UIViewController
@property(nonatomic, readwrite) Document* mpDocument;
- (IBAction)btnClicked:(id)sender;
- (IBAction)btnColor:(id)sender;
- (IBAction)thicknessChanged:(id)sender;

@end
