//
//  GlobalVar.cpp
//  fPlay
//
//  Created by Duc_NH on 5/6/14.
//
//

#include "GlobalVar.h"
int GlobalVar::gameVersion = 12;
bool GlobalVar::checkedDownload = false;
bool GlobalVar::requestLoginFB = false;
bool GlobalVar::isIPVN = true;
bool GlobalVar::needCheckIP = true;
bool GlobalVar::isLaunching = true;
bool GlobalVar::isInBackground = false;
int GlobalVar::curGameSvrId = -1;
EGAME_STATE GlobalVar::gameState = GS_OFF;
cocos2d::Layer* GlobalVar::curScene = NULL;
bool GlobalVar::isLaunchPoker = false;
bool GlobalVar::isLaunchPokerHK = false;
bool GlobalVar::isLaunchTala = false;
bool GlobalVar::isLaunchTLMN = false;
bool GlobalVar::isLaunchSlot = false;
bool GlobalVar::isLaunchBinh = false;
Texture2D* GlobalVar::avaTex = NULL;
int GlobalVar::randomNameCount = -1;
bool GlobalVar::hasDailyGift = false;
int GlobalVar::dailyGiftDay = 1;
int GlobalVar::goldPerDay = 0;
bool GlobalVar::needReloadImages = false;
bool GlobalVar::inServer = false;
std::unordered_map<std::string, Texture2D*> GlobalVar::avaDB;
sMyData GlobalVar::myData = {};

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
int GlobalVar::fbReady = 0;
#else
int GlobalVar::fbReady = -1;
#endif