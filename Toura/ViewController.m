//
//  ViewController.m
//  Toura
//
//  Created by Carpenter, Deepak (US - Bengaluru) on 02/12/17.
//  Copyright © 2017 TechMusketeers. All rights reserved.
//

#import "ViewController.h"
@interface ViewController ()

@end

@implementation ViewController
@synthesize touraChatButton = _touraChatButton;

- (void)viewDidLoad {
    [super viewDidLoad];
    [self pulseEffect];
    // Do any additional setup after loading the view, typically from a nib.
}

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

-(void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:YES];
    UIApplication.sharedApplication.statusBarStyle = UIStatusBarStyleDefault;
}



- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)TouraBotButtonAction:(id)sender {
    [self performSegueWithIdentifier:@"TouraBot" sender:nil];
}


@end
