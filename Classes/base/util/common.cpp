#include "common.h"
#include <regex>
#include <audio/include/SimpleAudioEngine.h>
#include "../../GlobalVar.h"
#include <cctype>
#include "../../Constants.h"

namespace util {

	ValueMap common::dataDict = {};

	void common::saveValue(const std::string& key, Value val)
	{
		FileUtils* fileUtil = FileUtils::getInstance();
		std::string path = getCacheDirectory();
		path += "data.dat";
		dataDict[enc(key)] = val;
		fileUtil->writeToFile(dataDict, path);
	}

	std::string common::enc(const std::string& msg)
	{
//		std::string out(msg);
//		for (int i = 0; i < msg.length(); ++i)
//		{
//			out[i] += 10;
//		}
//		return out;
        return msg;
	}

	std::string common::dec(const std::string& msg)
	{
//		std::string out(msg);
//		for (int i = 0; i < msg.length(); ++i)
//		{
//			out[i] -= 10;
//		}
//		return out;
        return msg;
	}

	Value common::getValue(const std::string& key)
	{	
		if (dataDict.size() == 0)
		{
			FileUtils* fileUtil = FileUtils::getInstance();
			std::string path = getCacheDirectory();
			path += "data.dat";
			dataDict = fileUtil->getValueMapFromFile(path);
		}

		ValueMap::iterator it = dataDict.find(key);
		if (it != dataDict.end())
		{
			Value val = it->second;
			return val;
		}
		else
		{
			return Value::Null;
		}
	}

	std::vector<std::string> common::splitStr(const char* source, char delim)
	{
		std::vector<std::string> vecSpltStrings;
		std::istringstream mainString(source);
		std::string string;
		while (std::getline(mainString, string, delim))
		{
			vecSpltStrings.push_back(string);
		}
		return vecSpltStrings;
	}

	void common::capitalize(std::string& str)
	{
		if(str.length() == 0)
			return;
		str[0] = std::toupper(str[0]);
	}

	std::string common::getCacheDirectory() 
	{
		#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
				std::string path = FileUtils::getInstance()->getWritablePath();
				size_t idx = path.find("Documents/");
				if (idx != std::string::npos)
				{
					path.erase(idx);
				}
				path.append("Library/Caches/");
				return path;
		#elif CC_TARGET_PLATFORM == CC_PLATFORM_MAC
				return "/Library/Caches/";
		#else
				return FileUtils::getInstance()->getWritablePath();
		#endif
	}

	std::string common::getTmpDirectory()
	{
		#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
				std::string path = FileUtils::getInstance()->getWritablePath();
				size_t idx = path.find("Documents/");
				if (idx != std::string::npos)
				{
					path.erase(idx);
				}
				path.append("tmp/");
				return path;
		#else
				return FileUtils::getInstance()->getWritablePath();
		#endif
	}

	void common::terminateApp()
	{
		Director::getInstance()->end();
		exit(0);
	}

	bool common::replace(std::string& sourceStr, const std::string& searchStr, const std::string& replaceStr)
	{
		size_t start_pos = sourceStr.find(searchStr);
		bool found = false;
		while (start_pos != std::string::npos)
		{
			found = true;
			sourceStr.replace(start_pos, searchStr.length(), replaceStr);
			start_pos = sourceStr.find(searchStr);
		}

		return found;
	}

	void common::trimSpace(std::string& sourceStr)
	{
		std::regex b("^\\s+");
		std::string rbegin = std::regex_replace(sourceStr, b, "");
		std::regex e("\\s+$");
		std::string rend = std::regex_replace(rbegin, e, "");
		std::regex m("\\s+");
		std::string rm = std::regex_replace(rend, m, " ", std::regex_constants::match_any);
		sourceStr = rm;
	}

	std::string common::numberWithCommas(unsigned long long n)
	{
		std::string s;
		int cnt = 0;
		do
		{
			s.insert(0, 1, char('0' + n % 10));
			n /= 10;
			if (++cnt == 3 && n)
			{
				s.insert(0, 1, '.');
				cnt = 0;
			}
		} while (n);
		return s;
	}

	uint32_t common::playSound(const char* snd, bool loop)
	{
		if (!GlobalVar::myData.isEnableAudio)
			return -1;
		std::string sound(snd);
//		std::size_t found = sound.find(Constants::ASS_SUFFIX_SOUND);
//		if (found==std::string::npos)
//			sound += std::string(Constants::ASS_SUFFIX_SOUND);
		CocosDenshion::SimpleAudioEngine* ins = CocosDenshion::SimpleAudioEngine::getInstance();
		return ins->playEffect(sound.c_str(), loop);
	}

	void common::playSoundNoResponse(const char* snd, bool loop)
	{
		playSound(snd,loop);
	}
    
    void common::stopMusic(bool fadeOut)
    {
        if (fadeOut)
        {
            Vector<FiniteTimeAction*> v;
            auto instance = CocosDenshion::SimpleAudioEngine::getInstance();
            float sound = 1.0f;
            float delayTime = 0.2f;
            for (int i = 0; i < 9; i++)
            {
                sound -= 0.1f;
                v.pushBack(CallFunc::create(CC_CALLBACK_0(CocosDenshion::SimpleAudioEngine::setBackgroundMusicVolume,instance,sound)));
                v.pushBack(DelayTime::create(delayTime));
                if (i == 8)
                {
                    v.pushBack(CallFunc::create(CC_CALLBACK_0(CocosDenshion::SimpleAudioEngine::stopBackgroundMusic, instance,false)));
                    v.pushBack(CallFunc::create(CC_CALLBACK_0(CocosDenshion::SimpleAudioEngine::setBackgroundMusicVolume, instance, 1)));
                }
            }
            GlobalVar::curScene->runAction(Sequence::create(v));
        }
        else
        {
            CocosDenshion::SimpleAudioEngine* ins = CocosDenshion::SimpleAudioEngine::getInstance();
            ins->stopBackgroundMusic();
        }
    }

	void common::playMusic(const char* music)
	{
		if (!GlobalVar::myData.isEnableAudio)
			return;
		CocosDenshion::SimpleAudioEngine* ins = CocosDenshion::SimpleAudioEngine::getInstance();
		if(!ins->isBackgroundMusicPlaying())
			ins->playBackgroundMusic(music, true);
	}

	void common::stopSound(uint32_t id)
	{
		CocosDenshion::SimpleAudioEngine* ins = CocosDenshion::SimpleAudioEngine::getInstance();
		ins->stopEffect(id);
	}

	void common::stopAllSounds(bool fadeOut)
	{
		if (fadeOut)
		{
			Vector<FiniteTimeAction*> v;
			auto instance = CocosDenshion::SimpleAudioEngine::getInstance();
			float sound = 1.0f;
			float delayTime = 0.3f;
			for (int i = 0; i < 9; i++)
			{
				sound -= 0.1f;
				v.pushBack(CallFunc::create(CC_CALLBACK_0(CocosDenshion::SimpleAudioEngine::setEffectsVolume, instance, sound)));
				v.pushBack(CallFunc::create(CC_CALLBACK_0(CocosDenshion::SimpleAudioEngine::setBackgroundMusicVolume,instance,sound)));				
				v.pushBack(DelayTime::create(delayTime));
				if (i == 8)
				{
					v.pushBack(CallFunc::create(CC_CALLBACK_0(CocosDenshion::SimpleAudioEngine::stopAllEffects, instance)));
					v.pushBack(CallFunc::create(CC_CALLBACK_0(CocosDenshion::SimpleAudioEngine::stopBackgroundMusic, instance,false)));
					v.pushBack(CallFunc::create(CC_CALLBACK_0(CocosDenshion::SimpleAudioEngine::setEffectsVolume, instance, 1)));
					v.pushBack(CallFunc::create(CC_CALLBACK_0(CocosDenshion::SimpleAudioEngine::setBackgroundMusicVolume, instance, 1)));
				}
			}
			GlobalVar::curScene->runAction(Sequence::create(v));
		}
		else
		{
			CocosDenshion::SimpleAudioEngine* ins = CocosDenshion::SimpleAudioEngine::getInstance();
			ins->stopAllEffects();
			ins->stopBackgroundMusic();
		}
		
	}
}
