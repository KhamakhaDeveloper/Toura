#import <Foundation/Foundation.h>

@class ARVector3;
@class ARVector4;
@class ARQuaternion;

/**
 An ARMatrix4 is a math class that represents a 4x4 Matrix.
 The methods in this class both create new transformation matrices using given data and perform matrix calculations.
 */
@interface ARMatrix4 : NSObject <NSCoding>

/**
 Creates a new 4x4 identity matrix.
 
 Example of use:
 @code
 ARMatrix4 matrix = [ARMatrix4 matrixWithIdentity];
 @endcode
 
 @return A 4x4 Identity Matrix.
 */
+ (ARMatrix4 *)matrixWithIdentity;

/**
 Creates a new m4x4 matrix with the given array of values. This will be a matrix with the column major order.
 
 Example of use:
 @code
 ARMatrix4 matrix = [ARMatrix4 matrixWithValues:values];
 @endcode
 
 @param values The array of float values to initialise the matrix with.
 
 @return A 4x4 Transformation Matrix with the given values.
 */
+ (ARMatrix4 *)matrixWithValues:(float *)values;

/**
 Creates a new 4x4 transformation matrix with the given parameters.
 
 Example of use:
 @code
 ARVector3 translation = [ARVector3 vectorWithValuesX:1.0 y:2.0 z:3.0];
 ARQuaternion = + [ARQuaternion quaternionWithDegrees:45.0 axisX:1.0 y:1.0 z:1.0];
 ARVector3 scale = [ARVector3 vectorWithValuesX:2.0 y:4.0 z:6.0];
 ARMatrix4 matrix = [ARMatrix4 matrixWithTranslation:translation rotation:rotation scale:scale];
 @endcode
 
 @param translation The translation to use in the transformation matrix.
 @param rotation The rotation to use in the transformation matrix.
 @param scale The scale to use in the transformation matrix.
 
 @return A 4x4 Transformation Matrix with the given translation, rotation and scale.
 */
+ (ARMatrix4 *)matrixWithTranslation:(ARVector3 *)translation rotation:(ARQuaternion *)rotation scale:(ARVector3 *)scale;

/**
 Creates a new 4x4 perspective matrix with the given field-of-view, aspect ratio, near plane distance, far plane distance and zoom paramaters. 
 This represents a frustum extending out from the centre of the camera view.
 
 Example of use:
 @code
 ARMatrix4 matrix = [ARMatrix4 frustumWithFOV:70.0 aspect:1.67 near:3.0 far:20.0 zoom:1.0];
 @endcode
 
 @param fov The "field of view" of this perspective matrix, representing the vertical angle of the camera through which we are looking at the world.
 @param aspect The "aspect ratio" between the width and the height of the rectangular area which will be the target of projection. For example, a 16:9 aspect ratio would be ~1.78.
 @param near The "near clipping plane" of this perspective matrix. Objects nearer to the camera than the near plane will not be rendered.
 @param far The "far clipping plane" of this perspective matrix. Objects further away from the camera than the far plane will not be rendered.
 @param zoom An artificial "zoom" factor separate from the FOV. Useful for creating special effects like a Dolly zoom.
 
 @return A 4x4 Perspective Matrix using the given parameters.
 */
+ (ARMatrix4 *)frustumWithFOV:(float)fov aspect:(float)aspect near:(float)near far:(float)far zoom:(float)zoom;

/**
 Creates a new 4x4 perspective matrix with the given plane distances. 
 This represents a frustum extending out from the centre of the camera view.
 
 Example of use:
 @code
 ARMatrix4 matrix = [ARMatrix4 frustumWithLeft:30.0 right:30.0 bottom:15.0 top:15.0 near:3.0 far:20.0];
 @endcode
 
 @param left How far the left-hand plane is from the centre of the camera view. Used to calculate the horizontal field of view and the aspect ratio.
 @param right How far the right-hand plane is from the centre of the camera view. Used to calculate the horizontal field of view and the aspect ratio.
 @param bottom How far the bottom plane is from the centre of the camera view. Used to calculate the vertical field of view and the aspect ratio.
 @param top How far the top plane is from the centre of the camera view. Used to calculate the vertical field of view and the aspect ratio.
 @param near How far the near plane is from the camera. Used to determine how close to the camera an object can be before it is clipped.
 @param far How far the far plane is form the camera. Used to determine how far away from the camera an object can be before it is clipped.
 
 @return A 4x4 Perspective Matrix calculated using the given parameters.
 */
+ (ARMatrix4 *)frustumWithLeft:(float)left right:(float)right bottom:(float)bottom top:(float)top near:(float)near far:(float)far;

/**
 Creates a new 4x4 orthographic with the given plane distances. 
 This represents a box with the minimum corner at (left, bottom, -near) and the maximum corner at (right, top, -far).
 
 Example of use:
 @code
 ARMatrix4 matrix = [ARMatrix4 orthoWithLeft:20.0 right:20.0 bottom:10.0 top:10.0 near:2.0 far:25.0];
 @endcode
 
 @param left How far the left-hand plane is from the centre of the bounding box.
 @param right How far the right-hand plane is from the centre of the bounding box.
 @param bottom How far the bottom plane is from the centre of the bounding box.
 @param top How far the top plane is from the centre of the bounding box.
 @param near How far the near plane is from the camera. Used to determine how close to the camera an object can be before it is clipped.
 @param far How far the far plane is form the camera. Used to determine how far away from the camera an object can be before it is clipped.
 
 @return A 4x4 Orthogonal Matrix with the given dimensions.
 */
+ (ARMatrix4 *)orthoWithLeft:(float)left right:(float)right bottom:(float)bottom top:(float)top near:(float)near far:(float)far;

/**
 Multiplies this matrix by another 4x4 matrix and returns the result as a new matrix. This matrix will the LHS, the other matrix will be the RHS.
 
 Example of use:
 @code
 ARMatrix4 newMatrix = [oldMatrix multiplyByMatrix:otherMatrix];
 @endcode
 
 @param matrix The 4x4 matrix to multiply this matrix by.
 
 @return A 4x4 Matrix containing the result of multiplying this matrix by another given matrix.
 */
- (ARMatrix4 *)multiplyByMatrix:(ARMatrix4 *)matrix;

/**
 Multiplies this matrix by another 4x4 matrix and assigns the result to this matrix.
 
 Example of use:
 @code
 [oldMatrix localMultiplyByMatrix:otherMatrix];
 @endcode
 
 @param matrix The 4x4 matrix to multiply this matrix by.
 
 @return A 4x4 Matrix containing the result of multiplying this matrix by another given matrix.
 */
- (ARMatrix4 *)localMultiplyByMatrix:(ARMatrix4 *)matrix;

/**
 Multiplies this matrix by a Vector3 and returns the result as a new Vector3.
 
 Example of use:
 @code
 ARVector3 newVector = [matrix multiplyByVector:otherVector];
 @endcode
 
 @param vector The vector (X, Y, Z) to multiply this matrix by.
 
 @return An ARVector3 containing the result of multiplying this matrix by the given vector.
 */
- (ARVector3 *)multiplyByVector:(ARVector3 *)vector;

/**
 Multiplies this matrix by a Vector3 and assigns the result to the passed vector.
 
 Example of use:
 @code
 [matrix localMultiplyByVector:otherVector];
 @endcode
 
 @param vector The vector (X, Y, Z) to multiply this matrix by.
 
 @return An ARVector3 containing the result of multiplying this matrix by the given vector.
 */
- (ARVector3 *)localMultiplyByVector:(ARVector3 *)vector;

/**
 Multiplies this matrix by a Vector4 and returns the result as a new Vector4.
 
 Example of use:
 @code
 ARVector4 newVector = [matrix multiplyByVector4:otherVector];
 @endcode
 
 @param vector The vector (X, Y, Z, W) to multiply this matrix by.
 
 @return An ARVector4 containing the result of multiplying this matrix by the given vector.
 */
- (ARVector4 *)multiplyByVector4:(ARVector4 *)vector;

/**
 Multiplies this matrix by a Vector4 and assigns the result to the passed vector.
 
 Example of use:
 @code
 [matrix localMultipleByVector4:otherVector];
 @endcode
 
 @param vector The vector (X, Y, Z, W) to multiply this matrix by.
 
 @return An ARVector4 containing the result of multiplying this matrix by the given vector.
 */
- (ARVector4 *)localMultiplyByVector4:(ARVector4 *)vector;

/**
 Transposes this matrix and returns the result as a new 4x4 matrix.
 
 Example of use:
 @code
 ARMatrix4 transposedMatrix = [matrix transpose];
 @endcode
 
 @return A 4x4 Matrix containing the transpose of this matrix.
 */
- (ARMatrix4 *)transpose;

/**
 Transposes this  matrix and assigns the result to this matrix.
 
 Example of use:
 @code
 [matrix localTranspose];
 @endcode
 
 @return A 4x4 Matrix containing the transpose of this matrix.
 */
- (ARMatrix4 *)localTranspose;

/**
 Calculates the inverse of this matrix and returns the result as a new 4x4 matrix.
 
 Example of use:
 @code
 ARMatrix4 inverseMatrix = [matrix inverse];
 @endcode
 
 @return A 4x4 matrix containing the inverse of this matrix.
 */
- (ARMatrix4 *)inverse;

/**
 Calculates the inverse of this matrix and assigns the result to this matrix.
 
 Example of use:
 @code
 [matrix localInverse];
 @endcode
 
 @return A 4x4 matrix containing the inverse of this matrix.
 */
- (ARMatrix4 *)localInverse;

/**
 Creates a float array representing a 4x4 transformation matrix for use by OpenGL as a buffer using a given set of floats.
 This method assigns to the parameter passed to it.
 
 The data expected by OpenGL is different to that of a standard transformation matrix. As such, it must be converted.
 
 Example of use:
 @code
 ARMatrix4 *matrix = [ARMatrix4 matrixWithIdentity];
 
 float result[16];
 
 [matrix makeGLMatrix:result];
 @endcode
 
 @param matrix An array of floats to convert to a transformation matrix.
 
 @return An array of 16 floats representing a 4x4 transformation matrix.
 */
- (float *)makeGLMatrix:(float *)matrix;

/**
 Creates a float array representing a 3x3 rotation matrix for use by OpenGL as a buffer using a given set of floats.
 This method assigns to the paramater passed to it.
 
 Example of use:
 @code
 ARMatrix4 matrix = [ARMatrix4 matrixWithIdentity];
 
 float result[16];
 
 [matrix makeGLRotationMatrix:result];
 @endcode
 
 @param matrix An array of floats to convert to a rotation matrix.
 
 @return An array of 9 floats representing a 3x3 rotation matrix.
 */
- (float *)makeGLRotationMatrix:(float *)matrix;

/**
 Returns the scale component of this transformation matrix.
 
 Example of use:
 @code
 ARVector3 scaleOfMatrix = [matrix scale];
 @endcode
 
 @return An ARVector3 containing the scale of this matrix.
 */
- (ARVector3 *)scale;

/**
 Returns the translation component of this transformation matrix.
 
 Example of use:
 @code
 ARVector3 translationOfMatrix = [matrix translation];
 @endcode
 
 @return An ARVector3 containing the translation of this matrix.
 */
- (ARVector3 *)translation;

/**
 Returns the rotation component of this transformation matrix.
 
 Example of use:
 @code
 ARQuaternion rotationOfMatrix = [matrix orientation];
 @endcode
 
 @return An ARQuaternion containing the rotation of this matrix.
 */
- (ARQuaternion *)orientation;

@end
