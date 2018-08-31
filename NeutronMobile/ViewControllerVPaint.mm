//
//  ViewControllerVPaint.m
//  NeutronMobile
//
//  Created by fengka on 7/21/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#import "ViewControllerVPaint.h"

#import "Views/ToolbarView.h"
#import "Commands/CommandMgr.h"
#import "Views/ToolbarItem.h"
#import "Graphics2dView.h"
#import "TouchEventsTranslator.h"

@interface ViewControllerVPaint ()
{
    TouchEventTranslator* mEventTranslator;
}

@property (nonatomic, strong) CommandMgr* mCmdMgr;
@property (nonatomic, strong) Graphics2dView* mGrxView;
@property (nonatomic, strong) IBOutlet ToolbarView* mToolbar;

@end

@implementation ViewControllerVPaint
@synthesize mGrxView = _mGrxView;
@synthesize mCmdMgr = _mCmdMgr;
@synthesize mToolbar = _mToolbar;
@synthesize mpDocument = _mpDocument;

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    // Init Document;
    self.mpDocument = new Document();
    
    // GraphicsView.
    self.mGrxView = (Graphics2dView*)self.view;
    self.mGrxView.mpDocument = self.mpDocument;
    
    // Command Manager.
    self.mCmdMgr = [[CommandMgr alloc] initWithView:self.view andDocument:self.mpDocument];
    
    mEventTranslator = new TouchEventTranslator(self.view);
    
    // Toolbar
//    CGRect frame = CGRectMake(0, 0, 200, 48);
//	frame.origin.x = round((self.view.frame.size.width - frame.size.width) / 2.0);
//	frame.origin.y = 16;
//    self.mToolbar = [[ToolbarView alloc] initWithFrame:frame];
//	self.mToolbar.frame = frame;
//    self.mToolbar.alpha = 0.5;	
//	[self.view addSubview:self.mToolbar];

    
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    
    delete mEventTranslator;
  
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    
    [self.mCmdMgr touchesBegan:touches];
    
    mEventTranslator->touchBegin(touches, event);
    
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    
    [self.mCmdMgr touchesMoved:touches];
    mEventTranslator->touchesMoved(touches, event);

}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {

    [self.mCmdMgr touchesEnded:touches];
    mEventTranslator->touchesEnded(touches, event);
    
    [self.view setNeedsDisplay];

}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
    [self.mCmdMgr touchesCancelled:touches];
    mEventTranslator->touchesCancelled(touches, event);
}

- (IBAction)btnClicked:(id)sender {
    UIButton* btn = (UIButton*)sender;
    NSString* str = btn.titleLabel.text;
    [self.mCmdMgr execute:str];
}

- (IBAction)btnColor:(id)sender {
    CGColorRef colorRef = [[UIColor redColor] CGColor];
    UIButton* btn = (UIButton*)sender;
    NSString* str = btn.titleLabel.text;
    if ([str compare: @"Red"] == YES) {
        colorRef = [[UIColor redColor] CGColor];
    }
    else if([str compare: @"Green"] == YES)
    {
        colorRef = [[UIColor greenColor] CGColor];
    }
    else if([str compare: @"Yellow"] == YES)
    {
        colorRef = [[UIColor yellowColor] CGColor];
    }
    else if([str compare: @"Blue"] == YES)
    {
        colorRef = [[UIColor blueColor] CGColor];
    }
    
    const CGFloat* cs = CGColorGetComponents(colorRef);
    Ns::Core::Color c(cs[0],cs[1], cs[2], cs[3]);
    self.mpDocument->m_color = c;


}

- (IBAction)thicknessChanged:(id)sender {
    UISlider* slider = (UISlider*)sender;
    
    self.mpDocument->m_thickness =slider.value;
}
@end
