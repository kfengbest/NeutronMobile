///////////////////////
//
// SplashController.h
//
// Controller around the splashView to get orientation callback
//
#import <UIKit/UIKit.h>
 

@interface SplashController : UIViewController 
{
	UIImageView *image;
}

- (void)setOrientation:(UIInterfaceOrientation)orientation;

@end
