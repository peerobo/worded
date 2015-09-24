#include "IOS.h"
#include "AppController.h"
#import <AudioToolbox/AudioServices.h>
#import <GameKit/GameKit.h>
#import <Social/Social.h>

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

void IOS::updateGCAchievement(const std::string& ach, float percent)
{
	GKAchievement* gk = [[GKAchievement alloc] init];
	NSString* idAch = [NSString stringWithUTF8String:ach.c_str()];
	gk.identifier = idAch;
	gk.percentComplete = percent;
    [GKAchievement reportAchievements:@[gk] withCompletionHandler:^(NSError * _Nullable error) {
        if (error) {
            NSLog(@"%@", [error localizedDescription]);
        }
        
    }];

}

bool IOS::share2Twitter(const std::string& path,const std::string& msg,  const std::string& url)
{
    if ([SLComposeViewController isAvailableForServiceType: SLServiceTypeTwitter]) {
        SLComposeViewController* tweetSheetOBJ = [SLComposeViewController composeViewControllerForServiceType:SLServiceTypeTwitter];
        [tweetSheetOBJ setInitialText:[NSString stringWithUTF8String:msg.c_str()]];
        UIImage* img = [[UIImage alloc]initWithContentsOfFile: [NSString stringWithUTF8String:path.c_str()]];
        [tweetSheetOBJ addImage: img];
		[tweetSheetOBJ addURL:[NSString stringWithUTF8String:url.c_str()]];
        [[UIApplication sharedApplication].keyWindow.rootViewController presentViewController:tweetSheetOBJ animated:YES completion:nil];
		return true;
    }
	else
	{
		return false;
	}
}

bool IOS::share2Facebook(const std::string& path,const std::string& msg, const std::string& url)
{
    if ([SLComposeViewController isAvailableForServiceType: SLServiceTypeFacebook]) {
        SLComposeViewController* fbSheetObj = [SLComposeViewController composeViewControllerForServiceType:SLServiceTypeFacebook];
        [fbSheetObj setInitialText:[NSString stringWithUTF8String:msg.c_str()]];
        UIImage* img = [[UIImage alloc]initWithContentsOfFile: [NSString stringWithUTF8String:path.c_str()]];
        [fbSheetObj addImage: img];
		[tweetSheetOBJ addURL:[NSString stringWithUTF8String:url.c_str()]];
        [[UIApplication sharedApplication].keyWindow.rootViewController presentViewController:fbSheetObj animated:YES completion:nil];
		return true;
    }
	else
	{
		return false;
	}
}

void IOS::saveToAlbum(const std::string &filePath)
{
    UIImage* img = [[UIImage alloc]initWithContentsOfFile: [NSString stringWithUTF8String:filePath.c_str()]];
    UIImageWriteToSavedPhotosAlbum(img, nil, nil, nil);
}

void IOS::rate(const std::string& appId)
{
    NSString* nsAppId = [NSString stringWithUTF8String:appId.c_str()];
    NSString* url = [NSString stringWithFormat:@"%@", nsAppId];
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
        
        gcView.viewState = GKGameCenterViewControllerStateDefault;
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