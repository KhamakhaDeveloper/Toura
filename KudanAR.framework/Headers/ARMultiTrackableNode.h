#import <KudanAR/ARNode.h>

@class ARImageTrackable;

/**
 An ARMultiTrackableNode is a type of ARNode that dynamically changes which world it is a child of.
 This allows a single node to be displayed across different worlds at different times.
 
 It is useful when one piece of content needs to be displayed across numerous trackables, as that content can be reused, and does not need to be created more than once.
 
 An ARMultiTrackableNode cannot be used to display content on multiple trackables at the same time.
 When a trackable is detected, this node changes its world. That means that detecting two trackables will simply make it change its world to the one that was detected last.
 */
@interface ARMultiTrackableNode : ARNode

/**
 The array of all trackables this node follows.
 */
@property (nonatomic) NSArray *trackables;

/**
 Adds a trackable to the array of trackables that this node will attach itself to when detected.
 This method adds one trackable at a time.

 Example of use:
 @code
 ARImageTrackable *trackable1 = [[ARImageTrackable alloc] initWithBundledFile:@"example1.jpg"];
 ARImageTrackable *trackable2 = [[ARImageTrackable alloc] initWithBundledFile:@"example2.jpg"];
 ARMultiTrackableNode *multiNode = [[ARMultiTrackableNode alloc] init];
 [multiNode addTrackable:trackable1];
 [multiNode addTrackable:trackable2];
 @endcode
 
 @param trackable The trackable to add.
 */
- (void)addTrackable:(ARImageTrackable *)trackable;

/**
 Removes a trackable from the array of trackables and no longer reparents itself to it once detected.
 This method removes one trackable at a time.

 Example of use:
 @code
 [multiNode removeTrackable:trackable2];
 @endcode
 
 @param trackable The trackable to remove.
 */
- (void)removeTrackable:(ARImageTrackable *)trackable;

@end
