//
//  TARViewController.m
//  Toura
//
//  Created by Pairmi, Vikram (US - Bengaluru) on 12/2/17.
//  Copyright © 2017 TechMusketeers. All rights reserved.
//

#import "TARViewController.h"
#import "TrackerSetup.h"
#import "Constants.h"

@interface TARViewController ()<ImageTrackerDelegate> {
    
    float lastScale;
    float lastPanX;
}

@property (nonatomic) ARModelNode *modelNode;
//@property (nonatomic) ARImageTrackable *markerTracable;

@end

@implementation TARViewController

- (void)setupContent {
    [self setupTracableMarkers];
    [self setupGestureRecognizers];
}

#pragma mark - Tracable Markers Method

// Doing it using multiple markers .KARMarker set

- (void)setupTracableMarkers {
    TrackerSetup *trackerSetup = [[TrackerSetup alloc] init];
    [trackerSetup intialise];
}

- (void)setupGestureRecognizers {
    // Add gesture recognisers.
    UIPinchGestureRecognizer *pinchGesture = [[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(nodePinch:)];
    [self.cameraView addGestureRecognizer:pinchGesture];
    
    UIPanGestureRecognizer *panGesture = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(nodePan:)];
    [self.cameraView addGestureRecognizer:panGesture];
    
    UITapGestureRecognizer *tapGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(nodeTap:)];
    [self.cameraView addGestureRecognizer:tapGesture];
}


#pragma mark - AR Node Methods

- (void)addImageNode {
    
}

- (void)addModelNode {
    
}

- (void)addVideoNode {
    
}

- (void)addSignConversionNode {
    
}

- (void)addNavigationNode {
    
}

- (void)loadAppropriateARNode:(ARImageTrackable *)imageTrackable {
    
}

#pragma mark - Tracker Setup Delegate Methods

- (void)detectedTrackable:(ARImageTrackable *)imageTrackable {
    if ([imageTrackable.name isEqualToString:UDAIPUR_MARKER_NAME]) {
    }
}

#pragma mark - Gesture Recognizers

- (void)nodeTap:(UITapGestureRecognizer *)gesture {
    
}

- (void)nodePinch:(UIPinchGestureRecognizer *)gesture {
    float scaleFactor = gesture.scale;
    
    if (gesture.state == UIGestureRecognizerStateBegan) {
        lastScale = 1;
    }
    
    scaleFactor = lastScale - (lastScale - scaleFactor);
    
    lastScale = gesture.scale;
    
    @synchronized ([ARRenderer getInstance]) {
        [self.modelNode scaleByUniform:lastScale];
    }
}

- (void)nodePan:(UIPanGestureRecognizer *)gesture {
    float x = [gesture translationInView:self.cameraView].x;
    
    if (gesture.state == UIGestureRecognizerStateBegan) {
        lastPanX = x;
    }
    
    float diff = x - lastPanX;
    
    float deg = diff * 0.5;
    
    @synchronized ([ARRenderer getInstance]) {
        [self.modelNode rotateByDegrees:deg axisX:0 y:1 z:0];
    }
}

@end
