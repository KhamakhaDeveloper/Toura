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
@synthesize touraChatButton = _touraChatButton;

- (void)setupContent {
    [self setupTracableMarkers];
    [self setupGestureRecognizers];
    [self pulseEffect];
}


#pragma mark - Pulse Animation
-(void)pulseEffect{
    CABasicAnimation *theAnimation;
    theAnimation=[CABasicAnimation animationWithKeyPath:@"transform.scale"];
    theAnimation.duration=0.7;
    theAnimation.repeatCount= 20;
    theAnimation.autoreverses=YES;
    theAnimation.fromValue=[NSNumber numberWithFloat:1.5];
    theAnimation.toValue=[NSNumber numberWithFloat:0.7];
    theAnimation.timingFunction=[CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseIn];
    [self.touraChatButton.layer addAnimation:theAnimation forKey:@"animateOpacity"];
}
#pragma mark - Tracable Markers Method

// Doing it using multiple markers .KARMarker set

- (void)setupTracableMarkers {
    [TrackerSetup sharedManager];
}

- (void)setupGestureRecognizers {
    // Add gesture recognisers.
        dispatch_async(dispatch_get_main_queue(), ^{
        UIPinchGestureRecognizer *pinchGesture = [[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(nodePinch:)];
        [self.cameraView addGestureRecognizer:pinchGesture];
        
        UIPanGestureRecognizer *panGesture = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(nodePan:)];
        [self.cameraView addGestureRecognizer:panGesture];
        
        UITapGestureRecognizer *tapGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(nodeTap:)];
        [self.cameraView addGestureRecognizer:tapGesture];
    });
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

#pragma mark - IBAction Methods

- (IBAction)TouraBotButtonAction:(id)sender {
    [self performSegueWithIdentifier:@"TouraBot" sender:nil];
}

@end
