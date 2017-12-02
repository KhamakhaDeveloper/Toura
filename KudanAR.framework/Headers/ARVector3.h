#ifndef __ARVector3_h
#define __ARVector3_h

#import <Foundation/Foundation.h>

@class ARQuaternion;

/**
 An ARVector3 is a 3-Dimensional vector consisting of an X, Y and Z component. Generally used to represent a point in 3D space.
 */
@interface ARVector3 : NSObject <NSCoding, NSCopying>

/**
 X component of the vector.
 */
@property (nonatomic) float x;

/**
 Y component of the vector.
 */
@property (nonatomic) float y;

/**
 Z component of the vector.
 */
@property (nonatomic) float z;

/**
 The length, or magnitude, of this vector, equal to sqrt((X * X) + (Y * Y) + (Z * Z)).
 */
@property (nonatomic, readonly) float length;

/**
 Creates a new empty ARVector3.
 
 Example of use:
 @code
 ARVector3 *vector = [ARVector3 vectorWithZero];
 @endcode
 
 @return An ARVector3 with values (0, 0, 0).
 */
+ (ARVector3 *)vectorWithZero;

/**
 Creates a new ARVector3 with the three given values.
 
 Example of use:
 @code
 ARVector3 *vector = [ARVector3 vectorWithValuesX:1.0 y:2.0 z:3.0];
 @endcode
 
 @param x The X component of the vector.
 @param y The Y component of the vector.
 @param z The Z component of the vector.
 
 @return An ARVector3 with values (x, y, z);
 */
+ (ARVector3 *)vectorWithValuesX:(float)x y:(float)y z:(float)z;

/**
 Creates a new ARVector3 with the given value.
 
 Example of use:
 @code
 ARVector3 *vector = [ARVector3 vectorWithValues:1.0];
 @endcode
 
 @float v The value to give all three components of the vector.
 
 @return An ARVector3 with values (v, v, v);
 */
+ (ARVector3 *)vectorWithValues:(float)v;

/**
 Creates a new ARVector3 with the given vector.
 
 Example of use:
 @code
 ARVector3 *vector = [ARVector3 vectorWithVector:otherVector];
 @endcode
 
 @param vec The ARVector3 to get values from.
 
 @return An ARVector3 with the same values as the given vector.
 */
+ (ARVector3 *)vectorWithVector:(ARVector3 *)vec;

/**
 Checks whether this vector is equal to another given vector. A tolerance value is used to account for potential floating-point errors.
 
 Example of use:
 @code
 ARVector3 vectorOne = [ARVector3 vectorWithValues:1.0];
 ARVector3 vectorTwo = [ARVector3 vectorWithValuesX:1.0 y:1.0 z:1.0];
 
 BOOL isEqual = [vectorOne equalsVector:vectorTwo withTolerance:FLT_EPSILON];
 @endcode
 
 @param vector The vector to check against.
 @param tolerance The maximum difference between each component of the vector. For example, if the tolerance were 0.1, then a vector with values (1.0, 1.0, 1.0) would be considered equal to a vector with values (1.0, 0.92, 1.099).
 The value FLT_EPSILON is a costant value of 0.00001, or 1e-5.
 
 @return True if each component of the two vectors are within the tolerance range, false otherwise.
 */
- (BOOL)equalsVector:(ARVector3 *)vector withTolerance:(float)tolerance;

/**
 Adds the components of two vectors together and returns the result.
 
 Example of use:
 @code
 ARVector3 vectorOne = [ARVector3 vectorWithValuesX:1.0 y:2.0 z:3.0];
 ARVector3 vectorTwo = [ARVector3 vectorWithValuesX:4.0 y:5.0 z:6.0];
 ARVector3 vectorThree = [vectorOne addVector:vectorTwo];
 @endcode
 
 @param vector The vector to add to this vector.
 
 @return A new ARVector3  with values (X1 + X2, Y1 + Y2, Z1 + Z2).
 */
- (ARVector3 *)addVector:(ARVector3 *)vector;

/**
 Adds the components of two vectors together and stores the result in this vector.
 
 Example of use:
 @code
 ARVector3 vectorOne = [ARVector3 vectorWithValuesX:1.0 y:2.0 z:3.0];
 ARVector3 vectorTwo = [ARVector3 vectorWithValuesX:4.0 y:5.0 z:6.0];
 [vectorOne localAddVector:vectorTwo];
 @endcode
 
 @param vector The vector to add to this vector.
 
 @return This vector with values (X1 + X2, Y1 + Y2, Z1 + Z2).
 */
- (ARVector3 *)localAddVector:(ARVector3 *)vector;

/**
 Subtracts a given vector's components from the components of this vector and returns the result.
 
 Example of use:
 @code
 ARVector3 vectorOne = [ARVector3 vectorWithValuesX:4.0 y:5.0 z:6.0];
 ARVector3 vectorTwo = [ARVector3 vectorWithValuesX:3.0 y:2.0 z:1.0];
 ARVector3 vectorThree = [vectorOne subtractVector:vectorTwo];
 @endcode
 
 @param vector The vector to subtract from this vector.
 
 @return A new ARVector3 with values (X1 - X2, Y1 - Y2, Z1 - Z2).
 */
- (ARVector3 *)subtractVector:(ARVector3 *)vector;

/**
 Subtracts a given vector's components from the componentes this vector and stores the result in this vector.
 
 Example of use:
 @code
 ARVector3 vectorOne = [ARVector3 vectorWithValuesX:4.0 y:5.0 z:6.0];
 ARVector3 vectorTwo = [ARVector3 vectorWithValuesX:3.0 y:2.0 z:1.0];
 [vectorOne subtractVector:vectorTwo];
 @endcode
 
 @param vector The vector to subtract from this vector.
 
 @return Thie vector with values (X1 - X2, Y1 - Y2, Z1 - Z2).
 */
- (ARVector3 *)localSubtractVector:(ARVector3 *)vector;

/**
 Multiplies this vector's components by the components of a given vector and returns the result.
 This is NOT the same as the Dot Product OR the Cross Product. It simply multiplies the components together.
 
 Example of use:
 @code
 ARVector3 vectorOne = [ARVector3 vectorWithValuesX:1.0 y:2.0 z:3.0];
 ARVector3 vectorTwo = [ARVector3 vectorWithValuesX:2.0 y:4.0 z:6.0];
 ARVector3 vectorThree = [vectorOne multiplyByVector:vectorTwo];
 @endcode
 
 @param vector The vector to multiply with this vector.
 
 @return A new ARVector3 with values (X1 * X2, Y1 * Y2, Z1 * Z2).
 */
- (ARVector3 *)multiplyByVector:(ARVector3 *)vector;

/**
 Multiplies this vector's components by the components of a given vector and stores the result in this vector.
 This is NOT the same as the Dot Product OR the Cross Product. It simply multiplies the components together.
 
 Example of use:
 @code
 ARVector3 vectorOne = [ARVector3 vectorWithValuesX:1.0 y:2.0 z:3.0];
 ARVector3 vectorTwo = [ARVector3 vectorWithValuesX:2.0 y:4.0 z:6.0];
 [vectorOne localMultiplyByVector:vectorTwo];
 @endcode
 
 @param vector The vector to multiply with this vector.
 
 @return This vector with values (X1 * X2, Y1 * Y2, Z1 * Z2).
 */
- (ARVector3 *)localMultiplyByVector:(ARVector3 *)vector;

/**
 Divides this vector's components by the components of a given vector a returns the result.
 
 Example of use:
 @code
 ARVector3 vectorOne = [ARVector3 vectorWithValuesX:8.0 y:12.0 z:25.0];
 ARVector3 vectorTwo = [ARVector3 vectorWithValuesX:2.0 y:3.0 z:5.0];
 ARVector3 vectorThree = [vectorOne divideByVector:vectorTwo];
 @endcode
 
 @param vector The vector to divide this vector by.
 
 @return A new ARVector3 with values (X1 / X2, Y1 / Y2, Z1 / Z2).
 */
- (ARVector3 *)divideByVector:(ARVector3 *)vector;

/**
 Divides this vector's components by the components of a given vector a stores the result in this vector.
 
 Example of use:
 @code
 ARVector3 vectorOne = [ARVector3 vectorWithValuesX:8.0 y:12.0 z:25.0];
 ARVector3 vectorTwo = [ARVector3 vectorWithValuesX:2.0 y:3.0 z:5.0];
 [vectorOne divideByVector:vectorTwo];
 @endcode
 
 @param vector The vector to divide this vector by.
 
 @return This vector with values (X1 / X2, Y1 / Y2, Z1 / Z2).
 */
- (ARVector3 *)localDivideByVector:(ARVector3 *)vector;

/**
 Multiplies each of this vector's components by a given value and returns the result.
 
 Example of use:
 @code
 ARVector3 oldVector = [ARVector3 vectorWithValuesX:1.0 y:2.0 z:3.0];
 ARVector3 newVector = [oldVector multiplyByScalar:4.0];
 @endcode
 
 @param scalar The value to multiply this vector by.
 
 @return A new ARVector3 with values (X * scalar, Y * scalar, Z * scalar).
 */
- (ARVector3 *)multiplyByScalar:(double)scalar;

/**
 Divides each of this vector's components by a given value and returns the result.
 
 Example of use:
 @code
 ARVector3 oldVector = [ARVector3 vectorWithValuesX:2.0 y:4.0 z:8.0];
 ARVector3 newVector = [oldVector divideByScalar:2.0];
 @endcode
 
 @param scalar The value to divide this vector by.
 
 @return A new ARVector3 with values (X / scalar, Y / scalar, Z / scalar).
 */
- (ARVector3 *)divideByScalar:(double)scalar;

/**
 Calculates the Euclidean distance between two 3-Dimensional points and returns the result.
 
 Example of use:
 @code
 ARVector3 vectorOne = [ARVector3 vectorWithValuesX:1.0 y:2.0 z:3.0];
 ARVector3 vectorTwo = [ARVector3 vectorWithValuesX:5.0 y:10.0 z:15.0];
 float distance = [vectorOne distanceToVector:vectorTwo];
 @endcode
 
 @param vector The other vector to use for the distance calculation.
 
 @return The Euclidean distance between the two ARVector3 objects.
 */
- (float)distanceToVector:(ARVector3 *)vector;

/**
 Calculates the dot product of this vector and another given vector and returns the result.
 
 Example of use:
 @code
 ARVector3 vectorOne = [ARVector3 vectorWithValuesX:1.0 y:2.0 z:3.0];
 ARVector3 vectorTwo = [ARVector3 vectorWithValuesX:7.0 y:3.0 z:12.0];
 float dotProduct = [vectorOne dotProductWithVector:vectorTwo];
 @endcode
 
 @param vector The other vector to use for the dot product calculation.
 
 @return The dot product of the two vectors, ((X1 * X2) + (Y1 * Y2) + (Z1 * Z2)).
 */
- (float)dotProductWithVector:(ARVector3 *)vector;

/**
 Normliases this vector so that each component of the vector is in the range 0..1 and returns the result.
 This is useful for finding the direction of a vector without its magnitude.
 
 Example of use:
 @code
 ARVector3 vector = [ARVector3 vectorWithValuesX:3.0 y:4.0 z:12.0];
 ARVector3 normalisedVector = [vector normalise];
 @endcode
 
 @return A new ARVector3 containing the normalised vector.
 */
- (ARVector3 *)normalise;

/**
 Normliases this vector so that each component of the vector is in the rang 0..1 and stores the result in this vector.
 
 Example of use:
 @code
 ARVector3 vector = [ARVector3 vectorWithValuesX:3.0 y:4.0 z:12.0];
 [vector localNormalise];
 
 @return This vector containing the normalised vector.
 */
- (ARVector3 *)localNormalise;

/**
 Multiplies each component of this vector by -1 and returns the result.
 
 Example of use:
 @code
 ARVector3 vector = [ARVector3 vectorWithValuesX:-1.0 y:2.0 z:-3.0];
 ARVector3 negatedVector = [vector negate];
 @endcode
 
 @return A new ARVector3 containing the negated vector (-X, -Y, -Z).
 */
- (ARVector3 *)negate;

/**
 Calculates the cross product of this vector with the given vector and returns the result.
 
 Example of use:
 @code
 ARVector3 vectorOne = [ARVector3 vectorWithValuesX:1.0 y:2.0 z:3.0];
 ARVector3 vectorTwo = [ARVector3 vectorWithValuesX:2.0 y:3.0 z:4.0];
 ARVector3 crossProductVector = [vectorOne crossProductWithVector:vectorTwo];
 @endcode
 
 @param vector The other vector to use for the cross product calculation.
 
 @return A new ARVector3 containing the cross product of the two vectors.
 */
- (ARVector3 *)crossProductWithVector:(ARVector3 *)vector;

/**
 Calculates the cross product of this vector with the given vector and store the result in this vector.
 
 Example of use:
 @code
 ARVector3 vectorOne = [ARVector3 vectorWithValuesX:1.0 y:2.0 z:3.0];
 ARVector3 vectorTwo = [ARVector3 vectorWithValuesX:2.0 y:3.0 z:4.0];
 [vectorOne localCrossProductWithVector:vectorTwo];
 @endcode
 
 @param vector The other vector to use for the cross product calculation.
 
 @return This vector containing the cross product of the two vectors.
 */
- (ARVector3 *)localCrossProductWithVector:(ARVector3 *)vector;

/**
 Calculates the quaternion rotation between this vector and the given vector and returns the result.
 
 Example of use:
 @code
 ARVector3 vectorOne = [ARVector3 vectorWithValuesX:1.0 y:2.0 z:3.0];
 ARVector3 vectorTwo = [ARVector3 vectorWithValuesX:-3.0 y:4.0 z:9.0];
 
 ARQuaternion rotationToVector = [vectorOne rotationTo:vectorTwo];
 @endcode
 
 @param vector The other vector to find the rotation to.
 
 @return A new ARQuaternion representing the rotation between this vector and the given vector.
 */
- (ARQuaternion *)rotationTo:(ARVector3 *)vector;

/**
 Linearly interpolates between two vectors and returns the result.
 This is most commonly used to find a point some fraction of the way along a line between two endpoints (e.g. to move an object gradually between those points). With lerp, each step is equidistant.
 When time = 0 this vector is returned. When time = 1 the given vector is returned. When time = 0.5 a point midway between this vector and the given vector is returned.
 Values lower than 0 or above 1 will return a point outside the range of the two points along the same line.
 
 Example of use:
 @code
 ARVector3 vectorOne = [ARVector3 vectorWithValuesX:1.0 y:-2.0 z:3.0];
 ARVector3 vectorTwo = [ARVector3 vectorWithValuesX:-2.0 y:5.0 z:-8.0];
 ARVector3 lerpVector = [vectorOne lerpTo:vectorTwo atTime:0.5];
 @endcode
 
 @param vector The other vector to use for the interpolation calculation.
 @param time Represents a percentage of how far along the line the resulting point should be.
 
 @return A new ARVector3 representing a point between this vector and the given vector.
 */
- (ARVector3 *)lerpTo:(ARVector3 *)vector atTime:(float)time;

/**
 Sets the components of this vector with the given values.
 
 Example of use:
 @code
 [vector setX:1.0 y:2.0 z:3.0];
 @endcode
 
 @param x The value to give the X component of this vector.
 @param y The value to give the Y component of this vector.
 @param z The value to give the Z component of this vector.
 */
- (void)setX:(float)x y:(float)y z:(float)z;

/**
 Allows an ARNode to add an ARVector3 as an observer.
 
 @param delegate The delegate to assign to this vector.
 @param selector The selector method to call when the vector is modified.
 */
- (void)setModifyObserverWithDelegate:(id)delegate selector:(SEL)selector;

@end

#endif
