#import <Foundation/Foundation.h>
#import <KudanAR/ARMaterial.h>

/**
 The ARColourMaterial is a material that renders a solid colour. Alpha transparency is supported.
 */
@interface ARColourMaterial : ARMaterial

/**
 The red component of the colour, in the range 0..1.
 */
@property float red;

/**
 The green component of the colour, in the range 0..1.
 */
@property float green;

/**
 The blue component of the colour, in the range 0..1.
 */
@property float blue;

/**
 The alpha component of the colour, in the range 0..1.
 */
@property float alpha;

/**
 Sets whether material draws in the depth buffer only.
 If true, this will not draw to the colour buffer. Useful for occlusion materials.
 
 A colour buffer stores the RGB colour data of a pixel. When a material is drawn, it uses the colour data to determine the colour of each pixel.
 A depth buffer stores the depth information of a pixel. When materials are drawn, if two or more points overlap, the depth data is used to determine which point is closest to the camera and therefore which pixel's colour data should be drawn.
 */
@property (nonatomic) BOOL depthOnly;

/**
 Initialise with red, green and blue components. Each component is in the range 0..1.
 The alpha of the material is set to 1.0 when initialised using this method.
 
 Example of use:
 @code
 ARColour *colour = [[ARColour alloc] initWithRed:1.0 green:0.3 blue:0.4];
 @endcode
 
 @param red component value 0..1.
 @param green component value 0..1.
 @param blue component value 0..1.
 */
- (instancetype)initWithRed:(float)red green:(float)green blue:(float)blue;

/**
 Initialise with red, green, blue and alpha components. Each component is in the range 0..1.
 
 Example of use:
 @code
 ARColour *colour = [[ARColour alloc] initWithRed:0.6 green:0.3 blue:0.8 alpha:0.5];
 @endcode
 
 @param red component value 0..1.
 @param green component value 0..1.
 @param blue component value 0..1.
 @param alpha component value 0..1.
 */
- (instancetype)initWithRed:(float)red green:(float)green blue:(float)blue alpha:(float)alpha;

/**
  Class method that initialises an instance of ARColourMaterial with the given red, green and blue component values.
 Each component is in the range 0..1.
 
 Example of use:
 @code
 ARColour *colour = [ARColour colourMaterialWithRed:0.2 green:0.4 blue:0.8];
 @endcode
 
 @param red component value 0..1.
 @param green component value 0..1.
 @param blue component value 0..1.
 */
+ (instancetype)colourMaterialWithRed:(float)red green:(float)green blue:(float)blue;

@end
