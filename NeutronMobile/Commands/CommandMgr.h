//
//  CommandMgr.h
//  NeutronMobile
//
//  Created by fengka on 7/23/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Command.h"
#import "ShapeCmds.h"
#import "../Server/Geometry2D/Document.h"
#import <map.h>
#import <string>

@interface CommandMgr : NSObject
@property(nonatomic, readwrite) Document* mpDocument;
@property(nonatomic, readwrite) Command* activeCmd;
@property(nonatomic, strong) NSDictionary* mCommands;

- (id)initWithView : (UIView*)theView andDocument:(Document*)theDoc;

- (void)touchesBegan:(NSSet *)touches;
- (void)touchesMoved:(NSSet *)touches;
- (void)touchesEnded:(NSSet *)touches;
- (void)touchesCancelled:(NSSet *)touches;

- (void)registerCmd:(Command*)pCmd;
- (void)execute:(NSString*)cmdName;

@end
