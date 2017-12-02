#import <Foundation/Foundation.h>
#import <KudanAR/ARColourMaterial.h>

/**
 This material type can be rendered with an ARMeshNode object to achieve an occlusion effect, where the alpha of the material is dynamically altered depending on its depth.
 This gives the appearance of models or images moving behind, under or around real-world objects, improving the level of immersion in the scene.
 */
@interface AROcclusionMaterial : ARColourMaterial


@end
