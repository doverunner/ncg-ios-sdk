//
//  ViewController.m
//  SDKSimple-Objective-C
//
//  Created by PallyCon on 2018. 8. 28..
//  Copyright © 2018년 INKA Entworks. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

static NSString * const CONTENT_URL = @"https://contents.pallycon.com/TEST/PACKAGED_CONTENT/TEST_SIMPLE/sintel-trailer.mp4.ncg";
static NSString * const TOKEN = @"eyJrZXlfcm90YXRpb24iOmZhbHNlLCJyZXNwb25zZV9mb3JtYXQiOiJvcmlnaW5hbCIsInVzZXJfaWQiOiJ1dGVzdCIsImRybV90eXBlIjoibmNnIiwic2l0ZV9pZCI6IkRFTU8iLCJoYXNoIjoiK2prMVpOUUNNY0JRM2d3ZDl6UHNmZjh1eXJ4M2M3XC9CZUwxYmlYUTBDMHM9IiwiY2lkIjoiVGVzdFJ1bm5lciIsInBvbGljeSI6IjlXcUlXa2RocHhWR0s4UFNJWWNuSnNjdnVBOXN4Z3ViTHNkK2FqdVwvYm9tUVpQYnFJK3hhZVlmUW9jY2t2dUVmdUx0dlVMWXEwTnVoNVJaOFhGYzQ1RWxHd1dcLzY3WVhUcTJQSDJ4Z3dIR1hDalVuaUgzbDQ4NVNmcDZjbmV1bm5qdjMxeGt5VHd6VlAzdVhIUGJWNWR3PT0iLCJ0aW1lc3RhbXAiOiIyMDIwLTExLTE4VDA1OjU2OjEzWiJ9";

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    NSError * error = nil;
    // 1. Ncg2Agent Instance
    self.ncg2agent = [Ncg2Agent sharedInstance];
    // 2. initialize
    [self.ncg2agent initialize:OfflineSupportYes rodbPath:nil deviceId:nil error:&error];
    // 3. content license acqusition
    [self.ncg2agent acquireLicenseByToken:TOKEN isTemporary:NO error:&error];
    // 4. local web server delegate and start
    [self.ncg2agent.getLocalWebServerInstance setWebServerDelegate:self];
    [self.ncg2agent.getLocalWebServerInstance startWebserver:&error];
    // 5. Get a playback URL
    NSString* playUrl = [self.ncg2agent.getLocalWebServerInstance addProgressiveDownloadUrlForPlayback:CONTENT_URL error:&error];
    if(error != nil) {
        NSLog(@"Error : %ld", (long)error.code);
    }
    
    // AV Player
    self.playerViewController = [[AVPlayerViewController alloc] init];
    AVPlayer *player = [AVPlayer playerWithURL:[NSURL URLWithString:playUrl]];
    self.playerViewController.player = player;
    [self.playerViewController.view setFrame:CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height)];
    [self.view addSubview:self.playerViewController.view];
    [player play];
    
}

// Local Web Server Protocol
- (PlayerState)onCheckPlayerStatus:(NSString *)uri {
    // if you have not been prepared you should return 'PlayerStateFail'
    // instead of 'PlayerStateReadyToPlay'
    return PlayerStateReadyToPlay;
}

- (void)onError:(int)errorCode errorMessage:(NSString *)errorMessage {
    NSLog(@"Error %@", errorMessage);
}

- (void)onNotification:(int)notificationCode notifyMessage:(NSString *)notifyMessage {
    NSLog(@"Error %@", notifyMessage);
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
