#include "ad.h"
#include <cocos2d.h>
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "AppTrackerWrapper.h"
#include "ios/IOS.h"
#endif

namespace util
{
	bool ad::isVideoAdAvailable()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		return IOS::isVungleAvailable;
#endif
		return true;
	}

	void ad::initLeadbolt(const std::string& apikey)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

		// Initialize Leadbolt SDK with your API Key
		AppTrackerWrapper::startSession(apikey.c_str());

		// cache Leadbolt Ad without showing it
		AppTrackerWrapper::loadModuleToCache("inapp");
#endif
	}
    
    void ad::initVungle(const std::string& appid)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        IOS::vungleInit(appid);
#endif
    }
    
    void ad::showVungle(std::function<void(bool)> onShownCB, std::function<void(bool)> onRewardCB)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		IOS::vungleShownCB = onShownCB;
		IOS::vungleRewardCB = onRewardCB;
        IOS::vungleShow();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		cocos2d::log("show Video Vungle");
		onRewardCB(true);
#endif
    }

	void ad::showLeadboltAd()
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		if(AppTrackerWrapper::isAdReady("inapp"))
			AppTrackerWrapper::loadModule("inapp");

		// cache Leadbolt Ad without showing it
		AppTrackerWrapper::loadModuleToCache("inapp");
#endif
		cocos2d::log("Show Leadbolt ad");
	}
}