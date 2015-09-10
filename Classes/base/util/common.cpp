#include "common.h"
#include <CCFileUtils.h>
#include <regex>
#include <audio/include/SimpleAudioEngine.h>
#include "../../GlobalVar.h"

USING_NS_CC;

namespace util {

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
		CocosDenshion::SimpleAudioEngine* ins = CocosDenshion::SimpleAudioEngine::getInstance();
		return ins->playEffect(snd, loop);
	}

	void common::playSoundNoResponse(const char* snd, bool loop)
	{
		if (!GlobalVar::myData.isEnableAudio)
			return;
		CocosDenshion::SimpleAudioEngine* ins = CocosDenshion::SimpleAudioEngine::getInstance();
		ins->playEffect(snd, loop);
	}

	void common::playMusic(const char* music)
	{
		if (!GlobalVar::myData.isEnableAudio)
			return;
		CocosDenshion::SimpleAudioEngine* ins = CocosDenshion::SimpleAudioEngine::getInstance();
		ins->playBackgroundMusic(music, true);
	}

	void common::stopAllSounds()
	{
		CocosDenshion::SimpleAudioEngine* ins = CocosDenshion::SimpleAudioEngine::getInstance();
		ins->stopAllEffects();
		ins->stopBackgroundMusic();
	}
}