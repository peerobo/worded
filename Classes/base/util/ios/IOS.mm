#include "IOS.h"
#include "AppController.h"
#import <AudioToolbox/AudioServices.h>
#import <GameKit/GameKit.h>

@interface IOSUtility : NSObject <GKGameCenterControllerDelegate>

@end

@implementation IOSUtility
- (void)gameCenterViewControllerDidFinish:(GKGameCenterViewController *)gameCenterViewController {
    [gameCenterViewController dismissViewControllerAnimated:YES completion:nil];
}
@end

static IOSUtility* iosUtil = nil;

bool IOS::isGC = false;

void IOS::vibrate()
{
	AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
}

void IOS::rate(const std::string& appId)
{
    NSString* nsAppId = [NSString stringWithUTF8String:appId.c_str()];
    NSString* url = [NSString stringWithFormat:@"https://itunes.apple.com/app/%@", nsAppId];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:url]];
}

void IOS::authenGC()
{
    GKLocalPlayer* localPlayer = [GKLocalPlayer localPlayer];
    localPlayer.authenticateHandler = ^(UIViewController* view, NSError* err){
        if (view != nil) {
            [[UIApplication sharedApplication].keyWindow.rootViewController presentViewController:view animated:YES completion:nil];
        }
        else{
            if ([GKLocalPlayer localPlayer].authenticated) {
                isGC = true;
            }
            else{
                isGC = false;
            }
                
        }
    };
    if (iosUtil == nil) {
        iosUtil = [[IOSUtility alloc]init];
    }
}

void IOS::showGC()
{
    if(isGC)
    {
        GKGameCenterViewController* gcView = [[GKGameCenterViewController alloc]init];
        gcView.gameCenterDelegate = iosUtil;
        
        gcView.viewState = GKGameCenterViewControllerStateLeaderboards;
        [[UIApplication sharedApplication].keyWindow.rootViewController presentViewController:gcView animated:YES completion:nil];
    }
}

void IOS::setScoreGC(const std::string &cat, int score)
{
    if(!isGC)
        return;
    NSString* idCat = [NSString stringWithUTF8String:cat.c_str()];
    GKScore* scoreGC = [[GKScore alloc] init];
    scoreGC.value = score;
    scoreGC.leaderboardIdentifier = idCat;
    [GKScore reportScores:@[scoreGC] withCompletionHandler:^(NSError * _Nullable error) {
        if (error) {
            NSLog(@"%@", [error localizedDescription]);
        }

    }];

}