//
//  TrackerSetupViewController.h
//  Toura
//
//  Created by Pairmi, Vikram (US - Bengaluru) on 12/2/17.
//  Copyright © 2017 TechMusketeers. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <KudanAR/KudanAR.h>

@protocol ImageTrackerDelegate

@required
- (void)detectedTrackable:(ARImageTrackable *)imageTrackable;
- (void)lostTrackable:(ARImageTrackable *)imageTrackable;

@end

@interface TrackerSetup : NSObject

//properties
@property(nonatomic, weak) id<ImageTrackerDelegate>delegate;

//Instance methods
+ (id)sharedManager;

@end
