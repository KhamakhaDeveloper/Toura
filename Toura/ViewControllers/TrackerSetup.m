//
//  TrackerSetupViewController.m
//  Toura
//
//  Created by Pairmi, Vikram (US - Bengaluru) on 12/2/17.
//  Copyright © 2017 TechMusketeers. All rights reserved.
//

#import "TrackerSetup.h"
#import "Constants.h"

@interface TrackerSetup ()

@end

@implementation TrackerSetup

- (void)intialise{
    [self setupTrackableContent];
}

- (void)setupTrackableContent {
    //Setup imageTrackableSet
    NSString *filePath = [[[NSBundle mainBundle] resourcePath] stringByAppendingString:@"udaipur.KARMarker"];
    ARImageTrackableSet *imageTrackableSet = [[ARImageTrackableSet alloc] initWithBundledFile:filePath];
    
    //Setup TrackerManager
    ARImageTrackerManager *imageTrackerManaer = [ARImageTrackerManager getInstance];
    [imageTrackerManaer initialise];
    [imageTrackerManaer toggleParallelDetection:YES];
    [imageTrackerManaer setMaximumSimultaneousTracking:10];
    
    [imageTrackerManaer addTrackableSet:imageTrackableSet];
    
    //Setup Gesture recognizers
    for (ARImageTrackable *imageTrackable in imageTrackableSet.trackables) {
        
        imageTrackable.name = UDAIPUR_MARKER_NAME;
        
        [imageTrackable addTrackingEventTarget:self action:@selector(trackerDetected:) forEvent:ARImageTrackableEventDetected];
        [imageTrackable addTrackingEventTarget:self action:@selector(trackerLost:) forEvent:ARImageTrackableEventLost];
    }
}

#pragma mark - Event detection methods

- (void)trackerDetected:(ARImageTrackable *)imageTrackable {
    // Initialise image node
    ARImageNode *imageNode = [[ARImageNode alloc] initWithBundledFile:@"overlay.png"];
    
    // Add image node to image trackable
    [imageTrackable.world addChild:imageNode];
    
    // Image scale
    float scale = (float)imageTrackable.width / imageNode.texture.width;
    [imageNode rotateByDegrees:0 axisX:0.0 y:1.0 z:0.0];
    [imageNode scaleByUniform:scale];
    
    // Hide image node
    [imageNode setVisible:YES];
    
    [self.delegate detectedTrackable:imageTrackable];
}

- (void)trackerLost:(ARImageTrackable *)imageTrackable {
    
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
