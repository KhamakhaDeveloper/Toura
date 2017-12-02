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
@class PulseAnaimation;
@synthesize touraChatButton = _touraChatButton;

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // Do any additional setup after loading the view, typically from a nib.
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
