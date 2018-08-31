//
//  ViewController3DGrxViewController.m
//  NeutronMobile
//
//  Created by fengka on 8/26/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#import "ViewController3DGrx.h"



@interface ViewController3DGrx ()
{

}

@end

@implementation ViewController3DGrx

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    [self.view initWithFrame:screenBounds];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

@end
