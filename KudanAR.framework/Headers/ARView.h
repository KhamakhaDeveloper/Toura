#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

@class ARRenderTargetMain;

/**
 An ARView encapsulates AR activities.
 It is a custom subclass of UIView that specifically handles the rendering of AR content and any interaction with it.
 It uses an assocaited render target to draw more complex content that an ordinary UIView is not capable of displaying.
 */
@interface ARView : UIView

/**
 The main render target associated with this view.
 */
@property (nonatomic) ARRenderTargetMain *renderTarget;

/**
 Take a screenshot of the current render target. To use this method, it is recommended to use it via the ARCameraView in your ARCameraViewController. 
 
 Example of use:
 @code
 UIImage image = [self.cameraView screenshot];
 @endcode
 
 @return A UIImage containing the current framebuffer of the main render target. Resolution will match that of the renderTarget.
 */
- (UIImage *)screenshot;

/**
 An abstract method that can be implemented in subclasses, this provides a way to run code when the view's orientation changes.
 */
- (void)didRotateToInterfaceOrientation:(UIInterfaceOrientation)orientation;

/**
 Initialise a view with the given frame at the given interface orientation.
 
 Example of use:
 @code
 CGRect frame = CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height);
 ARView *view = [[ARView alloc] initWithFrame:frame interfaceOrientation:[[UIApplication sharedApplication] statusBarOrientation]];
 @endcode
 
 @param frame The frame rectangle for the view.
 @param interfaceOrientation The orientation at the time of creation. ARView needs to keep track of this to function properly.
 */
- (instancetype)initWithFrame:(CGRect)frame interfaceOrientation:(UIInterfaceOrientation)orientation;

@end
