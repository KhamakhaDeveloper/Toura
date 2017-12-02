#import <Foundation/Foundation.h>
#import <KudanAR/ARNode.h>

@class ARVector3;

/**
 An ARBillboardNode is a subclass of ARNode that changes its orientation to ensure it always maintains its given forward vector direction relative to the camera.
 This is useful for showing content that rotates and follows the device as it moves around the scene and is especially useful for videos or other 2D content, as it will always be visible.
 
 ARBillboardNodes can be used in conjunction with ArbiTrack to make 3D models or videos turn to follow the camera, or with the Image Tracker to have objects face the camera independently of the marker's orientation.
 */
@interface ARBillboardNode : ARNode

/**
 The vector that should be aimed at the camera. For example, a vector of (0, 1, 0) would cause the Y-axis of the node's local space to point towards the camera.
 */
@property (nonatomic) ARVector3 *forward;

/**
 Determines whether rotation around the X axis is locked. Default is NO.
 **/
@property (nonatomic) BOOL lockX;

/**
 Determines whether rotation around the Y axis is locked. Default is NO.
 **/
@property (nonatomic) BOOL lockY;

/**
 Determines whether rotation around the Z axis is locked. Default is NO.
 **/
@property (nonatomic) BOOL lockZ;

@end
