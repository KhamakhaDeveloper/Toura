//
//  AppDelegate.h
//  Toura
//
//  Created by Carpenter, Deepak (US - Bengaluru) on 02/12/17.
//  Copyright © 2017 TechMusketeers. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <ApiAI/ApiAI.h>


@interface AppDelegate : UIResponder <UIApplicationDelegate>
@property(nonatomic, strong) ApiAI *apiAI;
@property (strong, nonatomic) UIWindow *window;


@end

