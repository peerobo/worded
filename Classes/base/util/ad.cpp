#include "ad.h"
#include <cocos2d.h>
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "AppTrackerWrapper.h"
#include "ios/IOS.h"
#endif

namespace util
{
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
    
    void ad::showVungle()
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        IOS::vungleShow();
#endif
    }

	void ad::showLeadboltAd()
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		AppTrackerWrapper::loadModule("inapp");
#endif
	}
}