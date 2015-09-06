//
//  GlobalVar.h
//  fPlay
//
//  Created by Duc_NH on 5/6/14.
//
//

#ifndef __fPlay__GlobalVar__
#define __fPlay__GlobalVar__
#include "cocos2d.h"
#include <vector>
#include <string>
#include <unordered_map>
USING_NS_CC;

struct sMyData{	
    bool isFb;
	bool isEnableAudio;	
	bool isEnableVibration;
};

enum EGAME_STATE {
    GS_OFF = 0,
    GS_LOGIN,
    GS_SEL_GAMESVR,
    GS_SEL_ROOM,
    GS_WAIT_PLAY,
    GS_PLAY,
	GS_VIEW
};

struct sFriendInfo {
    std::string fbId;
    std::string uName;
    uint32_t uId;
    int32_t roomId;
    int32_t gameSvrId;
    int64_t money;
};

class GlobalVar {
public:
	static bool requestLoginFB;
	static bool isInBackground;
	static bool isIPVN;
	static bool needCheckIP;
	static bool checkedDownload;
    static int curGameSvrId;
    static EGAME_STATE gameState;
    static cocos2d::Layer* curScene;
	static bool isLaunching;
    static int fbReady;
	static Texture2D* avaTex;
	static bool isLaunchPoker;
	static bool isLaunchPokerHK;
	static bool isLaunchTala;
	static bool isLaunchTLMN;
	static bool isLaunchSlot;
	static bool isLaunchBinh;
    static int randomNameCount;
    static bool hasDailyGift;
    static int dailyGiftDay;
    static int goldPerDay;
	static bool needReloadImages;
    static int gameVersion;
	static std::unordered_map<std::string, Texture2D*> avaDB;
	static bool inServer;
	static sMyData myData;
};

#endif /* defined(__fPlay__GlobalVar__) */
