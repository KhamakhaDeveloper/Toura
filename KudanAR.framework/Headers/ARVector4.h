#import <Foundation/Foundation.h>

/**
 An ARVector4 is a 4-Dimensional vector consisting of an X, Y, Z and W component. Generally used for graphical shading.
 */
@interface ARVector4 : NSObject

/**
 The x value of the vector.
 */
@property (nonatomic) float x;

/**
 The y value of the vector.
 */
@property (nonatomic) float y;

/**
 The z value of the vector.
 */
@property (nonatomic) float z;

/**
 The w value of the vector.
 */
@property (nonatomic) float w;

/**
 Create a vector with all 4 components set to 0.
 
 Example of use:
 @code
 ARVector4 *vector = [ARVector4 vectorWithZero];
 @endcode
 
 @return A vector with (0, 0, 0, 0)
 */
+ (ARVector4 *)vectorWithZero;

/**
 Create a vector with the specified component values.
 
 Example of use:
 @code
 ARVector4 *vector = [ARVector4 vectorWithValuesX:1.0 y:0.0 z:1.0 w:0.0];
 @endcode
 
 @param x The x component of the vector.
 @param y The y component of the vector.
 @param z The z component of the vector.
 @param w The w component of the vector.
 
 @return A vector with components set to the specified values.
 */
+ (ARVector4 *)vectorWithValuesX:(float)x y:(float)y z:(float)z w:(float)w;

/**
 Adds the components of two vectors together and returns the result.
 
 Example of use:
 @code
 ARVector4 vectorOne = [ARVector4 vectorWithValuesX:1.0 y:2.0 z:3.0 w:4.0];
 ARVector4 vectorTwo = [ARVector4 vectorWithValuesX:5.0 y:6.0 z:7.0 w:8.0];
 ARVector4 vectorThree = [vectorOne addVector:vectorTwo];
 @endcode
 
 @param vector The vector to add to this vector.
 
 @return A new ARVector4 with values (X1 + X2, Y1 + Y2, Z1 + Z2, W1 + W2).
 */
- (ARVector4 *)addVector:(ARVector4 *)vector;

/**
 Adds the components of two vectors together and stores the result in this vector.
 
 Example of use:
 @code
 ARVector4 vectorOne = [ARVector4 vectorWithValuesX:1.0 y:2.0 z:3.0 w:4.0];
 ARVector4 vectorTwo = [ARVector4 vectorWithValuesX:5.0 y:6.0 z:7.0 w:8.0];
 [vectorOne localAddVector:vectorTwo];
 @endcode
 
 @param vector The vector to add to this vector.
 
 @return This vector with values (X1 + X2, Y1 + Y2, Z1 + Z2, W1 + W2).
 */
- (ARVector4 *)localAddVector:(ARVector4 *)vector;

/**
 Subtracts a given vector's components from the components of this vector and returns the result.
 
 Example of use:
 @code
 ARVector4 vectorOne = [ARVector4 vectorWithValuesX:8.0 y:7.0 z:6.0 w:5.0];
 ARVector4 vectorTwo = [ARVector4 vectorWithValuesX:4.0 y:3.0 z:2.0 w:1.0];
 ARVector4 vectorThree = [vectorOne subtractVector:vectorTwo];
 @endcode
 
 @param vector The vector to subtract from this vector.
 
 @return A new ARVector4 with values (X1 - X2, Y1 - Y2, Z1 - Z2, W1 - W2).
 */
- (ARVector4 *)subtractVector:(ARVector4 *)vector;

/**
 Subtracts a given vector's components from the componentes this vector and stores the result in this vector.
 
 Example of use:
 @code
 ARVector4 vectorOne = [ARVector4 vectorWithValuesX:8.0 y:7.0 z:6.0 w:5.0];
 ARVector4 vectorTwo = [ARVector4 vectorWithValuesX:4.0 y:3.0 z:2.0 w:1.0];
 [vectorOne subtractVector:vectorTwo];
 @endcode
 
 @param vector The vector to subtract from this vector.
 
 @return Thie vector with values (X1 - X2, Y1 - Y2, Z1 - Z2, W1 - W2).
 */
- (ARVector4 *)localSubtractVector:(ARVector4 *)vector;

/**
 Multiplies this vector's components by the components of a given vector and returns the result.
 This is NOT the same as the Dot Product OR the Cross Product. It simply multiplies the components together.
 
 Example of use:
 @code
 ARVector4 vectorOne = [ARVector4 vectorWithValuesX:1.0 y:2.0 z:3.0 w:4.0];
 ARVector4 vectorTwo = [ARVector4 vectorWithValuesX:5.0 y:6.0 z:7.0 w:8.0];
 ARVector4 vectorThree = [vectorOne multiplyByVector:vectorTwo];
 @endcode
 
 @param vector The vector to multiply with this vector.
 
 @return A new ARVector4 with values (X1 * X2, Y1 * Y2, Z1 * Z2, W1 * W2).
 */
- (ARVector4 *)multiplyByVector:(ARVector4 *)vector;

/**
 Multiplies this vector's components by the components of a given vector and stores the result in this vector.
 This is NOT the same as the Dot Product OR the Cross Product. It simply multiplies the components together.
 
 Example of use:
 @code
 ARVector4 vectorOne = [ARVector4 vectorWithValuesX:1.0 y:2.0 z:3.0 w:4.0];
 ARVector4 vectorTwo = [ARVector4 vectorWithValuesX:5.0 y:6.0 z:7.0 w:8.0];
 [vectorOne localMultiplyByVector:vectorTwo];
 @endcode
 
 @param vector The vector to multiply with this vector.
 
 @return This vector with values (X1 * X2, Y1 * Y2, Z1 * Z2, W1 * W2).
 */
- (ARVector4 *)localMultiplyByVector:(ARVector4 *)vector;

/**
 Divides this vector's components by the components of a given vector a returns the result.
 
 Example of use:
 @code
 ARVector4 vectorOne = [ARVector4 vectorWithValuesX:8.0 y:7.0 z:6.0 w:5.0];
 ARVector4 vectorTwo = [ARVector4 vectorWithValuesX:4.0 y:3.0 z:2.0 w:1.0];
 ARVector4 vectorThree = [vectorOne divideByVector:vectorTwo];
 @endcode
 
 @param vector The vector to divide this vector by.
 
 @return A new ARVector4 with values (X1 / X2, Y1 / Y2, Z1 / Z2, W1 / W2).
 */
- (ARVector4 *)divideByVector:(ARVector4 *)vector;

/**
 Divides this vector's components by the components of a given vector a stores the result in this vector.
 
 Example of use:
 @code
 ARVector4 vectorOne = [ARVector4 vectorWithValuesX:8.0 y:7.0 z:6.0 w:5.0];
 ARVector4 vectorTwo = [ARVector4 vectorWithValuesX:4.0 y:3.0 z:2.0 w:1.0];
 [vectorOne divideByVector:vectorTwo];
 @endcode
 
 @param vector The vector to divide this vector by.
 
 @return This vector with values (X1 / X2, Y1 / Y2, Z1 / Z2, W1 / W2).
 */
- (ARVector4 *)localDivideByVector:(ARVector4 *)vector;

/**
 Calculates the dot product of this vector and another given vector and returns the result.
 
 Example of use:
 @code
 ARVector4 vectorOne = [ARVector4 vectorWithValuesX:1.0 y:2.0 z:3.0 w:4.0];
 ARVector4 vectorTwo = [ARVector4 vectorWithValuesX:7.0 y:3.0 z:9.0 w:1.0];
 float dotProduct = [vectorOne distanceToVector:vectorTwo];
 @endcode
 
 @param vector The other vector to use for the dot product calculation.
 
 @return The dot product of the two vectors, ((X1 * X2) + (Y1 * Y2) + (Z1 * Z2) + (W1 * W2)).
 */
- (float)dotProductWithVector:(ARVector4 *)vector;

/**
 Sets the components of this vector with the given values.
 
 Example of use:
 @code
 [vector setX:1.0 y:2.0 z:3.0 w:4.0];
 @endcode
 
 @param x The value to give the X component of this vector.
 @param y The value to give the Y component of this vector.
 @param z The value to give the Z component of this vector.
 @param w The value to give the W component of this vector.
 */
- (void)setX:(float)x y:(float)y z:(float)z w:(float)w;

/**
 Allows an ARNode to add an ARVector3 as an observer.
 
 @param delegate The delegate to assign to this vector.
 @param selector The selector method to call when the vector is modified.
 */
- (void)setModifyObserverWithDelegate:(id)delegate selector:(SEL)selector;

@end
