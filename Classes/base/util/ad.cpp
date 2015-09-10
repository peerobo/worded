#include "ad.h"
#include <cocos2d.h>
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "AppTrackerWrapper.h"
#include "PluginVungle.h"
#endif

namespace util
{
	void ad::initLeadbolt(std::string apikey)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

		// Initialize Leadbolt SDK with your API Key
		AppTrackerWrapper::startSession(apikey.c_str());

		// cache Leadbolt Ad without showing it
		AppTrackerWrapper::loadModuleToCache("inapp");

#endif
	}
    
    void ad::initVungle()
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        sdkbox::PluginVungle::init();
#endif
    }
    
    void ad::showVungle()
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        sdkbox::PluginVungle::show("reward");
#endif
    }

	void ad::showLeadboltAd()
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		AppTrackerWrapper::loadModule("inapp");
#endif
	}
}