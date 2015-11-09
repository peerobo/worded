#pragma once
#include <cocos2d.h>
#include <platform/CCFileUtils.h>

USING_NS_CC;

#define CONST_STR const std::string& 

namespace util
{
	class common
	{
	private:
		static ValueMap dataDict;
	public:
		static std::string getCacheDirectory();
		static std::string getTmpDirectory();
		static void terminateApp();
		static bool replace(std::string& sourceStr, const std::string& searchStr, const std::string& replaceStr);
		static void trimSpace(std::string& sourceStr);
		static std::string numberWithCommas(unsigned long long n);
		static uint32_t playSound(const char* snd, bool loop);
		static void playSoundNoResponse(const char* snd, bool loop);
		static void playMusic(const char* music);
		static void stopSound(uint32_t id);
		static void stopAllSounds(bool fadeOut = false);
        static void stopMusic(bool fadeOut = false);
		static std::vector<std::string> splitStr(const char* source, char delim);
		static void capitalize(std::string& str);
		static Value getValue(const std::string& key);
		static void saveValue(const std::string& key, Value value);
		static std::string enc(const std::string& msg);
		static std::string dec(const std::string& msg);
	};
}
