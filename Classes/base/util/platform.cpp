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
    
	std::string platform::getBuildVersion()
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		return IOS::getBuildVer();
#endif
		return "";
	}


    void platform::rate()
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        IOS::rate(Constants::KEY_APPID);
#endif
    }

	void platform::openURL(const std::string& url)
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		IOS::openURL(url);
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
    
    void platform::saveToAlbum(const std::string &fileURL)
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        IOS::saveToAlbum(fileURL);
#endif
    }

    void platform::updateAchGC(const std::string& ach, float percent, std::function<void()> okCB)
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		IOS::updateGCAchievement(ach, percent, okCB);
#endif
	}
    
    void platform::resetAchGC()
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        IOS::resetAchievement();
#endif
    }
	
	bool platform::share2Twitter(const std::string& imagePath, const std::string msg)
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		return IOS::share2Twitter(imagePath, msg, std::string(Constants::KEY_APPID));
#endif
		return false;
	}

	bool platform::share2FB(const std::string& imagePath, const std::string msg)
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		return IOS::share2Facebook(imagePath, msg, std::string(Constants::KEY_APPID));
#endif
		return false;
	}
}