#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

/**
 The ARCameraStreamEvents are a set of events that fire when the ARCamera receives a new frame.
 */
@protocol ARCameraStreamEvent <NSObject>

@optional
/**
 Event fired when the camera receives a new frame.
 
 @param data Contains the camera image data buffer in the format defined by cameraDataFormat.
 @param timeStamp The time the frame was captured.
 */
- (void)didReceiveNewFrame:(NSData *)data timeStamp:(NSTimeInterval)timeStamp;

/**
 Event fired when the camera received a new colour frame.
 
 @param lumaData Contains the camera image data buffer containing the luma component channel.
 @param chromaData Contains the camera image data buffer containing the blue-difference and red-difference chroma component interleaved channels in a biplanar buffer.
 @param timeStamp The time the frame was captured.
 */
- (void)didReceiveNewFrameWithLuma:(NSData *)lumaData chroma:(NSData *)chromaData timeStamp:(NSTimeInterval)timeStamp;

@end

@class ARTexture;
@class ARColour;

/**
 The ARCameraStream is a singleton manager class for handling the camera stream.
 It can be used to gain access to the background camera texture or to provide camera events.
 */
@interface ARCameraStream : NSObject <AVCaptureVideoDataOutputSampleBufferDelegate>

/**
 The width of the camera image, in pixels.
 */
@property (nonatomic) float width;

/**
 The height of the camera image, in pixels.
 */
@property (nonatomic) float height;

/**
 The thickness of padding around the camera image, in pixels. This effectively creates a border around the camera stream.
 */
@property (nonatomic) float padding;

/**
 The full-colour camera texture, including all 3 channels.
 **/
@property (nonatomic) ARTexture *cameraTexture;

/**
 Camera luma texture. This texture only includes the Y(Luma) colour channel, meaning it will appear as a black-and-white image.
 **/
@property (nonatomic) ARTexture *cameraTextureY;

/**
 Camera chroma texture. This texture includes both the U and V channels, which contain the colour information of the image.
 The is not a full colour texture, as the U and V channels are colour differences that depend on the luminance values of the Y channel to be correct.
 **/
@property (nonatomic) ARTexture *cameraTextureUV;

/**
 Array containing all ARCameraStreamEvent delegates that have been added to this singleton.
 */
@property (nonatomic) NSArray *delegates;

/**
 Gets the instance of the camera stream singleton.
 
 Example of use:
 @code
 ARCameraStream *cameraStream = [ARCameraStream getInstance];
 @endcode
 
 @return The singleton instance.
 */
+ (ARCameraStream *)getInstance;

/**
 Returns the average colour of an image expressed as a byte array. The image will be downsized before computation of the average. Smaller images will compute faster at the expense of accuracy. It is recommended to reduce image size as much as possible.
 
 Example of use:
 @code
 ARCameraStream *cameraStream = [ARCameraStream getInstance];
 ARColour *averageColour = [cameraStream averageColourFromData:cameraStream.cameraTexture._rawImage withChannels:3 downSamplingWidth:64 height:64];
 @endcode
 
 @param data NSData object containing the image data.
 @param channels The number of channels contained within the image data. For example, RGB data would contain 3 channels.
 @param width The width, in pixels, to which the image will be scaled before computing the average.
 @param height The height, in pixels, to which the image will be scaled before computing the average.
 
 @return Average colour of the image as an ARColour object.
 */
- (ARColour *)averageColourFromData:(NSData *)data withChannels:(int)channels downsamplingWidth:(int)width height:(int)height;

/**
 Initialise the camera. This is handled automatically when your view controller is a subclass of the ARCameraViewController.
 When the ARCameraStream instance is initialised, it performs the following:
 * Creates a reference to the renderer's texture cache.
 * Creates a reference to a valid camera device.
 * Sets up a new capture session with a valid camera input device.
 * Sets the camera to "continous autofocus" mode, if supported.
 
 Example of use:
 @code
 [[ARCameraStream getInstance] initialise];
 @endcode
 */
- (void)initialise;

/**
 Deinitialise the camera. This is handled automatically when your view controller is a subclass of the ARCameraViewController.
 
 Example of use:
 @code
 [[ARCameraStream getInstance] deinitialise];
 @endcode
 */
- (void)deinitialise;

/**
 Start the camera stream. This is handled automatically when your view controller is a subclass of the ARCameraViewController.
 
 Example of use:
 @code
 [[ARCameraStream getInstance] start];
 @endcode
 */
- (void)start;

/**
 Stop the camera stream. This is handled automatically when your view controller is a subclass of the ARCameraViewController.
 
 Example of use:
 @code
 [[ARCameraStream getInstance] stop];
 @endcode
 */
- (void)stop;

/**
 @param delegate The delegate to add.
 Add a delegate for camera update event notifications.
 */
- (void)addDelegate:(id<ARCameraStreamEvent>)delegate;

/**
 @param delegate The delegate to remove.
 Remove a delegate from camera update event notifications.
 */
- (void)removeDelegate:(id<ARCameraStreamEvent>)delegate;

/**
 Removes all ARCameraStreamEvent delegates currently associated with this singleton.
 */
- (void) removeDelegates;

@end
