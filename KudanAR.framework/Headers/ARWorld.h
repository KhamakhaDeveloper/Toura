#import <Foundation/Foundation.h>
#import <KudanAR/ARNode.h>

/**
 A node representing the concept of a world.
 Every image trackable has its own world. ARGyroManager and ARGyroPlaceManager also have their own worlds. These represent the coordinate frames of these specific objects.
 This allows content to be placed relative to the positions of these worlds and move with these worlds, rather than everything being placed relative to the camera.
 
 An ARWorld has special meaning for reflection maps, which are calculated in world space. This means that the environment map is aligned with the nearest descending ARWorld in the scenegraph.
 */
@interface ARWorld : ARNode

@end
