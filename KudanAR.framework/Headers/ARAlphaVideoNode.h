#import <Foundation/Foundation.h>
#import <KudanAR/ARMeshNode.h>

@class ARVideoTexture;

/**
 An ARAlphaVideoNode is a subclass of ARMeshNode that renders a supplied alpha video file on a flat mesh in the scene.
 It can be initialised using either a video file bundled in your app or with an ARVideoTexture containing an Alpha Video. 
 */
@interface ARAlphaVideoNode : ARMeshNode

/**
 The ARVideoTexture used by this Alpha Video Node. This is the video that will be played when then node becomes active and visible.
 */
@property (nonatomic) ARVideoTexture *videoTexture;

/**
 Initialises an ARAlphaVideoNode using an ARVideoTexture.
 
 Example of use:
 @code
 ARVideoTexture *videoTexture = [[ARVideoTexture alloc] initWithVideoFile:@"video.mp4" audioFile:"audio.aac"];
 ARAlphaVideoNode *alphaVideoNode = [[ARAlphaVideoNode alloc] initWithVideoTexture: videoTexture];
 @endcode
 
 @param videoTexture The ARVideoTexture to initialise the object with.
 */
- (instancetype)initWithVideoTexture:(ARVideoTexture *)videoTexture NS_DESIGNATED_INITIALIZER;

/**
 Initialises an ARAlphaVideoNode using a video file at the specified path.
 
 Example of use:
 @code
 ARAlphaVideoNode *alphaVideoNode = [[ARAlphaVideoNode alloc] initWithBundledFile:“example.mp4”];
 @endcode
 
 @param file The file in the app bundle to initialise with. The file path is relative to the app bundle and includes the file extension.
 */
- (instancetype)initWithBundledFile:(NSString *)file;

@end
