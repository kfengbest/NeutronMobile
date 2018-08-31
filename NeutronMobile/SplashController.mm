///////////////////////
//
// SplashController.m
//
// Controller around the splashView to get orientation callback
//
#import "SplashController.h"
#import <QuartzCore/QuartzCore.h>
 
@implementation SplashController

- (void)loadView 
{
	CGRect rect;
	if(UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone)
		rect = CGRectMake(0,0,320,480);
	else 
		rect = CGRectMake(0,0,768,1024);

	self.view = [[UIView alloc] initWithFrame:rect];
	self.view.backgroundColor = [UIColor blackColor];	
	
	if(UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone)
	{
		image = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"iPhone.png"]];
		[self.view addSubview:image];
	}
	else 
		image = NULL;
}

- (void) viewDidAppear:(BOOL)animated
{
	[super viewDidAppear:animated];
	
	[self performSelector:@selector(dismissSplash) withObject:self afterDelay:0];
}


- (void)setOrientation:(UIInterfaceOrientation)interfaceOrientation
{
	if(UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone)
		return;
	
	if(image)
	{
		[image removeFromSuperview];
	}
	if(interfaceOrientation == UIInterfaceOrientationPortrait || interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown)
		image = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"Neutron_Ipad_Portait.png"]];
	else 
		image = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"Neutron_Ipad_Landscape.png"]];
	
//	UIView *rootview = [[SimpleAppDelegate Get].window.subviews objectAtIndex:0];
	
//	CGAffineTransform R = rootview.transform;
//	self.view.transform = R;
//	self.view.frame = rootview.frame;

	[self.view addSubview:image];
}

- (void)dismissSplash 
{	
//	[[SimpleAppDelegate Get] prepareEndSplash];
    
	CABasicAnimation *animSplash = [CABasicAnimation animationWithKeyPath:@"opacity"];
	animSplash.duration = 1;
	animSplash.removedOnCompletion = NO;
	animSplash.fillMode = kCAFillModeForwards;
	animSplash.fromValue=[NSNumber numberWithFloat:1.0];
	animSplash.toValue = [NSNumber numberWithFloat:0];
	animSplash.delegate = self;
	[self.view.layer addAnimation:animSplash forKey:@"animateOpacity"];
}

- (void)animationDidStop:(CAAnimation *)theAnimation finished:(BOOL)flag 
{	
	[image removeFromSuperview];

//	[[SimpleAppDelegate Get] endSplash];
}

- (void)didReceiveMemoryWarning 
{
    [super didReceiveMemoryWarning];
}

- (void)viewDidUnload 
{
    [super viewDidUnload];
}




@end
