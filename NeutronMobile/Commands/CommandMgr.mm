//
//  CommandMgr.m
//  NeutronMobile
//
//  Created by fengka on 7/23/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#import "CommandMgr.h"
#import "StarCommand.h"
#import "LineCmd.h"
#import "RectangleCmd.h"
#import "SketchCmd.h"
#import "../UI/Base/Commands/NuCommand.h"

@interface CommandMgr ()
{
    Nu::Command* m_pActiveCmd;
}

@property (nonatomic, strong) UIView* mView;
@end


@implementation CommandMgr
@synthesize mView = _mView;
@synthesize activeCmd = _activeCmd;
@synthesize mpDocument = _mpDocument;
@synthesize mCommands = _mCommands;

- (id)initWithView : (UIView*)theView andDocument:(Document*)theDoc
{
    self = [super init];
    if (self) {
        self.mView = theView;
        self.mpDocument = theDoc;
        
        //Remove it...
        SketchCmd* pCmd1 = [SketchCmd alloc];
        [pCmd1 initWithView : self.mView];
        pCmd1.mpDocument = self.mpDocument;
        pCmd1.mCmdId = @"Sketch";
        
        
        LineCmd* pCmd2 = [LineCmd alloc];
        [pCmd2 initWithView : self.mView];
        pCmd2.mpDocument = self.mpDocument;
        pCmd2.mCmdId = @"Line";
        
        
        RectangleCmd* pCmd3 = [RectangleCmd alloc];
        [pCmd3 initWithView : self.mView];
        pCmd3.mpDocument = self.mpDocument;
        pCmd3.mCmdId = @"Rectangle";
    
        StarCommand* pCmd4 = [StarCommand alloc];
        [pCmd4 initWithView : self.mView];
        pCmd4.mpDocument = self.mpDocument;
        pCmd4.mCmdId = @"Star";
    
        self.mCommands = [NSDictionary dictionaryWithObjectsAndKeys:pCmd1,pCmd1.mCmdId,
                                                                    pCmd2, pCmd2.mCmdId,
                          pCmd3, pCmd3.mCmdId,pCmd4, pCmd4.mCmdId, nil];
        
                              
        self.activeCmd = pCmd1;
        [self.activeCmd begin];
        
        m_pActiveCmd = new Nu::LineCommand(self.mpDocument);
        
    }
    return self;
}

- (void)touchesBegan:(NSSet *)touches
{
    [self.activeCmd touchesBegan:touches];
    
}

- (void)touchesMoved:(NSSet *)touches
{
    [self.activeCmd touchesMoved:touches];
}

- (void)touchesEnded:(NSSet *)touches
{
    [self.activeCmd touchesEnded:touches];
}

- (void)touchesCancelled:(NSSet *)touches
{
    [self.activeCmd touchesCancelled:touches];
}

- (void)registerCmd:(Command*)pCmd
{
}

- (void)execute:(NSString*)cmdName
{
    if (cmdName == self.activeCmd.mCmdId) {
        return;
    }
    
    Command* pCmd = nil;
    pCmd = [self.mCommands objectForKey: cmdName];
    if (pCmd != nil) {
        [self.activeCmd end];
        self.activeCmd = pCmd;
        [self.activeCmd begin];
    }
}

@end
