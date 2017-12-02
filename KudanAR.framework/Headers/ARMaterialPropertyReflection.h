#import <Foundation/Foundation.h>

@class ARMaterialProperty;
@class ARTextureCube;

/**
 ARMaterialPropertyReflection is a class used by ARLightMaterial to simulate reflection of a material.
 **/
@interface ARMaterialPropertyReflection : NSObject

//@property (nonatomic) ARMaterialProperty *reflectivity;

/**
 The reflectivity ratio in range 0..1.
 This represents how reflective the material is. 
    - A value of 0 would mean no reflection.
    - A value of 1 would mean complete reflection, no light is absorbed.
    - Values within this range represent partial reflection. This is good for simulating real-life reflective surfaces, such as mirrors.
 **/
@property (nonatomic) float reflectivity;

/**
 A texture cube that simulates the environment surrounding the material. A map must be assigned for reflection to occur.
 **/
@property (nonatomic) ARTextureCube *environment;

@end
