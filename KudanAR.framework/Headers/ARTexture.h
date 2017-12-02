#import <Foundation/Foundation.h>
#import <OpenGLES/ES2/gl.h>

@class UIImage;

/**
 An ARTexture is a class representing a 2D texture. Textures cannot exceed 2048x2048 pixels in size.
 
 Textures are typically used for images to decorate 3D models, but in reality they can be used to store many different kinds of data on the GPU.
 */
@interface ARTexture : NSObject
{
    /**
     The raw image data, in bytes. This data is in the RGBA format.
     */
    NSData *_rawImage;
}

/**
 Texture filtering modes:
 */
typedef enum {
    /**
     Use 'Nearest Neighbour' filtering.
     */
    ARTextureFilterNearest,
    
    /**
     Use Linear Interpolation.
     */
    ARTextureFilterLinear,
} ARTextureFilter;

/**
 The texture's handle in OpenGL.
 This is a reference to the texture and allows access to it on the GPU.
 **/
@property (nonatomic) GLuint textureID;

/**
 The width of the texture, in pixels.
 */
@property (nonatomic) unsigned long width;

/**
 The height of the texture, in pixels.
 */
@property (nonatomic) unsigned long height;

/**
 Whether or not this texture is a "Power of Two" texture.
 A texture is "Power of Two" if and only if its width and height are both some power of 2 (64, 128, 256, 1024, etc).
 While it is not a problem if a texture is not "Power of Two", there are some features of OpenGL that can only be used with "Power of Two" textures.
 */
@property (nonatomic) BOOL isPowerOfTwo;

/**
 The filtering type used for minification. ARTextureFilterLinear is recommended for less aliasing.
 Minification is a type of anti-aliasing, where texture samples exist at a higher frequency than required for the sample frequency needed for texture fill.
 */
@property (nonatomic) ARTextureFilter minificationFilter;

/**
 The filtering type used for magnification. ARTextureFilterLinear is recommended for less aliasing.
 Magnification is a type of reconstruction filter where sparse data is interpolated to fill gaps.
 */
@property (nonatomic) ARTextureFilter magnificationFilter;

/**
 Create a texture from a UIImage.
 
 Example of use:
 @code
 ARTexture *texture = [[ARTexture alloc] initWithUIImage:[UIImage imageNamed:@"exampleTexture.jpg"]];
 @endcode
 
 @param image The UIImage to create the texture from.
 */
- (instancetype)initWithUIImage:(UIImage *)image;

/**
 Create an empty texture to be loaded with an image later.
 
 Example of use:
 @code
 ARTexture *texture = [[ARTexture alloc] initWithEmpty];
 @endcode
 */
- (instancetype)initWithEmpty;


//+ (id)textureWithUIImage:(UIImage *)image;
//+ (id)textureWithUIImage:(UIImage *)image normalMap:(BOOL)normalMap;

- (instancetype)initWithExistingTextureID:(unsigned)textureID;

/**
 Generates a new texture on the GPU using the texture ID.
 **/
- (void)generateTexture;

/**
 Allocate memory on the GPU to the texture and upload texture data to it.
 */
- (void)uploadTexture;

/**
 Loads image data, sets image width and height, sets pixel format, and stores it in the rawImage property.
 
 @param image Image to generate texture from.
 @param reverseLines  Whether to read pixels from top(YES) or bottom.
 */
- (void)loadTextureFromUIImage:(UIImage *)image reverseLines:(BOOL)reverseLines;

- (void)uploadBGRATexture:(unsigned char *)data width:(float)width height:(float)height;
- (void)uploadBGRATextureSub:(unsigned char *)data width:(float)width height:(float)height;

/**
 Method called just before this texture is rendered.
 
 @return BOOL Whether or not to proceed with rendering.
 */
- (BOOL)preRender;

/**
 Method called just after this texture has been used in rendering.
 */
- (void)postRender;

@end
