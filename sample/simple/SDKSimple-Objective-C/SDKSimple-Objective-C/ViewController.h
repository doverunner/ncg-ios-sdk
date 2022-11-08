//
//  ViewController.h
//  SDKSimple-Objective-C
//
//  Created by PallyCon on 2018. 8. 28..
//  Copyright © 2018년 INKA Entworks. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <AVKit/AVKit.h>
#import <iOSNcgSDK/iOSNcgSDK.h>

@interface ViewController : UIViewController<WebServerDelegate>

@property (strong, nonatomic) Ncg2Agent * ncg2agent;
@property (strong, nonatomic) AVPlayerViewController *playerViewController;

@end

