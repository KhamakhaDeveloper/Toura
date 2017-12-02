#import <Foundation/Foundation.h>
#import <KudanAR/ARNode.h>

@class ARViewPort;

/**
 An ARCamera is a subclass of ARNode that represents the root node of the scenegraph, at the top of the hierarchy.
 It is attached to an ARViewPort and controls the projection.
 */
@interface ARCamera : ARNode

/**
 The projection matrix representing the camera intrinsics.
 A computer monitor is a 2D surface. A 3D scene rendered must therefore be projected onto the computer screen as a 2D image. 
 The projection matrix is used for this projection transformation. First, it transforms all vertex data from eye space to clip space. 
 The resulting coordinates are then transformed from camera space to screen space.
 */
@property (nonatomic) ARMatrix4 *projectionMatrix;

/**
 The distance to the far clipping plane of the camera frustum. Any objects further than this distance will not be rendered.
 */
@property (nonatomic) CGPoint frustumPlaneDistance;

/**
 The point where the forward axis intersects with the image plane. This point is also referred to as the image center.
 **/
@property (nonatomic) CGPoint principlePoint;

/**
 The cameras horizontal and verticle field of view. The x represents the horizontal fov and the y represents the vertical fov. 
 The field of view is the extent of the observable scene that is seen by the camera at any given moment.
 A larger field of view alows more of the scene to be seen at a time.
 **/
@property (nonatomic) CGPoint fov;

/**
 The viewport this camera is attached to, or nil if detached.
 */
@property (nonatomic, weak) ARViewPort *viewPort;

/**
 Reference to a default static camera. Will be created if it hasn't already.
 
 Example of use:
 @code
 ARCamera *camera = [ARCamera defaultCamera];
 @endcode
 */
+ (ARCamera *)defaultCamera;

@end
