#import <Foundation/Foundation.h>
#import <CoreMotion/CoreMotion.h>
#import "ARRenderer.h"

@class ARWorld;
@class ARQuaternion;

/**
 A delegate for events relating to the Gyro Manager.
 Add this as a delegate to be notified when the gyroscope has been initialised and started.
 */
@protocol ARGyroManagerDelegate  <NSObject>

@required
@optional

/**
 Delegate method that notifies delegates when the gyro has started and has values.
 */
- (void)gyroStarted;

@end

/**
 A manager class representing the device's gyro. This class is resposible for using IMU data to transform AR content with device rotations.
 */
@interface ARGyroManager : NSObject <ARRendererDelegate>

/**
 Gets the instance of the gyro manager singleton.
 
 Example of use:
 @code
 ARGyroManager *gyroManager = [ARGyroManager getInstance];
 @endcode
 
 @return The singleton instance.
 */
+ (ARGyroManager *)getInstance;

/**
 Enum representing the gyro's state.
 */
typedef enum {
    /**
     Gyro Manager has been initialised.
     */
    ARGyroManagerStateInitialised,
    
    /**
     Gyro has stopped running.
     */
    ARGyroManagerStateStopped,
    
    /**
     Gyro is running.
     */
    ARGyroManagerStateStarted,
} ARGyroManagerState;

/**
 The gyro manager's current state.
 */
@property (nonatomic) ARGyroManagerState gyroState;

/**
 Enum representing the gyro managers internal state.
 */
typedef enum {
    /**
     Gyro Manager has been initialised.
     */
    ARGyroManagerStateInternalInitialised,
    
    /**
     Gyro has stopped running.
     */
    ARGyroManagerStateInternalStopped,
    
    /**
     Gyro is running.
     */
    ARGyroManagerStateInternalStarted,
} ARGyroManagerStateInternal;

/**
 The gyro managers current internal state
 */
@property (nonatomic) ARGyroManagerStateInternal internalGyroState;

/**
 The motion manager used to update the ARGyroManager's orientation.
 */
@property (nonatomic, readonly) CMMotionManager *motionManager;

/**
 The reference frame used to start the motion manager. Default is CMAttitudeReferenceFrameXTrueNorthZVertical.
 */
@property (nonatomic) CMAttitudeReferenceFrame gyroReferenceFrame;

/**
 A node representing the ARGyroManager's world.
 **/
@property (nonatomic) ARWorld *world;

/**
 Initialises the ARGyroManager singleton and the ARCMMotionManger singleton with a default gyro update interval of 0.05 seconds.
 */
- (void)initialise;

/**
 Deinitialises the ARGyroManager singleton and dereferences CMMotiionManger.
 */
- (void)deinitialise;

/**
 Sets the gyro state to ARGyroManagerStateInitialised, starts device motion updates and adds ARGyroManager to the array of ARRenderDelegates.
 */
- (void)start;
/**
 Sets the gyro state to ARGyroManagerStateStopped, stops device motion updates and removes ARGyroManager from the array of ARRenderDelegates.
 */
- (void)stop;

- (void)actualStart;
- (void)actualStop;

/**
 Updates the world node by getting a 3x3 rotation matrix from the gyroscope attitude, rotating it so that its axes match the camera's, and applying it to the orientation of the Gyro Manager's world.
 */
- (void)updateNode;

/**
 Add a delegate for gyro event notifications.
 
 @param delegate The delegate to add to the Gyro Manager.
 */
- (void)addDelegate:(id <ARGyroManagerDelegate>)delegate;

/**
 Remove a delegate for gyro event notifications.
 
 @param delegate The delegate to remove from the Gyro Manager.
 */
- (void)removeDelegate:(id <ARGyroManagerDelegate>)delegate;

@end
