#import <Foundation/Foundation.h>

@class ARVector3;
@class ARMatrix4;

/**
 An ARQuaternion is a class that represents a rotation.
 Working with quaternions is better than simply using Euler angles because quaternions avoid problems such as gimbal lock.
 */
@interface ARQuaternion : NSObject <NSCoding>

/**
 The x value of the quaternion.
 */
@property (nonatomic, readonly) float x;

/**
 The y value of the quaternion.
 */
@property (nonatomic, readonly) float y;

/**
 The z value of the quaternion.
 */
@property (nonatomic, readonly) float z;

/**
 The w value of the quaternion.
 */
@property (nonatomic, readonly) float w;

/**
 Creates an ARQuaternion with identity, representing no rotation.
 
 Example of use:
 @code
 ARQuaternion quaternion = [ARQuaternion quaternionWithIdentity];
 @endcode
 
 @return A new ARQuaternion with values (0, 0, 0, 1).
 */
+ (ARQuaternion *)quaternionWithIdentity;

/**
 Creates an ARQuaternion with the given values.
 
 Example of use:
 @code
 ARQuaternion quaternion = [ARQuaternion quaternionWithX:0.0 y:1.0 z:0.0 w:1.0];
 @endcode
 
 @param x The value to give the X component of this quaternion.
 @param y The value to give the Y component of this quaternion.
 @param z The value to give the Z component of this quaternion.
 @param w The value to give the W component of this quaternion.
 
 @return A new ARQuaternion with values (X, Y, Z, W).
 */
+ (ARQuaternion *)quaternionWithX:(float)x y:(float)y z:(float)z w:(float)w;

/**
 Creates an ARQuaternion from a 4x4 matrix.
 
 Example of use:
 @code
 ARQuaternion quaternion = [ARQuaternion quaternionFromMatrix4:[ARMatrix4 matrixWithIdentity];
 @endcode
 
 @param matrix The 4x4 matrix to convert to a quaternion.
 
 @return A new ARQuaternion made from the given matrix.
 */
+ (ARQuaternion *)quaternionFromMatrix4:(ARMatrix4 *)matrix;

/**
 Creates an ARQuaternion representing a rotation of the given angle in degrees around the constructed axis.
 
 Example of use:
 @code
 ARQuaternion quaternion = [ARQuaternion quaternionWithDegrees:45 axisX:1.0 y:0.0 z:1.0];
 @endcode
 
 @param angle The number of degrees around the axes this quaternion should rotate.
 @param x The x component of the axis.
 @param y The y component of the axis.
 @param z The z component of the axis.
 
 @return A new ARQuaternion of rotation angle degrees around the axis (X, Y, Z).
 */
+ (ARQuaternion *)quaternionWithDegrees:(float)angle axisX:(float)x y:(float)y z:(float)z;

/**
 Creates an ARQuaternion representing a rotation of the given angle in radians around the constructed axis.
 
 Example of use:
 @code
 ARQuaternion quaternion = [ARQuaternion quaternionWithRadisn:M_PI/2 axisX:1.0 y:0.0 z:1.0];
 @endcode
 
 @param angle The number of radians around the axes this quaternion should rotate.
 @param x The x component of the axis.
 @param y The y component of the axis.
 @param z The z component of the axis.
 
 @return A new ARQuaternion of rotation angle degrees around the axis (X, Y, Z).
 */
+ (ARQuaternion *)quaternionWithRadians:(float)angle axisX:(float)x y:(float)y z:(float)z;

/**
 Checks whether this quaternion is equal to another given quaternion. A tolerance value is used to account for potential floating-point errors.
 
 Example of use:
 @code
 ARQuaternion quaternionOne = [ARQuaternion quaternionWithDegrees:90 axisX:1.0 y:0.0 z:1.0];
 ARQuaternion quaternionTwo = [ARQuaternion quaternionWithRadians:M_PI/2 axisX:1.0 y:0 z:1.0];
 
 BOOL isEqual = [quaternionOne equalsQuaternion:quaternionTwo withTolerance:FLT_EPSILON];
 @endcode
 
 @param quaternion The quaternion to check against.
 @param tolerance The maximum difference between each component of the quaternion. For example, if the tolerance were 0.1, then a quaternion with values (0.5, 0.5, 0.5, 1.0) would be considered equal to a quaternion with values (0.45, 0.52, 0.59, 1.01).
 The value FLT_EPSILON is a costant value of 0.00001, or 1e-5.
 
 @return True if each component of the two quaternions are within the tolerance range, false otherwise.
 */
- (BOOL)equalsQuaternion:(ARQuaternion *)quaternion withTolerance:(float)tolerance;

/**
 Adds the components of two quaternions together and returns the result.
 
 Example of use:
 @code
 ARQuaternion quaternionOne = [ARQuaternion quaternionWithDegrees:90 axisX:1.0 y:0.0 z:1.0];
 ARQuaternion quaternionTwo = [ARQuaternion quaternionWithDegrees:45 axisX:0.0 y:1.0 z:0.0];
 ARQuaternion quaternionThree = [quaternionOne addQuaternion:quaternionTwo];
 @endcode
 
 @param quaternion The quaternion to add to this quaternion.
 
 @return A new ARQuaternion with values (X1 + X2, Y1 + Y2, Z1 + Z2, W1 + W2).
 */
- (ARQuaternion *)addQuaternion:(ARQuaternion *)quaternion;

/**
 Adds the components of two quaternions together and stores the result in this quaternion.
 
 Example of use:
 @code
 ARQuaternion quaternionOne = [ARQuaternion quaternionWithDegrees:90 axisX:1.0 y:0.0 z:1.0];
 ARQuaternion quaternionTwo = [ARQuaternion quaternionWithDegrees:45 axisX:0.0 y:1.0 z:0.0];
 [quaternionOne localAddQuaternion:quaternionTwo];
 @endcode
 
 @param quaternion The quaternion to add to this quaternion.
 
 @return This quaternion with values (X1 + X2, Y1 + Y2, Z1 + Z2, W1 + W2).
 */
- (ARQuaternion *)localAddQuaternion:(ARQuaternion *)quaternion;

/**
 Subtracts a given quaternion's components from the components of this quaternion and returns the result.
 
 Example of use:
 @code
 ARQuaternion quaternionOne = [ARQuaternion quaternionWithDegrees:90 axisX:1.0 y:0.0 z:1.0];
 ARQuaternion quaternionTwo = [ARQuaternion quaternionWithDegrees:45 axisX:0.0 y:1.0 z:0.0];
 ARQuaternion quaternionThree = [quaternionOne subtractQuaternion:quaternionTwo];
 @endcode
 
 @param quaternion The quaternion to subtract from this quaternion.
 
 @return A new ARQuaternion with values (X1 - X2, Y1 - Y2, Z1 - Z2, W1 - W2).
 */
- (ARQuaternion *)subtractQuaternion:(ARQuaternion *)quaternion;

/**
 Subtracts a given quaternion's components from the components of this quaternion and stores the result in this quaternion.
 
 Example of use:
 @code
 ARQuaternion quaternionOne = [ARQuaternion quaternionWithDegrees:90 axisX:1.0 y:0.0 z:1.0];
 ARQuaternion quaternionTwo = [ARQuaternion quaternionWithDegrees:45 axisX:0.0 y:1.0 z:0.0];
 [quaternionOne localSubtractQuaternion:quaternionTwo];
 @endcode
 
 @param quaternion The quaternion to subtract from this quaternion.
 
 @return This quaternion with values (X1 - X2, Y1 - Y2, Z1 - Z2, W1 - W2).
 */
- (ARQuaternion *)localSubtractQuaternion:(ARQuaternion *)quaternion;

/**
 Multiplies this quaternion's components by the components of a given quaternion and returns the result.
 This is NOT the same as the Dot Product OR the Cross Product. It simply multiplies the components together.
 
 Example of use:
 @code
 ARQuaternion quaternionOne = [ARQuaternion quaternionWithDegrees:90 axisX:1.0 y:0.0 z:1.0];
 ARQuaternion quaternionTwo = [ARQuaternion quaternionWithDegrees:45 axisX:0.0 y:1.0 z:0.0];
 ARQuaternion quaternionThree = [quaternionOne multiplyByquaternion:quaternionTwo];
 @endcode
 
 @param quaternion The quaternion to multiply with this quaternion.
 
 @return A new ARQuaternion with values (X1 * X2, Y1 * Y2, Z1 * Z2, W1 * W2).
 */
- (ARQuaternion *)multiplyByQuaternion:(ARQuaternion *)quaternion;

/**
 Multiplies this quaternion's components by the components of a given quaternion and stores the result in this quaternion.
 This is NOT the same as the Dot Product. It simply multiplies the components together.
 
 Example of use:
 @code
 ARQuaternion quaternionOne = [ARQuaternion quaternionWithDegrees:90 axisX:1.0 y:0.0 z:1.0];
 ARQuaternion quaternionTwo = [ARQuaternion quaternionWithDegrees:45 axisX:0.0 y:1.0 z:0.0];
 [quaternionOne localMultiplyByquaternion:quaternionTwo];
 @endcode
 
 @param quaternion The quaternion to multiply with this quaternion.
 
 @return This quaternion with values (X1 * X2, Y1 * Y2, Z1 * Z2, W1 * W2).
 */
- (ARQuaternion *)localMultiplyByQuaternion:(ARQuaternion *)quaternion;

/**
 Multiplies this quaternion by an ARVector3 and returns the resulting rotated vector.
 
 Example of use:
 @code
 ARQuaternion quaternion = [ARQuaternion quaternionWithDegrees:90 axisX:1.0 y:0.0 z:1.0];
 ARVector3 vector = [ARVector3 vectorWithValuesX:1.0 y:2.0 z:3.0];
 ARVector3 rotatedVector = [quaternion multiplyByVector:vector];
 @endcode
 
 @param vector The vector to multiply this quaternion by.
 
 @return A new ARVector3 containing the given vector rotated by this quaternion.
 */
- (ARVector3 *)multiplyByVector:(ARVector3 *)vector;

/**
 Multiplies this quaternion by an ARVector3 and stores the resulting rotated vector in the given vector.
 
 Example of use:
 @code
 ARQuaternion quaternion = [ARQuaternion quaternionWithDegrees:90 axisX:1.0 y:0.0 z:1.0];
 ARVector3 vector = [ARVector3 vectorWithValuesX:1.0 y:2.0 z:3.0];
 [quaternion localMultiplyByVector:vector];
 @endcode
 
 @param vector The vector to multiply this quaternion by.
 
 @return A new ARVector3 containing the given vector rotated by this quaternion.
 */
- (ARVector3 *)localMultiplyByVector:(ARVector3 *)vector;

/**
 Multiplies this quaternion by -1 and returns the result.
 
 Example of use:
 @code
 ARQuaternion quaternion = [ARQuaternion quaternionWithDegrees:90 axisX:1.0 y:0.0 z:1.0];
 ARQuaternion negatedQuaternion = [quaternion negate];
 @endcode
 
 @return A new ARQuaternion with values (-X, -Y, -Z, -W).
 */
- (ARQuaternion *)negate;

/**
 Multiplies this quaternion by -1 and stores the result in this quaternion.
 
 Example of use:
 @code
 ARQuaternion quaternion = [ARQuaternion quaternionWithDegrees:90 axisX:1.0 y:0.0 z:1.0];
 [quaternion localNegate];
 @endcode
 
 @return This quaternion with values (-X, -Y, -Z, -W).
 */
- (ARQuaternion *)localNegate;

/**
 Calculates the dot product of this quaternion and another given quaternion and returns the result.
 
 Example of use:
 @code
 ARQuaternion quaternionOne = [ARQuaternion quaternionWithDegrees:90 axisX:1.0 y:0.0 z:1.0];
 ARQuaternion quaternionTwo = [ARQuaternion quaternionWithDegrees:45 axisX:0.0 y:1.0 z:0.0];
 float dot = [quaternionOne dotWithQuaternion:quaternionTwo];
 @endcode
 
 @param quaternion The other quaternion to use for the dot product calculation.
 
 @return The dot product of the two quaternions.
 */
- (float)dotWithQuaternion:(ARQuaternion *)quaternion;

/**
 Normliases this quaternion so that each component of the quaternion is in the range 0..1 and returns the result.
 
 Example of use:
 @code
 ARQuaternion quaternion = [ARQuaternion quaternionWithDegrees:90 axisX:1.0 y:0.0 z:1.0];
 ARQuaternion normalisedQuaternion = [quaternion normalise];
 @endcode
 
 @return A new ARQuaternion containing the normalised quaternion.
 */
- (ARQuaternion *)normalise;

/**
 Normliases this quaternion so that each component of the quaternion is in the range 0..1 and stores the result in this quaternion.
 
 Example of use:
 @code
 ARQuaternion quaternion = [ARQuaternion quaternionWithDegrees:90 axisX:1.0 y:0.0 z:1.0];
 [quaternion localNormalise];
 @endcode
 
 @return This quaternion containing the normalised quaternion.
 */
- (ARQuaternion *)localNormalise;

/**
 Finds the inverse rotation of this quaternion and returns the result.
 This is useful for rotating something back to its original position.
 
 Example of use:
 @code
 ARQuaternion quaternion = [ARQuaternion quaternionWithDegrees:90 axisX:1.0 y:0.0 z:1.0];
 ARQuaternion inverseQuaternion = [quaternion inverse];
 @endcode
 
 @return A new ARQuaternion containing the inverse rotation of this quaternion.
 */
- (ARQuaternion *)inverse;

/**
 Finds the inverse rotation of this quaternion and stores the result in this quaternion.
 
 Example of use:
 @code
 ARQuaternion quaternion = [ARQuaternion quaternionWithDegrees:90 axisX:1.0 y:0.0 z:1.0];
 [quaternion inverse];
 @endcode
 
 @return This quaternion containing its inverse rotation.
 */
- (ARQuaternion *)localInverse;

/**
 Spherically interpolates between this quaternion and another given quaternion and returns the result.
 Slerp provides a "slow in" and "slow out" effect. Each step is not equidstant.
 When time = 0 this quaternion will be return. When time = 1 the given quaternion is returned. When time = 0.5 a rotation halfway between the two quaternions will be returned.
 Values below 0 or above 1 will return a larger rotation than either of the two.
 
 £xample of use:
 @code
 ARQuaternion quaternionOne = [ARQuaternion quaternionWithDegrees:90 axisX:1.0 y:0.0 z:1.0];
 ARQuaternion quaternionTwo = [ARQuaternion quaternionWithDegrees:45 axisX:0.0 y:1.0 z:0.0];
 ARQuaternion slerpQuaternion = [quaternionOne slerpToQuaternion:quaternionTwo atTime:0.5];
 @endcode
 
 @param quaternion The other quaternion to use for the interpolation calculation.
 @param time Represents a percentage of how much of a rotation between the two quaternions the result should represent.
 
 @return A new ARQuaternion representing a rotation between this quaternion and the given quaternion.
 */
- (ARQuaternion *)slerpToQuaternion:(ARQuaternion *)quaternion atTime:(float)time;

@end
