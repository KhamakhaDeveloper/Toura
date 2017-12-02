#import <KudanAR/ARTexture.h>

/**
 An ARTextureCube is a "Cubemap" texture, a collection of six square textures that represent the reflections on an environment.
 The six squares form the faces of an imaginary cube that surrounds an object.
 Each face represents the view along the directions of the world axes (up, down, left, right, forward and back).
 Cubemaps are often used to capture reflections or “surroundings” of objects. 
 For example, skyboxes often use cubemaps, as do environment reflections, which allow an object to appear as though it is a reflective surface.
 
 Images used must be a "Power of Two" texture. This means that the width and height of each image must be a power of 2 (128, 256, 512, 1024, etc).
 */
@interface ARTextureCube : ARTexture

/**
 Initialise a cube with an array of UIImage images.
 The array must be in the correct order for the mapping to work properly.
 The order of images cannot be altered once initialised.
 The correct order of images is as follows:
 Element 0 - Right.
 Element 1 - Left.
 Element 2 - Top.
 Element 3 - Bottom.
 Element 4 - Front.
 Element 5 - Back.
 
 Example of use:
 @code
 UIImage *backImage = [UIImage imageNamed:@"rightImage.jpg"];
 UIImage *frontImage = [UIImage imageNamed:@"leftImage.jpg"];
 UIImage *leftImage = [UIImage imageNamed:@"topImage.jpg"];
 UIImage *rightImage = [UIImage imageNamed:@"bottomImage.jpg"];
 UIImage *topImage = [UIImage imageNamed:@"frontImage.jpg"];
 UIImage *bottomImage = [UIImage imageNamed:@"backImage.jpg"];
 NSArray *array = @[rightImage, leftImage, topImage, bottomImage, frontImage, backImage];
 ARTextureCube *textureCube = [[ARTextureCube alloc] initWithUIImages:array];
 @endcode
 
 @param images An array of UIImage objects to load into the cube map.
 */
- (instancetype)initWithUIImages:(NSArray *)images;

/**
 Initialise with an array of strings, each of which is a file path relative to the main bundle, pointing to image files.
 The array must be in the correct order for the mapping to work properly.
 The order of images cannot be altered once initialised.
 The correct order of images is as follows:
 Element 0 - Right.
 Element 1 - Left.
 Element 2 - Top.
 Element 3 - Bottom.
 Element 4 - Front.
 Element 5 - Back.
 
 Example of use:
 @code
 NSArray *array = @[@"rightImage.jpg", @"leftImage.jpg", @"topImage.jpg", @"bottomImage.jpg", @"frontImage.jpg", @"backImage.jpg"];
 ARTextureCube *textureCube = [[ARTextureCube alloc] initWithBundledFiles:array];
 @endcode
 
 @param images An array of image file names relative to the main bundle.
 */
- (instancetype)initWithBundledFiles:(NSArray *)bundledFiles;

@end
