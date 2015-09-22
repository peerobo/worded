#include "IOS.h"
#include "AppController.h"
#import <AudioToolbox/AudioServices.h>
#import <GameKit/GameKit.h>

void IOS::vibrate()
{
	AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
}

void IOS::rate(std::string appId)
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
}