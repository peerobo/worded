#include "IOS.h"
#include "AppController.h"
#import <AudioToolbox/AudioServices.h>
#import <GameKit/GameKit.h>
#import <Social/Social.h>
#import <VungleSDK/VungleSDK.h>

////////////////////////////////////////////////////////////////////////////////////////
//                                   objective c
////////////////////////////////////////////////////////////////////////////////////////

@interface IOSUtility : NSObject <GKGameCenterControllerDelegate, VungleSDKDelegate>

@end

@implementation IOSUtility
- (void)gameCenterViewControllerDidFinish:(GKGameCenterViewController *)gameCenterViewController {
    [gameCenterViewController dismissViewControllerAnimated:YES completion:nil];
}

- (void)vungleSDKAdPlayableChanged:(BOOL)isAdPlayable
{
    IOS::isVungleAvailable = isAdPlayable == YES ? true: false;
    
    NSLog(@"Ad Vungle available: %@", isAdPlayable ? @"yes" : @"no");
}

- (void)vungleSDKwillShowAd
{
    if(IOS::vungleShownCB != nullptr)
        IOS::vungleShownCB(true);
}

- (void)vungleSDKwillCloseAdWithViewInfo:(NSDictionary*)viewInfo willPresentProductSheet:(BOOL)willPresentProductSheet
{
    if(willPresentProductSheet == NO)
    {
        if(IOS::vungleShownCB != nullptr)
            IOS::vungleShownCB(false);
        NSLog(@"The ad presented was not tapped - the user has returned to the app");
        NSLog(@"ViewInfo Dictionary:");
        for(NSString * key in [viewInfo allKeys]) {
            NSLog(@"%@ : %@", key, [[viewInfo objectForKey:key] description]);
        }
		if([viewInfo valueForKey:@"completedView"]  == 1 && IOS::vungleRewardCB != nullptr)
			IOS::vungleRewardCB(true);
		else
			IOS::vungleRewardCB(false);
			
//        2015-09-27 00:21:07.288 Worded by PE[1566:60b] The ad presented was not tapped - the user has returned to the app
//        2015-09-27 00:21:07.292 Worded by PE[1566:60b] ViewInfo Dictionary:
//        2015-09-27 00:21:07.295 Worded by PE[1566:60b] playTime : 15.08166666666667
//        2015-09-27 00:21:07.297 Worded by PE[1566:60b] didDownload : 0
//        2015-09-27 00:21:07.298 Worded by PE[1566:60b] videoLength : 15.08166666666667
//        2015-09-27 00:21:07.300 Worded by PE[1566:60b] completedView : 1
    }
        
}

- (void)vungleSDKwillCloseProductSheet:(id)productSheet
{
    if(IOS::vungleShownCB != nullptr)
        IOS::vungleShownCB(false);
    if(IOS::vungleRewardCB != nullptr)
        IOS::vungleRewardCB(true);
}
@end


////////////////////////////////////////////////////////////////////////////////////////
//                                   c++
////////////////////////////////////////////////////////////////////////////////////////

static IOSUtility* iosUtil = [[IOSUtility alloc]init];
bool IOS::isVungleAvailable = false;
bool IOS::isGC = false;
std::function<void(bool)> IOS::vungleShownCB = nullptr;
std::function<void(bool)> IOS::vungleRewardCB = nullptr;

void IOS::resetAchievement()
{
    [GKAchievement resetAchievementsWithCompletionHandler:^(NSError * _Nullable error) {
        if(error){
            NSLog(@"%@", [error localizedDescription]);
        }
    }];
}

void IOS::vibrate()
{
	AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
}

void IOS::updateGCAchievement(const std::string& ach, float percent, std::function<void()> okCB)
{
	GKAchievement* gk = [[GKAchievement alloc] init];
	NSString* idAch = [NSString stringWithUTF8String:ach.c_str()];
	gk.identifier = idAch;
	gk.percentComplete = percent;
    gk.showsCompletionBanner = YES;
    [GKAchievement reportAchievements:@[gk] withCompletionHandler:^(NSError * _Nullable error) {
        if (error) {
            NSLog(@"%@", [error localizedDescription]);
        }
        else{
            if(okCB)
                okCB();
        }
        
    }];
    [gk autorelease];
}

bool IOS::share2Twitter(const std::string& path,const std::string& msg,  const std::string& url)
{
    if ([SLComposeViewController isAvailableForServiceType: SLServiceTypeTwitter]) {
        SLComposeViewController* tweetSheetOBJ = [SLComposeViewController composeViewControllerForServiceType:SLServiceTypeTwitter];
        [tweetSheetOBJ setInitialText:[NSString stringWithUTF8String:msg.c_str()]];
        UIImage* img = [[UIImage alloc]initWithContentsOfFile: [NSString stringWithUTF8String:path.c_str()]];
        [tweetSheetOBJ addImage: img];
		[tweetSheetOBJ addURL:[NSURL URLWithString:[NSString stringWithUTF8String:url.c_str()]]];
        [[UIApplication sharedApplication].keyWindow.rootViewController presentViewController:tweetSheetOBJ animated:YES completion:nil];
        [img autorelease];
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
        [fbSheetObj addURL:[NSURL URLWithString:[NSString stringWithUTF8String:url.c_str()]]];
        [[UIApplication sharedApplication].keyWindow.rootViewController presentViewController:fbSheetObj animated:YES completion:nil];
        [img autorelease];
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
    [img autorelease];
}

void IOS::openURL(const std::string& URL)
{
    NSString* nsAppId = [NSString stringWithUTF8String:URL.c_str()];
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
    [scoreGC autorelease];
}

void IOS::vungleInit(const std::string &appID)
{
    NSString* vungleID = [NSString stringWithUTF8String:appID.c_str()];
    [[VungleSDK sharedSDK] startWithAppId:vungleID];
    [[VungleSDK sharedSDK] setDelegate: iosUtil];
    [vungleID autorelease];
}

void IOS::vungleShow()
{
    UIViewController* v = [UIApplication sharedApplication].keyWindow.rootViewController;
    NSError *error;
    [[VungleSDK sharedSDK] playAd:v error:&error];
    if (error) {
        NSLog(@"Error encountered playing ad: %@", error);
    }
}

static std::string getBuildVer()
{
	NSString *version = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"];
	return std::string(version.UTF8String);
}