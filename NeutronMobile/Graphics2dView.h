//
//  Graphics2dView.h
//  NeutronMobile
//
//  Created by fengka on 7/21/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Server/Geometry2D/Document.h"

@interface Graphics2dView : UIView
@property(nonatomic, readwrite) Document* mpDocument;
@end


