#import <Foundation/Foundation.h>
#import "ARGyroManager.h"

@class ARNode;

/**
 A delegate for events relating to the ArbiTracker.
 Add this as a delegate to be notified when the ArbiTracker starts and has values.
 */
@protocol ARArbiTrackerManagerDelegate <NSObject>

@required
@optional

/**
 Delegate method that notifies delegates when ArbiTrack has started and has valid values. The gyro can take a few frames to get started.
 Using this ensures you don't get uninitialised values when fetching the ArbiTracker's world orientation.
 **/
- (void)arbiTrackStarted;

@end

/**
 Manager singleton for The ArbiTracker.
 This tracker is used for markerless tracking. 
 Add content to this tracker's world in order to track it without a marker.
 
 For more information on how to set up the ArbiTracker, check out our ArbiTrack Basics wiki page at https://wiki.kudan.eu/ArbiTrack_Basics_iOS
 */
@interface ARArbiTrackerManager : NSObject <ARGyroManagerDelegate>

/**
 The node whose transformation will be used when the ArbiTracker is started. Position this to determine the initial transformation of the ArbiTracker's world when ArbiTrack begins, and to define the coordinate space.
 In order to move the targetNode in relation to the gyroscope, add it as a child of the Gyro Place Manager's world. It will then automatically change its position based on the orientation of the device.
 It can also be added to an ARImageTrackable's world for the purposes of starting ArbiTrack using an Image Trackable's position and orientation.
 */
@property (nonatomic) ARNode *targetNode;

/**
 When the ArbiTracker is tracking, its world node's transformation is updated by the tracker each frame. Add content to this node in order to track it using ArbiTrack.
 */
@property (nonatomic) ARNode *world;

/**
 Whether or not the ArbiTracker is currently tracking.
 
 If YES, the tracker will update each frame.
 If NO, the tracker will not update each frame.
 
 This is set automatically by the tracker.
 */
@property (nonatomic) BOOL isTracking;

/**
 The absolute minimum number of feature points that need to be tracked in any given frame. 
 If the number of tracked feature points drops below this threshold, tracking is automatically stopped.
 Ordinarily around 100 features are tracked in any given frame.
 Default value is 20.
 
 Increasing this value ensures that only high-feature environments can be tracked.
 Decreasing this value forces tracking to continue in low-feature environments.
 */
@property (nonatomic) int minimumFeatureCount;

/**
 Whether or not the tracker has been initialised.
 
 If YES, the tracker will process new frames.
 If NO, the tracker will not process new frames.
 
 This is set automatically by the tracker.
 */
@property (nonatomic) BOOL isInitialised;

/**
 Gets the ArbiTracker singleton. The first time this is called, a new ARNode called "ArbiTrack" will be created to be the ArbiTracker's world.
 
 Example of use:
 @code
 ARArbiTrackerManager *arbiTrackerManager = [ARArbiTrackerManager getInstance];
 @endcode
 
 @return The ArbiTracker singleton.
 */
+ (ARArbiTrackerManager *)getInstance;

/**
 Initialises both the ArbiTracker and the Gyro Manager. This method should only be called once during setup.
 When the ArbiTacker is initialised, it performs the following:
 * A new ARNode is created to become the ArbiTracker's world.
 * A reference to the native ArbiTracker interface is made and the the interface is initialised.
 * An empty array of delegates is created.
 * A reference to the Gyro Manager is made and it is initialised.
 * The ArbiTracker is added as a delegate for the Gyro Manager.
 Note: This does NOT initialise the Gyro Place Manager, which is separate to the Gyro Manager. It must be initialised separately.
 
 Example of use:
 @code
 [[ARArbiTrackerManager getInstance] initialise];
 @endcode
 */
- (void)initialise;

/**
 Deinitialise the ArbiTracker. This method should only be called once during cleanup, ideally when the AR View Controller is being dismissed.
 When the ArbiTracker is deinitialised, it performs the following:
 * The native ArbiTracker interface is deinitialised.
 * The target node is emptied and assigned nil.
 * The ArbiTracker's world is reset with a new ARNode.
 
 Example of use:
 @code
 [[ARArbiTrackerManager getInstance] deinitialise];
 @endcode
 */
- (void)deinitialise;

/**
 Passes Camera data to KudanCV for processing. Called every frame the tracker is running.
 @param data Camera data.
 @param width Camera width.
 @param height Camera height.
 @param padding Camera padding.
 **/
- (void)process:(NSData *)data width:(int)width height:(int)height padding:(int)padding;

/**
 Start the ArbiTracker. The targetNode's transformation at this time is used to determine the initial pose of the tracker. The ArbiTracker must have first been initialised before starting, or it will not work.
 
 Example of use:
 @code
 [[ARArbiTrackerManager getInstance] start];
 @endcode
 */
- (void)start;

/**
 Stop the ArbiTracker. Any nodes being rendered will stop rendering at this time.
 
 Example of use:
 @code
 [[ARArbiTrackerManager getInstance] stop];
 @endcode
 */
- (void)stop;

/**
 Add a delegate for rendering event notifications.
 
 Example of use:
 @code
 [[ARArbiTrackerManager getInstance] addDelegate:self];
 @endcode
 
 @param delegate The delegate to add.
 */
- (void)addDelegate:(id <ARArbiTrackerManagerDelegate >)delegate;

/**
 Remove a delegate for rendering event notifications.
 
 Example of use:
 @code
 [[ARArbiTrackerManager getInstance] removeDelegate:self];
 @endcode

 @param delegate The delegate to remove.
 */
- (void)removeDelegate:(id <ARArbiTrackerManagerDelegate >)delegate;

@end
