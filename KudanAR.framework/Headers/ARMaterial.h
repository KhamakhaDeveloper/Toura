#import <Foundation/Foundation.h>
#import <KudanAR/ARRenderer.h>

@class ARNode;

/**
 An ARMaterial represents a basic material system. 
 It enhances the realism of meshes by applying extra properties to it.
 It can be attached to an ARMeshNode to provide the parameters and contexual information to a shader, which allows it to correctly render a mesh node.
 
 This serves as a base class and shouldn't be created directly.
 */
@interface ARMaterial : NSObject

/**
 The name of this material. 
 This is automatically set during the model import process.
 **/
@property (nonatomic) NSString *name;

/**
 Whether this material has any alpha transparency. Default is NO.
 */
@property (nonatomic) BOOL isTranslucent;

/**
 The blend mode to use with this material. 
 If transparency is enabled, the ARBlendMode will control how the renderer blends the object it is drawing with the framebuffer, based on its alpha value.
 */
@property (nonatomic) ARBlendMode blendMode;

/**
 Whether pixels rendered with this material should be depth tested against existing pixels in the framebuffer. Default is YES.
 */
@property (nonatomic) BOOL depthTest;

/**
 Whether pixels rendered with this material should generate depth information in the framebuffer. Default is YES.
 */
@property (nonatomic) BOOL depthWrite;

/**
 Whether to write to the colour buffer. If NO, only depth information will be written. Default is YES.
 */
@property (nonatomic) BOOL colourWrite;

/**
 The type of face culling this material uses. This determines which faces are considered non-visible and are subsequently not drawn by the renderer. Default is ARFaceCullModeBack.
 */
@property (nonatomic) ARFaceCullMode cullMode;

/**
 Method called after this material has been used to render an object. This can be useful for playable textures if you wish to check their updated state.
 */
- (void)postRender;

@end
