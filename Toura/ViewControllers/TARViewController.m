//
//  TARViewController.m
//  Toura
//
//  Created by Pairmi, Vikram (US - Bengaluru) on 12/2/17.
//  Copyright © 2017 TechMusketeers. All rights reserved.
//

#import "TARViewController.h"
#import "TrackerSetup.h"
#import "MarkerInfoViewController.h"
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
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [self setupGestureRecognizers];
        [self pulseEffect];
    });
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
    self.touraChatButton.layer.cornerRadius = 20.0f;
    self.touraChatButton.layer.masksToBounds = YES;
    [self.touraChatButton.layer addAnimation:theAnimation forKey:@"animateOpacity"];
}
#pragma mark - Tracable Markers Method

// Doing it using multiple markers .KARMarker set

- (void)setupTracableMarkers {
    TrackerSetup *l_TrackerSetup = [TrackerSetup sharedManager];
    [l_TrackerSetup setDelegate:self];
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

- (void)addModelNode:(ARImageTrackable *)imageTrackable isVisible:(BOOL )isVisible {
    
    if (isVisible) {
        // Import the model.
        ARModelImporter *importer = [[ARModelImporter alloc] initWithBundled:@"Castle.armodel"];
        
        // Get a node representing the model's contents.
        ARModelNode *modelNode = [importer getNode];
        
        // Create the model texture from a UIImage.
        ARTexture *modelTexture = [[ARTexture alloc] initWithUIImage:[UIImage imageNamed:@"texture.png"]];
        
        // Create a textured material using the texture.
        ARTextureMaterial *textureMaterial = [[ARTextureMaterial alloc] initWithTexture:modelTexture];
        
        // Assign textureMaterial to every mesh in the model.
        for (ARMeshNode *meshNode in modelNode.meshNodes) {
            
            meshNode.material = textureMaterial;
        }
        
        // Modelled with y-axis up. Marker has z-axis up. Rotate around the x-axis to correct this.
        [modelNode rotateByDegrees:90 axisX:1 y:0 z:0];
        [modelNode scaleByUniform:20];
        
        // Add the model to a marker.
        [imageTrackable.world addChild:modelNode];
        
        self.modelNode = modelNode;
    }else {
        [imageTrackable.world removeChild:self.modelNode];
    }
}

- (void)addVideoNode:(ARImageTrackable *)imageTrackable {
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
        [self showMarkerInfo:imageTrackable];
    }else if ([imageTrackable.name isEqualToString:@"fortModel"]){
        [self addModelNode:imageTrackable isVisible:YES];
    }
}

- (void)lostTrackable:(ARImageTrackable *)imageTrackable {
    if ([imageTrackable.name isEqualToString:UDAIPUR_MARKER_NAME]) {
        [self showMarkerInfo:imageTrackable];
    }else if ([imageTrackable.name isEqualToString:@"fortModel"]){
        [self addModelNode:imageTrackable isVisible:NO];
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

//test

- (void)showMarkerInfo:(ARImageTrackable *)imageTrackable {
    
    MarkerInfoViewController *markerInfo = [self.storyboard instantiateViewControllerWithIdentifier:@"MarkerInfoViewController"];
    UIGraphicsBeginImageContextWithOptions(markerInfo.view.frame.size, markerInfo.view.opaque, 0.0);
    [markerInfo.view.layer renderInContext:UIGraphicsGetCurrentContext()];
    
    UIImage *img = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    [self saveImage:img];
    
    // Initialise image node
    ARImageNode *imageNode = [[ARImageNode alloc] initWithImage:[self getImage]];
    
    
    // Add image node to image trackable
    [imageTrackable.world addChild:imageNode];
    
    // Image scale
    float scale = (float)imageTrackable.width / imageNode.texture.width;
    [imageNode rotateByDegrees:25 axisX:1.0 y:0.0 z:0.0];
    [imageNode scaleByUniform:1.0];
    
    // Hide image node
    [imageNode setVisible:YES];
    
}

- (void)saveImage:(UIImage *)_postImage {
    // For error information
    NSError *error;
    NSFileManager *fileMgr = [NSFileManager defaultManager];
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0]; // Get documents folder
    NSString *dataPath = [documentsDirectory stringByAppendingPathComponent:@"/YOUR_IMG_FOLDER"];
    
    if (![fileMgr fileExistsAtPath:dataPath])
        [[NSFileManager defaultManager] createDirectoryAtPath:dataPath withIntermediateDirectories:NO attributes:nil error:&error]; //Create folder
    
    //    //Get the current date and time and set as image name
    //    NSDate *now = [NSDate date];
    //
    //    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    //    dateFormatter.dateFormat = @"yyyy-MM-dd_HH-mm-ss";
    //    [dateFormatter setTimeZone:[NSTimeZone systemTimeZone]];
    //    NSString *gmtTime = [dateFormatter stringFromDate:now];
    //    NSLog(@"The Current Time is :%@", gmtTime);
    
    NSData *imageData = UIImageJPEGRepresentation(_postImage, 0.5); // _postImage is your image file and you can use JPEG representation or PNG as your wish
    int imgSize = imageData.length;
    ////NSLog(@"SIZE OF IMAGE: %.2f Kb", (float)imgSize/1024);
    
    //NSString *imgfileName = [NSString stringWithFormat:@"%@%@", gmtTime, @".jpg"];
    
    NSString *imgfileName = [NSString stringWithFormat:@"markerInfo.jpg"];
    
    // File we want to create in the documents directory
    NSString *imgfilePath= [dataPath stringByAppendingPathComponent:imgfileName];
    // Write the file
    [imageData writeToFile:imgfilePath atomically:YES];
}

- (UIImage *)getImage {
    //Get image file from sand box using file name and file path
    NSString *stringPath = [[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)objectAtIndex:0]stringByAppendingPathComponent:@"YOUR_IMG_FOLDER"];
    stringPath  = [stringPath stringByAppendingPathComponent:@"markerInfo.jpg"]; // imgFile to get from your array, where you saved those image file names
    return [UIImage imageWithContentsOfFile:stringPath];
}

@end
