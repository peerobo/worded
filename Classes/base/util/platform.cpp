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
}