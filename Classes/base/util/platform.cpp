#include "platform.h"
#include "cocos2d.h"
#include "../../GlobalVar.h"
#include "../../Constants.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "ios/IOS.h"
#endif

namespace util
{
	void platform::vibrate()
	{
		if (GlobalVar::myData.isEnableVibration)
		{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
			GlobalVar::curScene->runAction(Sequence::create(
				CallFunc::create(std::bind(&IOS::vibrate)),
				DelayTime::create(0.3f),
				CallFunc::create(std::bind(&IOS::vibrate)),
				NULL
				));
#endif
		}
	}
    
    void platform::rate()
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        IOS::rate(Constants::KEY_APPID);
#endif
    }
    
    void platform::authenGC()
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        IOS::authenGC();
#endif
    }
    
    bool platform::isGC()
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        return IOS::isGC;
#else
        return false;
#endif
    }
    
    void platform::showGC()
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        IOS::showGC();
#endif
    }
    
    void platform::setScoreGC(const std::string &cat, int score)
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        IOS::setScoreGC(cat, score);
#endif
    }
}