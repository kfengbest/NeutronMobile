//
//  Command.h
//  NeutronMobile
//
//  Created by fengka on 7/23/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "../Server/Geometry2D/Document.h"
#import <string>

@interface Command : NSObject
@property(nonatomic, readwrite) Document* mpDocument;
@property (nonatomic, readwrite) BOOL mIsActive;
@property (nonatomic, readwrite) NSString* mCmdId;

- (void)touchesBegan:(NSSet *)touches;
- (void)touchesMoved:(NSSet *)touches;
- (void)touchesEnded:(NSSet *)touches;
- (void)touchesCancelled:(NSSet *)touches;
- (void)begin;
- (void)end;

@end